#ifndef CONFIG_H // include guard
#define CONFIG_H

#include <iostream>

namespace CustomClasses
{

    class Config
    {
    public:
        static Config &getInstance()
        {
            static Config instance; // Guaranteed to be destroyed; Instantiated on first use.
            return instance;
        }

    private:
        Config(){};

    public:
        Config(Config const &) = delete;
        void operator=(Config const &) = delete;

    public:
        const int mapFilePointerSize = 2;

        const int randomBytesInObjectId = 1;
        const int timeBytesInObjectId = 1;
        const int counterBytesInObjectId = 1;
    };
} // namespace CustomClasses

#endif