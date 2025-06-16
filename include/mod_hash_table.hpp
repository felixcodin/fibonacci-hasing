#ifndef MOD_HASH_TABLE_HPP
#define MOD_HASH_TABLE_HPP

#include "hash_table_base.hpp"
#include <vector>
#include <list>

class ModHashTable : public HashTableBase
{
public:
    ModHashTable(int pow2);
    void insert(const string &key, int value) override;
    bool get(const string &key, int &value) override;
    void remove(const string &key) override;

private:
    int tableSize;
    int numElements = 0;
    static constexpr double LOAD_FACTOR = 0.75;
    vector<list<pair<string, int>>> table;
    unsigned int hash(const string &key) const;

    int getElementCount() const override;
    double getLoadFactor() const override;
    double getAverageChainLength() const override;
    int getMaxChainLength() const override;

    void rehash();

};

#endif