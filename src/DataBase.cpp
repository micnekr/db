#include "DataBase.h"

#include <utility>

using namespace CustomClasses;

std::unordered_map<unsigned char, std::type_index> DataBase::binToTypeRepresentations;
std::unordered_map<std::type_index, unsigned char> DataBase::typeToBinRepresentations;
bool DataBase::haveTypeBinaryRepresentationsBeenSet = false;

DataBase::DataBase(std::string _name, std::string primaryMapPath, std::string secondaryMapPath,
                   int primaryAllocatedSpace, int secondaryAllocatedSpace) {

    if (!haveTypeBinaryRepresentationsBeenSet) {
        std::cout << "Setting representations for classes..." << "\n";
        //first hex value being a 1 means it is a custom class that can be serialised normally
        std::vector<unsigned char> representations = {0x10, 0x11, 0x12};
        std::vector<std::type_index> typeIndices = {std::type_index(typeid(StringComponent)),
                                                    std::type_index(typeid(NumberComponent)),
                                                    std::type_index(typeid(NullComponent))};

        for (int i = 0; i < representations.size(); i++) {
            DataBase::binToTypeRepresentations.emplace(representations.at(i), typeIndices.at(i));
            DataBase::typeToBinRepresentations[typeIndices.at(i)] = representations.at(i);
        }
        haveTypeBinaryRepresentationsBeenSet = true;
    }

    try {
        primaryMap = new MapFile(std::move(primaryMapPath), primaryAllocatedSpace);
        secondaryMap = new MapFile(std::move(secondaryMapPath), secondaryAllocatedSpace);
        charStreamDecoder = new CharStreamDecoder();

        std::cout << "created the maps\n";

        className = "Database";
        name = std::move(_name);

        tombstones = new std::list<TombIndex *>();

        updateTombstones();
        std::cout << "updated the tombstones\n";
    } catch (const std::system_error &e) {
        throw std::runtime_error("Files could not be opened or created");
    }
}

void DataBase::createTable(const std::string& _name) {
    auto *newTablePtr = new Table(_name, this);
    setChild(_name, newTablePtr);
}

void DataBase::updateTombstones() const {
    for (const auto &iterator : *tombstones) delete iterator;
    tombstones->clear();

    //reset the flags and go to the beginning
    secondaryMap->file->clear();
    secondaryMap->file->seekg(std::ios_base::beg);

    //loop through the file
    //start at the first character because the index 0 is not possible to be written to

    int lastg = 1;
    char c;


    auto *newTombIndex = new TombIndex();

    newTombIndex->startIndex = 1;

    //skip the first character
    secondaryMap->file->seekg(1, std::ios::beg);

    while (true) {
        secondaryMap->file->read((char *) &c, sizeof(char));

        if (secondaryMap->file->eof()) break;

        CharStreamDecoderStates previousState = charStreamDecoder->state;

        charStreamDecoder->next(c);

        //if started reading a new block, end the tombstone
        if (previousState == CharStreamDecoderStates::InvalidData &&
            charStreamDecoder->state != CharStreamDecoderStates::InvalidData) {
            //-1 because read advanced the pointer
            newTombIndex->endIndex = int(secondaryMap->file->tellg()) - 1;

            //if an empty index, delete
            if (newTombIndex->startIndex == newTombIndex->endIndex) delete newTombIndex;
            else tombstones->push_back(newTombIndex);
        }

        //if stopped reading length, skip to the next occurrence
        if (charStreamDecoder->state == CharStreamDecoderStates::ReadingData) {
            secondaryMap->file->seekg(charStreamDecoder->charactersLength, std::ios::cur);
            charStreamDecoder->reset();
            newTombIndex = new TombIndex();
            newTombIndex->startIndex = secondaryMap->file->tellg();
            lastg = secondaryMap->file->tellg();
        }
        lastg++;
    }

    //if at the end, the tombstone hasn't finished, remember it
    const int lastPositionIndex = lastg - 1;
    if (newTombIndex->startIndex == lastPositionIndex) delete newTombIndex;
    else {
        newTombIndex->endIndex = lastPositionIndex;
        tombstones->push_back(newTombIndex);
    }
}

uint64_t charVectorTouint64_t(std::vector<unsigned char> *vals) {
    uint64_t value = 0;
    for (unsigned char val : *vals) {
        value <<= 8u;
        value += val;
    }
    return value;
}

