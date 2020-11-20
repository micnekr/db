#include "FileAccess.h"

using namespace CustomClasses;

MapFile* FileAccess::openFileSafe(std::string path, int allocatedSpace, bool needsTombstoneUpdate){
    //check if the file has already been opened

    try {
        MapFile* mapFile = new MapFile(path, allocatedSpace);

        // create a new MapFile
        openedFiles.push_back(mapFile);
        openedFilesNames.push_back(path);

        return mapFile;
    }catch(const std::system_error& e){
        std::cout << "error opening a file '" << path << "'\n";
        return nullptr;
    }
}