#include <iostream>
#include "fibo_hash_table.hpp"
#include "mod_hash_table.hpp"
#include "utils.hpp"
using namespace std;

void benchmark(HashTableBase& table, const vector<string>& keys, const string& label) 
{
    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < keys.size(); ++i) 
    {
        table.insert(keys[i], static_cast<int>(i));
    }
    
    cout << "=== Benchmark: " << label << " ===\n";
    cout << "Load factor: " << table.getLoadFactor() << '\n';
    cout << "Avg chain length: " << table.getAverageChainLength() << '\n';
    cout << "Max chain length: " << table.getMaxChainLength() << "\n";
    
    for (const auto& key : keys) 
    {
        int val;
        table.get(key, val);
    }
    
    for (const auto& key : keys) 
    {
        table.remove(key);
    }
    auto end = chrono::high_resolution_clock::now();
    
    double time_ms = chrono::duration<double, milli>(end - start).count();
    cout << "Execution time: " << time_ms << " ms\n\n";

}

int main() 
{
    const int count = 5000;
    const int tablePower = 10;

    // === Random keys ===
    vector<string> randomKeys = generateRandomKeys(count);
    FiboHashTable fiboRand(tablePower);
    ModHashTable modRand(tablePower);
    benchmark(fiboRand, randomKeys, "Fibonacci Hashing (Random)");
    benchmark(modRand, randomKeys, "Modulo Hashing (Random)");

    // === Sequential keys ===
    vector<string> seqKeys = generateSequentialKeys(count);
    FiboHashTable fiboSeq(tablePower);
    ModHashTable modSeq(tablePower);
    benchmark(fiboSeq, seqKeys, "Fibonacci Hashing (Sequential)");
    benchmark(modSeq, seqKeys, "Modulo Hashing (Sequential)");

    // === Clustered keys ===
    vector<string> clusterKeys = generateClusteredKeys(count, 100);
    FiboHashTable fiboClus(tablePower);
    ModHashTable modClus(tablePower);
    benchmark(fiboClus, clusterKeys, "Fibonacci Hashing (Clustered)");
    benchmark(modClus, clusterKeys, "Modulo Hashing (Clustered)");

    return 0;
}