std::vector<unsigned char> *uint64_tToCharVector(uint64_t value, int length) {
    std::vector<unsigned char> bytes;

    for (int i = 0; i < length; i++) {
        bytes.push_back(value & 0xFFu);
        value >>= 8u;
    }

    auto *returnValue = new std::vector<unsigned char>();
    for (int i = length - 1; i >= 0; i--) returnValue->push_back(bytes.at(i));

    return returnValue;
}


void DataBase::storePrimaryAndSecondaryMap(std::vector<unsigned char> *pmIndexPointerCharVector, Component *key,
                                           Component *value) {
    //TODO: check if is already stored

    //first, serialise the data to store
    std::vector<unsigned char> *serialisedValue = DataBase::serialiseSecondaryMapEntry(key, value);

    uint64_t dataLength = serialisedValue->size();
    //find a suitable location among the tombstones
    auto tombIndex = findSuitableTombIndexIterator(dataLength, Config::getInstance().defaultTOmbIndexSearchType);

    //get pointers to the new location in the secondary map
    uint64_t smPointerUInt = (*tombIndex)->startIndex;
    auto smPointerCharVector = uint64_tToCharVector(smPointerUInt,
                                                    Config::getInstance().mapFilePointerSize);

    //update the length of the tombstone
    (*tombIndex)->startIndex += dataLength;

    //set the data itself
    const int pointerSize = Config::getInstance().mapFilePointerSize;
    uint64_t pmBytePointerUInt = charVectorTouint64_t(pmIndexPointerCharVector);

    //first, check for hash collisions in pm
    std::vector<unsigned char> *pmData = primaryMap->get(pmBytePointerUInt, pointerSize);

    //check that it is all 0s
    bool isEmpty = true;
    for (unsigned char i : *pmData) {
        if (i != 0x00) {
            isEmpty = false;
            break;
        }
    }

    //if empty, then record the place
    // else, find the next place and change the address bytes
    if (isEmpty) {
        primaryMap->set(pmBytePointerUInt, smPointerCharVector);
    } else {
        //re-assign to avoid confusion
        std::vector<unsigned char> *lastPointerCharVector = pmData;
        const int lengthBytesInDataRepresentation = Config::getInstance().lengthBytesInDataRepresentation;

        while (true) {

            //data at pm index is the index of the first token, move forward by the number of length bytes
            uint64_t nextPointerUInt =
                    charVectorTouint64_t(lastPointerCharVector) + lengthBytesInDataRepresentation;
            //get the new last pointer
            std::vector<unsigned char> *newPointerCharVector = secondaryMap->get(nextPointerUInt, pointerSize);
            //check if it is all 0s
            bool isNewPositionEmpty = true;
            for (unsigned char i : *newPointerCharVector) {
                if (i != 0x00) {
                    isNewPositionEmpty = false;
                    break;
                }
            }

            //if it is, break
            if (isNewPositionEmpty) break;

            //else, update
            lastPointerCharVector = newPointerCharVector;
        }

        //set the new bytes
        uint64_t smEntryNextFieldPointerUInt =
                charVectorTouint64_t(lastPointerCharVector) + lengthBytesInDataRepresentation;
        secondaryMap->set(smEntryNextFieldPointerUInt, smPointerCharVector);
    }
    //set the values
    secondaryMap->set(smPointerUInt, serialisedValue);
}

std::list<TombIndex *>::iterator
DataBase::findSuitableTombIndexIterator(uint64_t minLength, TombIndexSearchTypes searchType) const {
    uint64_t bestLength = 0;
    std::list<TombIndex *>::iterator bestIterator;

    //loop through the tombs and check their lengths
    for (auto it = tombstones->begin(); it != tombstones->end(); it++) {
        TombIndex *currentTomb = *it;
        uint64_t length = currentTomb->endIndex - currentTomb->startIndex;

        //check the length
        if (length < minLength) continue;

        //if it is the first one

        if (bestLength == 0) {
            bestLength = length;
            bestIterator = it;
        }

        // check which type works best
        switch (searchType) {
            case TombIndexSearchTypes::First:
                return it;
            case TombIndexSearchTypes::Largest:
                if (bestLength < length) {
                    bestLength = length;
                    bestIterator = it;
                }
                break;
            case TombIndexSearchTypes::Smallest:
                if (bestLength > length) {
                    bestLength = length;
                    bestIterator = it;
                }
                break;
        }
    }
    return bestIterator;
}

