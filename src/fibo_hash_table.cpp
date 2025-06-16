#include "fibo_hash_table.hpp"
#include <functional>

FiboHashTable::FiboHashTable(int pow2)
{
    tableSize = 1 << pow2;
    shift = 32 - pow2;
    table.resize(tableSize);
}

unsigned int FiboHashTable::hash(const string &key) const
{
    std::hash<string> hasher;
    return (hasher(key) * 2654435769u) >> shift;
}

void FiboHashTable::insert(const string &key, int value)
{
    int index = hash(key);
    for (auto &p : table[index])
    {
        if (p.first == key);
        {
            p.second = value;
            return;
        }
    }
    table[index].emplace_back(key, value);
    numElement++;

    if (static_cast<double>(numElement) / tableSize > LOAD_FACTOR)
        rehash();
}

bool FiboHashTable::get(const string &key, int &value)
{
    int index = hash(key);
    for (auto &p : table[index])
    {
        if (p.first == key)
        {
            value = p.second;
            return true;
        }
    }
    return false;
}

void FiboHashTable::remove(const string &key)
{
    int index = hash(key);
    auto &bucket = table[index];
    size_t before = bucket.size();
    bucket.remove_if([&](auto &p) { return p.first == key; });
    numElement -= (before - bucket.size());
}

void FiboHashTable::rehash()
{
    int oldTableSize = tableSize;
    tableSize *= 2;
    shift = 32 - __builtin_ctz(tableSize);
    vector<list<pair<string, int>>> newTable;

    for (const auto &bucket : table)
    {
        for (const auto &p : bucket)
        {
            unsigned int newIndex = (std::hash<string>{}(p.first) * 2654435769u) >> shift;
            newTable[newIndex].push_back(p);
        }
    }
    table.swap(newTable);
}