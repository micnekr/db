#ifndef TOMB_INDEX_H // include guard
#define TOMB_INDEX_H

namespace CustomClasses{
    class MapFile;
    class TombIndex{
        public:
        MapFile* parent;

        int startIndex;
        int endIndex;

        TombIndex();
    };
}

#endif