std::vector<unsigned char> *DataBase::serialiseSecondaryMapEntry(Component *key, Component *value) {
    auto dataToStore = new std::vector<unsigned char>;

    const int mapFilePointerSize = Config::getInstance().mapFilePointerSize;
    const int lengthBytesInDataRepresentation = Config::getInstance().lengthBytesInDataRepresentation;

    //length|nextObject|KeyLength|Key|Value

    //length will be at the end

    //nextObject
    for (int i = 0; i < mapFilePointerSize; i++) dataToStore->push_back(0x00u);

    //Key:
    //type specifier
    auto keyBytes = new std::vector<unsigned char>;

    //add the actual serialised value
    serialiseComponent(keyBytes, key);

    //add the length to the data representation
    std::vector<unsigned char> *keyBytesLengthCharVector = uint64_tToCharVector(keyBytes->size(),
                                                                                lengthBytesInDataRepresentation);
    for (const auto &keyByteLength : *keyBytesLengthCharVector) dataToStore->push_back(keyByteLength);

    //store the overall value
    for (const auto &keyByte : *keyBytes) dataToStore->push_back(keyByte);

    //Value:
    serialiseComponent(dataToStore, value);

    //length

    // make sure that it is not longer than it should be
    uint64_t length = dataToStore->size();

    uint64_t mask = uint64_t(1) << (lengthBytesInDataRepresentation * 8u - 1u);//get the largest bit possible

    //if the largest bit is occupied, throw an error
    if ((mask & length) != 0x00u) throw std::runtime_error("The serialised map entry is too long");

    //set the highest bit
    length |= mask;

    //calculate the length chars
    //TODO: replace with the function
    std::vector<unsigned char> lengthBytes;

    for (int i = 0; i < lengthBytesInDataRepresentation; i++) {
        lengthBytes.push_back(length & 0xFFu);
        length >>= 8u;
    }

    auto bytes = new std::vector<unsigned char>();

    //add reversed length bytes
    for (int i = lengthBytes.size() - 1; i >= 0; i--) bytes->push_back(lengthBytes.at(i));
    //add data bytes
    for (unsigned char & i : *dataToStore) bytes->push_back(i);
    return bytes;
}

