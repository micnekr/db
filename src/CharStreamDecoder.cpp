//
// Created by misha on 22/11/2020.
//

#include "CharStreamDecoder.h"

using namespace CustomClasses;

void CharStreamDecoder::next(char c) {
    const char emptyChar = 0x00;

    //load length if not set
    if (lengthBytesInDataRepresentation == -1) lengthBytesInDataRepresentation = Config::getInstance().lengthBytesInDataRepresentation;

    if (state == ReadingLengthData) {
        //if still reading length bytes
        //shift a byte to the left
        charactersLength <<= 8;
        charactersLength += c;
        lengthCharsLeft--;
        if (lengthCharsLeft == 0) {
            state = ReadingData;
            charactersLeft = charactersLength;
        }
    } else if (state == ReadingData) {
        if(charactersLeft <= 0){
            state = InvalidData;
        }else{
            charactersLeft--;
        }
    }
    else if(state == InvalidData){
        //because the first bit of length is always 1, the first char can not be 0x00
        //check if starting valid data,
        if (c != 0x00) {
            state = ReadingLengthData;
            //7F = 0111 1111
            //remove the first bit
            lengthCharsLeft = lengthBytesInDataRepresentation - 1;
            charactersLength = 0x7F & c;
        }
    }
}

void CharStreamDecoder::reset() {
    state = InvalidData;
    charactersLeft = 0;
    charactersLength = 0;
    lengthCharsLeft = 0;
    lengthBytesInDataRepresentation = -1;
}
