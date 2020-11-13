#ifndef MAP_FILE_H // include guard
#define MAP_FILE_H

#include "dep/mio/mio.hpp"

#include "Config.h"
#include "TombIndex.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>
#include <list>

namespace CustomClasses{

    class MapFile{
        public:
            std::string path;
            mio::mmap_sink* mappedFile;
            std::fstream file;
            int fileSize;

            MapFile(std::string, int);
            void set(uint32_t, uint64_t);

            std::list<TombIndex*> tombstones;

            void updateTombstones();
    };
}

#endif