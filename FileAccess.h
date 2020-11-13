#ifndef FILE_ACCESS_H // include guard
#define FILE_ACCESS_H

#include "MapFile.h"

#include <iostream>
#include <vector>
#include <system_error>

namespace CustomClasses{

    class FileAccess{
        public:
            std::vector<MapFile*> openedFiles;
            std::vector<std::string> openedFilesNames;

            MapFile* openFileSafe(std::string, int);
    };
}

#endif