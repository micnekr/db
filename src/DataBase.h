#ifndef DATABASE_H // include guard
#define DATABASE_H

#include "dataTypes/IdComponent.h"
#include "dataTypes/NullComponent.h"
#include "dataTypes/NumberComponent.h"
#include "Table.h"
#include "Token.h"
#include "MapFile.h"
#include "CharStreamDecoder.h"
#include <iostream>
#include <string>
#include <vector>
#include <system_error>
#include <stdint.h>
#include <typeindex>

namespace CustomClasses {
    class Table;

    class DataBase : public IdComponent {
    public:
        //TODO: move some functionality to the table class
        DataBase(std::string, std::string, std::string, int, int);

        DataBase() = delete;

        std::string name;
        MapFile *primaryMap;
        MapFile *secondaryMap;
        CharStreamDecoder *charStreamDecoder;

        std::list<TombIndex *> *tombstones;

        void createTable(const std::string &);

        void updateTombstones() const;

        std::list<TombIndex *>::iterator findSuitableTombIndexIterator(uint64_t, TombIndexSearchTypes) const;

        void storePrimaryAndSecondaryMap(std::vector<unsigned char> *, Component *, Component *);
        void store(Component *, Component *);

        Component *searchPrimaryAndSecondaryMap(std::vector<unsigned char> *, Component *) const;

        Component *search(Component *) const;

        std::vector<unsigned char> *getPrimaryMapIndex(Component *) const;

        static std::vector<unsigned char> *serialiseSecondaryMapEntry(Component *, Component *);

        static std::unordered_map<unsigned char, std::type_index> binToTypeRepresentations;
        static std::unordered_map<std::type_index, unsigned char> typeToBinRepresentations;
        static bool haveTypeBinaryRepresentationsBeenSet;

    private:
        static void serialiseComponent(std::vector<unsigned char> *, Component *component);
    };
}

#endif