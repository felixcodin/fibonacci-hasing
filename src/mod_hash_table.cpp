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
    numElements++;
    
    if (static_cast<double>(numElements) / tableSize > LOAD_FACTOR)
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
    bucket.remove_if([&](auto &p) { return p.first == key; });
    numElements -= (before - bucket.size());
}

void ModHashTable::rehash()
{
    int oldTableSize = tableSize;
    tableSize *= 2;
    vector<list<pair<string, int>>> newTable(tableSize);

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

int ModHashTable::getElementCount() const
{
    return numElements;
}

double ModHashTable::getLoadFactor() const
{
    return static_cast<double>(numElements) / tableSize;
}

double ModHashTable::getAverageChainLength() const
{
    int nonEmpty = 0;
    for (const auto &bucket : table)
    {
        if (!bucket.empty())
            nonEmpty++;
    }
    return nonEmpty ? static_cast<double>(numElements) / nonEmpty : 0.0;
}

int ModHashTable::getMaxChainLength() const
{
    int maxLen = 0;
    for (const auto &bucket : table)
    {
        if (bucket.size() > maxLen)
            maxLen = bucket.size();
    }
    return maxLen;
}