#ifndef MAP_FILE_H // include guard
#define MAP_FILE_H

#include "dep/mio/mio.cpp"

#include "Config.h"
#include "TombIndex.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <list>
#include <vector>

namespace CustomClasses{

    class MapFile{
        public:
            std::string path;
            mio::ummap_sink mappedFile;
            std::fstream* file;
            int fileSize;

            std::error_code error;

            MapFile(std::string, int);
            void set(uint64_t, std::vector<unsigned char>*);
            std::vector<unsigned char>* get(uint64_t, int length);
    };
}

#endif