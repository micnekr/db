#include "MapFile.h"

using namespace CustomClasses;
MapFile::MapFile(std::string _path, int allocatedSpace){
    path = _path;
    fileSize = allocatedSpace;


    //init a file
    bool fileExists = std::ifstream(path).is_open();

    std::ofstream writeFile;

    //if file doesn't exist, fill it with default size
    if(!fileExists){
        //create new
        writeFile.open(path);
        file.open(path);
        //size
        std::string s(allocatedSpace, 0x00);
        writeFile << s << std::flush;
    }

    mappedFile = new mio::mmap_sink(path);
}

void MapFile::set(uint32_t index, uint64_t value){
    int pointerSize = Config::getInstance().mapFilePointerSize;
    uint64_t charStartIndex = index * pointerSize;
    if(charStartIndex >= fileSize || charStartIndex < 0) throw "Map file out of range, index " + std::to_string(index);

    //loop through the values, most significant bits first
    for(int i = pointerSize - 1; i >= 0; i--){
        char currentChar = static_cast<char>(value);
        (*mappedFile)[charStartIndex + i] = currentChar;

        //shift the value back by 8 bits - a size of a char
        value >>= 8;
    }
}

void MapFile::updateTombstones(){
    for(const auto& iterator : tombstones) delete iterator;
    tombstones.clear();

    //loop through the file
    file.seekg(std::ios::beg);
}