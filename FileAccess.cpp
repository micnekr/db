#include "FileAccess.h"

using namespace CustomClasses;

void FileAccess::openFileSafe(std::string path, int allocatedSpace){
    //init a file
    bool fileExists = std::ifstream(path).is_open();

    //if file doesn't exist, fill it with default size
    if(!fileExists){
        // //create new
        std::ofstream file;
        file.open(path);
        //size
        std::string s(allocatedSpace, 0x00);
        file << s;
    }

    mio::mmap_sink* rw_mmap = new mio::mmap_sink(path);

    openedFiles.push_back(rw_mmap);
    openedFilesNames.push_back(path);
}