Component *DataBase::searchPrimaryAndSecondaryMap(std::vector<unsigned char> *pmPointerCharVector, Component *key) const {
    auto serialisedKey = new std::vector<unsigned char>;
    serialiseComponent(serialisedKey, key);

    // calculate its size
    uint64_t keySize = serialisedKey->size();
    uint64_t pmPointerUInt = charVectorTouint64_t(pmPointerCharVector);

    std::cout << "pmPointerUInt: " << pmPointerUInt << "\n";

    const int mapFilePointerSize = Config::getInstance().mapFilePointerSize;
    const int lengthBytesInDataRepresentation = Config::getInstance().lengthBytesInDataRepresentation;

    uint64_t smPointerUInt = charVectorTouint64_t(
            primaryMap->get(pmPointerUInt, mapFilePointerSize));

    //check if it is null, then return nullptr
    if(smPointerUInt == 0) return nullptr;

    //TODO: change it
    // assume it is the first one

    //find the correct entry

    uint64_t storedKeySize;

    std::cout << "smPointer" << smPointerUInt << "\n";

    while (true) {
        //move forward by the number of length bytes
        uint64_t nextPointerPointerUInt =
                smPointerUInt + lengthBytesInDataRepresentation;
        //get the new last pointer
        std::vector<unsigned char> *newPointerCharVector = secondaryMap->get(nextPointerPointerUInt,
                                                                             mapFilePointerSize);

        //read the key length bits
        //length of the key = lengthBytesInDataRepresentation
        //skip the next address
        std::vector<unsigned char> *keyLengthVector = secondaryMap->get(nextPointerPointerUInt + mapFilePointerSize,
                                                                        lengthBytesInDataRepresentation);
        storedKeySize = charVectorTouint64_t(keyLengthVector);

        //check the key lengths and then the contents
        if (keySize == storedKeySize) {
            //skip to the beginning of the key
            auto storedKey = secondaryMap->get(
                    nextPointerPointerUInt + mapFilePointerSize + lengthBytesInDataRepresentation, keySize);
            //check byte by byte
            bool areKeysEqual = true;
            for (int i = 0; i < storedKeySize; ++i) {
                if (storedKey->at(i) != serialisedKey->at(i)) {
                    areKeysEqual = false;
                    break;
                }
            }
            if (areKeysEqual) break;
        }

        //if not found, return nullptr
        bool isNewPositionEmpty = true;
        for (unsigned char i : *newPointerCharVector) {
            if (i != 0x00) {
                isNewPositionEmpty = false;
                break;
            }
        }
        if (isNewPositionEmpty) return nullptr;

        //else, update
        smPointerUInt = charVectorTouint64_t(newPointerCharVector);
    }

    // finalise the index

    //go over the file and read the length bits
    uint64_t tokenLengthUInt = charVectorTouint64_t(secondaryMap->get(smPointerUInt, lengthBytesInDataRepresentation));

    //remove the largest bit
    //get the largest bit alone, then negate it
    uint64_t mask = ~(uint64_t(1) << (lengthBytesInDataRepresentation * 8u - 1u));

    // remove the largest bit
    tokenLengthUInt &= mask;

    //remove the first bit

    //read the rest
    //do not read the address bits or length bits
    //skip the overall length, nextObject pointer, key length bytes and the key length
    uint64_t numberOfBytesBeforeValue =
            mapFilePointerSize + lengthBytesInDataRepresentation + storedKeySize;
    std::vector<unsigned char> *storedToken = secondaryMap->get(
            smPointerUInt + numberOfBytesBeforeValue + lengthBytesInDataRepresentation, tokenLengthUInt - numberOfBytesBeforeValue); // + lengthBytes because they are exlcuded in the length


    unsigned char componentTypeChar = storedToken->at(0);
    auto componentTypeIndex = DataBase::binToTypeRepresentations.at(componentTypeChar);
    auto encodedToken = new std::vector<unsigned char>();
    for (int i = 1; i < storedToken->size(); i++) encodedToken->push_back(storedToken->at(i));

    Component *retrievedComponent;

    if (componentTypeIndex == typeid(StringComponent)) {
        retrievedComponent = new StringComponent("");
        retrievedComponent->deserealise(encodedToken);
    } else if (componentTypeIndex == typeid(NumberComponent)) {
        retrievedComponent = new NumberComponent(0);
        retrievedComponent->deserealise(encodedToken);
    } else if (componentTypeIndex == typeid(NullComponent)) {
        retrievedComponent = new NullComponent();
        retrievedComponent->deserealise(encodedToken);
    }

    return retrievedComponent;
}

void DataBase::serialiseComponent(std::vector<unsigned char> *toAddTo, Component *component) {
    unsigned char typeRepresentation;
    auto componentTypeIndex = std::type_index(typeid(*component));
    try {
        typeRepresentation = DataBase::typeToBinRepresentations.at(componentTypeIndex);
    } catch (const std::out_of_range&) {
        std::string errorString = "Can not find a type byte for the given type, type ";
        errorString += componentTypeIndex.name();
        throw std::runtime_error(errorString);
    }

    toAddTo->push_back(typeRepresentation);

    std::vector<unsigned char> *serialisedValue = component->serialise();
    for (unsigned char &i : *serialisedValue) toAddTo->push_back(i);
}

std::vector<unsigned char> *DataBase::getPrimaryMapIndex(Component * component) const {
    //hash the component
    //TODO: have the same number of bits for both
    //TODO: test different key types, including null

    const int pointerSize = Config::getInstance().mapFilePointerSize;
    uint32_t bucket = component->getId() % (primaryMap->fileSize / pointerSize);
    uint64_t address = bucket * pointerSize;
    std::cout << "address: " << address << "\n";
    std::cout << "size: " << primaryMap->fileSize << "\n";
    return uint64_tToCharVector(address, 8);
}

Component *DataBase::search(Component * key) const {
    return searchPrimaryAndSecondaryMap(getPrimaryMapIndex(key), key);
}

void DataBase::store(Component* key, Component* value) {
    storePrimaryAndSecondaryMap(getPrimaryMapIndex(key), key, value);
}
