#ifndef HASH_TABLE_BASE_HPP
#define HASH_TABLE_BASE_HPP

#include <string>
using namespace std;

class HashTableBase
{
    public:
        virtual void insert(const string &key, int value) = 0;
        virtual bool get(const string &key, int &value) = 0;
        virtual void remove(const string &key) = 0;

        virtual int getElementCount() const = 0;
        virtual double getLoadFactor() const = 0;
        virtual double getAverageChainLength() const = 0;
        virtual int getMaxChainLength() const = 0;

        virtual ~HashTableBase() = default;
};

#endif