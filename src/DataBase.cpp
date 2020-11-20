#include "DataBase.h"

using namespace CustomClasses;

DataBase::DataBase(std::string _name, MapFile* _primaryMap, MapFile* _secondaryMap){
    if(_primaryMap == nullptr || _secondaryMap == nullptr) throw "Null map files in database constructor";

    primaryMap = _primaryMap;
    secondaryMap = _secondaryMap;

    className = "Database";
    name = _name;

    
}

DataBase::DataBase(std::string _name, std::string primaryMapPath, std::string secondaryMapPath, int primaryAllocatedSpace, int secondaryAllocatedSpace){
    try{
        primaryMap = new MapFile(primaryMapPath, primaryAllocatedSpace);
        secondaryMap = new MapFile(secondaryMapPath, secondaryAllocatedSpace);

        updateTombstones();
    }catch (const std::system_error& e){
        throw "Files could not be opened or created";
    }
}

void DataBase::createTable(std::string name){
    Table* newTablePtr = new Table(name, this);
    setChild(name, newTablePtr);
}

void DataBase::store(uint32_t index, Component* value){
    primaryMap->set(index, 65 * 256 + 66);
}

void DataBase::updateTombstones(){
    const char emptyChar = 0x00;
    for(const auto& iterator : tombstones) delete iterator;
    tombstones.clear();

    //reset the flags and go to the beginning
    secondaryMap->file->clear();
    secondaryMap->file->seekg(std::ios_base::beg);

    //loop through the file
    const int lengthBytesInDataRepresentation = Config::getInstance().lengthBytesInDataRepresentation;

    bool isValidData = false;
    uint64_t charactersLeft = 0;
    int lengthCharsLeft = 0;
    char c;

    std::cout << std::hex << std::bitset<8>(char(0x80)) << " char" << char(0x80) << "\n";

    while(true){
        secondaryMap->file->read((char*)&c, sizeof(char));

        if(secondaryMap->file->eof()) break;


        if(isValidData){
            //if still reading length bytes
            if(lengthCharsLeft > 0){
                std::cout << "reading length\n";
                //shift a byte to the left
                std::cout << charactersLeft << "\n";
                charactersLeft  <<= 8;
                std::cout << charactersLeft << "\n";
                charactersLeft += c;
                lengthCharsLeft--;
                std::cout << charactersLeft << " " << lengthCharsLeft << "\n";
            }else{
                if(charactersLeft == 0){
                    isValidData = false;
                }else{
                    std::cout << "length left:" << charactersLeft << "\n";
                    charactersLeft--;
                }
            }
        }else{
            //because the first bit of length is always 1, the first char can not be 0x00
            //check if starting valid data,
            if(c != 0x00){
                std::cout << "start reading\n";
                isValidData = true;
                //7F = 0111 1111
                //remove the first bit
                lengthCharsLeft = lengthBytesInDataRepresentation;
                charactersLeft = 0x7F & c;

                std::cout << lengthCharsLeft << " " << charactersLeft << "\n";
            }
        }

        std::cout << std::hex << "'" << std::bitset<16>(c) << "'\n";
    }
    std::cout << "end of search\n";

}