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
    return ((hasher(key) * 2654435769u) >> shift) & (tableSize - 1);
}

void FiboHashTable::insert(const string &key, int value)
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
    numElements -= (before - bucket.size());
}

int countTrailingZeros(unsigned int n)
{
    if (n == 0) return 32;
    int count = 0;
    while ((n & 1) == 0)
    {
        n >>= 1;
        count++;
    }
    return count;
}

void FiboHashTable::rehash()
{
    int oldTableSize = tableSize;
    tableSize *= 2;
    shift = 32 - countTrailingZeros(tableSize);
    vector<list<pair<string, int>>> newTable(tableSize);

    for (const auto &bucket : table)
    {
        for (const auto &p : bucket)
        {
            unsigned int newIndex = ((std::hash<string>{}(p.first) * 2654435769u) >> shift) & (tableSize - 1);
            newTable[newIndex].push_back(p);
        }
    }
    table.swap(newTable);
}

int FiboHashTable::getElementCount() const
{
    return numElements;
}

double FiboHashTable::getLoadFactor() const
{
    return static_cast<double>(numElements) / tableSize;
}

double FiboHashTable::getAverageChainLength() const
{
    int nonEmpty = 0;
    for (const auto &bucket : table)
    {
        if (!bucket.empty())
            nonEmpty++;
    }
    return nonEmpty ? static_cast<double>(numElements) / nonEmpty : 0.0;
}

int FiboHashTable::getMaxChainLength() const
{
    int maxLen = 0;
    for (const auto &bucket : table)
    {
        if (bucket.size() > maxLen)
            maxLen = bucket.size();
    }
    return maxLen;
}
