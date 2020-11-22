#include "DataBase.h"

using namespace CustomClasses;

DataBase::DataBase(std::string _name, std::string primaryMapPath, std::string secondaryMapPath,
                   int primaryAllocatedSpace, int secondaryAllocatedSpace) {
    try {
        primaryMap = new MapFile(primaryMapPath, primaryAllocatedSpace);
        secondaryMap = new MapFile(secondaryMapPath, secondaryAllocatedSpace);
        charStreamDecoder = new CharStreamDecoder();

        className = "Database";
        name = _name;

        tombstones = new std::list<TombIndex *>();

        updateTombstones();
    } catch (const std::system_error &e) {
        throw std::runtime_error("Files could not be opened or created");
    }
}

void DataBase::createTable(std::string name) {
    Table *newTablePtr = new Table(name, this);
    setChild(name, newTablePtr);
}

void DataBase::store(uint32_t index, Component *value) {
    primaryMap->set(index, 65 * 256 + 66);
}

void DataBase::updateTombstones() {
    for (const auto &iterator : *tombstones) delete iterator;
    tombstones->clear();

    //reset the flags and go to the beginning
    secondaryMap->file->clear();
    secondaryMap->file->seekg(std::ios_base::beg);

    //loop through the file

    int lastg = 0;
    char c;

    TombIndex *newTombIndex = new TombIndex();

    newTombIndex->startIndex = 0;

    while (true) {
        secondaryMap->file->read((char *) &c, sizeof(char));

        if (secondaryMap->file->eof()) break;

        std::cout << "'" << std::hex << c << "'\n";
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


    for (const auto &iterator : *tombstones) {
        std::cout << iterator->startIndex << " " << iterator->endIndex << "\n";
    }
}