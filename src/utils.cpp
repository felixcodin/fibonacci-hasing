#include "utils.hpp"

random_device rd;
mt19937 gen(rd());

vector<string> generateRandomKeys(int count, int length = 8)
{
    uniform_int_distribution<> distrib('a', 'z');
    vector<string> keys;

    for (int i = 0; i < count; i++)
    {
        string s;
        for (int j = 0; j < length; j++)
        {
            s += static_cast<char>(distrib(gen));
        }
        keys.push_back(s);
    }
    return keys;
}

vector<string> generateSequentialKeys(int count)
{
    vector<string> keys;
    for (int i = 0; i < count; i++)
    {
        keys.push_back(to_string(i));
    }
    return keys;
}

vector<string> generateClusteredKeys(int count, int clusterSize)
{
    vector<string> keys;
    for (int i = 0; i < count; i++)
    {
        int cluster = i % clusterSize;
        keys.push_back("cluster" + to_string(cluster));
    }
    return keys;
}