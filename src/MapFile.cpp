#include "MapFile.h"

#include <utility>

using namespace CustomClasses;

MapFile::MapFile(std::string _path, int allocatedSpace) {
    path = std::move(_path);
    fileSize = allocatedSpace;

    //init a file
    auto fileReader =  std::ifstream(path, std::ios::binary);
    bool fileExists = fileReader.is_open();

    //if file doesn't exist, fill it with default size
    if (!fileExists) {
        //create new
        std::ofstream writeFile(path);
        //size
        std::string s(allocatedSpace, 0x00);
        writeFile << s << std::flush;
    }else{
        //set file size
        fileReader.seekg(0, std::ios::end);
        fileSize = fileReader.tellg();
    }

    fileReader.close();

    file = new std::fstream(path, std::ios::in | std::ios::out | std::ios::binary);

    *file << std::noskipws;
    mappedFile = mio::ummap_sink(path);
}

void MapFile::set(uint64_t index, std::vector<unsigned char> *value) {
    if (index + value->size() > fileSize || index < 0)
        throw std::runtime_error("Map file out of range, index " + std::to_string(index) + " data size " + std::to_string(value->size()) + ", file size " + std::to_string(fileSize));

//    loop through the values, most significant bits first
    for (int i = 0; i < value->size(); i++) {
        mappedFile[index + i] = value->at(i);
    }

    mappedFile.sync(error);
    if (error) std::cerr << error.message() << "\n";
}

std::vector<unsigned char> *MapFile::get(uint64_t index, int length) {
    auto values = new std::vector<unsigned char>();
    for(int i = 0; i < length; i++) values->push_back(mappedFile[index + i]);
    return values;
}
