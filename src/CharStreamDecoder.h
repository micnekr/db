//
// Created by misha on 22/11/2020.
//

#ifndef DB_CHARSTREAMDECODER_H
#define DB_CHARSTREAMDECODER_H

#include "Config.h"

#include <cstdint>
#include <iostream>

namespace CustomClasses {
    enum CharStreamDecoderStates {
        InvalidData,
        ReadingLengthData,
        ReadingData
    };

    class CharStreamDecoder {
    public:
        CharStreamDecoderStates state = InvalidData;
        uint64_t charactersLeft = 0;
        uint64_t charactersLength = 0;
        int lengthCharsLeft = 0;
        int lengthBytesInDataRepresentation = -1;
        void next(unsigned char);
        void reset();
    };
}

#endif //DB_CHARSTREAMDECODER_H
