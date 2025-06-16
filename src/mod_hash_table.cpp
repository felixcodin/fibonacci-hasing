#include "mod_hash_table.hpp"
#include <functional>

ModHashTable::ModHashTable(int pow2)
{
    tableSize = 1 << pow2;
    table.resize(tableSize);
}

unsigned int ModHashTable::hash(const string &key) const
{
    std::hash<string> hasher;
    return hasher(key) & (tableSize - 1);
}

void ModHashTable::insert(const string &key, int value)
{
    int index = hash(key);
    for (auto &p : table[index])
    {
        if (p.first == key)
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

bool ModHashTable::get(const string &key, int &value)
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

void ModHashTable::remove(const string &key)
{
    int index = hash(key);
    auto &bucket = table[index];
    size_t before = bucket.size();
    bucket.remove_if(([&](auto &p) { return p.first == key; }));
    numElement -= (before - bucket.size());
}

void ModHashTable::rehash()
{
    int oldTableSize = tableSize;
    tableSize *= 2;
    vector<list<pair<string, int>>> newTable;

    for (const auto &bucket : table)
    {
        for (const auto &p : bucket)
        {
            unsigned int newIndex = std::hash<string>{}(p.first) & (tableSize - 1);
            newTable[newIndex].push_back(p);
        }
    }
    table.swap(newTable);
}