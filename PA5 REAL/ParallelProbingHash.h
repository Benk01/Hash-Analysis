#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>

#include "Hash.h"

using std::vector;
using std::pair;

// Can be used for tracking lazy deletion for each element in your table
enum EntryState {
    EMPTY = 0,
    VALID = 1,
    DELETED = 2
};

template<typename K, typename V>
class ProbingHash : public Hash<K, V> { // derived from Hash
private:
    // Needs a table and a size.
    // Table should be a vector of std::pairs for lazy deletion
    vector<pair<K, V>> table;
    int numEntries;
    int numBuckets;
    vector<EntryState> entryStateVector;

public:
    ProbingHash(int n = 11) {
        numBuckets = n;
        table.resize(numBuckets);
        entryStateVector.resize(numBuckets);
        for (int i = 0; i < numBuckets; i++) {
            entryStateVector[i] = EMPTY;
        }
    }

    ~ProbingHash() {
        // Needs to actually free all table contents
    }

    bool empty() {
        return numEntries == 0;
    }

    int size() {
        return numEntries;
    }

    V& at(const K& key) {
        int index = hash(key);
        if (entryStateVector[index] == VALID) {
            return table[index].second;
        }
        V ret = -1;
        return ret;
    }

    V& operator[](const K& key) {
        return at(key);
    }

    int count(const K& key) {
        int index = hash(key);
        if (entryStateVector[index] == VALID) {
            return 1;
        }
        return 0;
    }

    void emplace(K key, V value) {
        pair<K, V> newPair;
        newPair.first = key;
        newPair.second = value;
        insert(newPair);
    }

    void insert(const std::pair<K, V>& pair) {
        int index = hash(pair.first);
        while (entryStateVector[index] == VALID) {
            if (table[index].first == pair.first) {
                table[index] = pair;
                return;
            }
            index++;
        }

        if (load_factor() > 0.75) {
            rehash();
        }
        entryStateVector[index] = VALID;
        table[index] = pair;
        numEntries++;
    }

    void erase(const K& key) {
        int index = hash(key);
        if (table[index].first == key && entryStateVector[index] == VALID) {
            numEntries--;
            entryStateVector[index] = DELETED;
        }
    }

    void clear() {
        table.clear();
        entryStateVector.clear();
        numBuckets = 0;
        numEntries = 0;
    }

    int bucket_count() {
        return numBuckets;
    }

    int bucket_size(int n) {
        if (entryStateVector[n] == VALID)
            return 1;
        return 0;
    }

    int bucket(const K& key) {
        int index = hash(key);
        return index;
    }

    float load_factor() {
        float lf;
        lf = float(numEntries);
        lf = lf / (float)numBuckets;
        return lf;
    }

    void rehash() {
        rehash(2 * (findNextPrime(numBuckets)) + 1);
    }

    void rehash(int n) {
        auto oldTable = table;
        auto oldState = entryStateVector;
        int newTableSize = n;
        numBuckets = newTableSize;
        table.resize(newTableSize);
        entryStateVector.resize(newTableSize);
        for (int i = 0; i < numBuckets; i++)
            entryStateVector[i] = EMPTY;

        for (int j = 0; j < oldTable.size(); j++) {
            if (oldState[j] == VALID) {
                auto itr = oldTable[j];
                insert(itr);
            }
        }
    }

private:
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    int hash(const K& key) {
        return key % numBuckets;
    }

};

#endif //__PROBING_HASH_H
