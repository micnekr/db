#ifndef FILE_ACCESS_H // include guard
#define FILE_ACCESS_H

#include "dep/mio/mio.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <system_error>

namespace CustomClasses{

    class FileAccess{
        public:
            std::vector<mio::mmap_sink*> openedFiles;
            std::vector<std::string> openedFilesNames;

            void openFileSafe(std::string, int);
    };
}

#endif