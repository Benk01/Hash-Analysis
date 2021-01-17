/*
 *  Separate chaining hashtable
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

// Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;

//
// Separate chaining based hash table - derived from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K,V> {
private:
    vector<list<pair<K, V>>> table;
    int numEntries;
    int numBuckets;
public:
    ChainingHash(int n) {
        table.resize(n);
        numBuckets = n;
        numEntries = 0;
    }

    ~ChainingHash() {
        this->clear();
    }

    bool empty() {
        return numEntries == 0;
    }

    int size() {
        return numEntries;
    }

    V& at(const K& key) {
        int index = hash(key);
        list<pair<K, V>> individualList = table[index];
        typename list<pair<K, V>>::iterator itr;
        for (itr = individualList.begin(); itr != individualList.end(); ++itr) {
            if ((*itr).first == key)
                return (*itr).second;
        }

        V ret = -1;

        return ret;
    }
    

    V& operator[](const K& key) {
        return at(key);
    }

    int count(const K& key) {
        int sum = 0;
        int index = hash(key);
        list<pair<K, V>> individualList = table[index];
        typename list<pair<K, V>>::iterator itr;
        for (itr = individualList.begin(); itr != individualList.end(); ++itr) {
            if ((*itr).first == key)
                sum++;
        }
        return sum;
    }

    void emplace(K key, V value) {
        pair<K, V> newPair;
        newPair.first = key;
        newPair.second = value;
        insert(newPair);
    }

    void insert(const std::pair<K, V>& newPair) {
        int index = hash(newPair.first);
        table[index].push_back(newPair);
        numEntries++;

        if (load_factor() > 0.75) {
            rehash();
        }

    }

    void erase(const K& key) {
        int index = hash(key);
        list<pair<K, V>> individualList = table[index];
        typename list<pair<K, V>>::iterator itr;
        for (itr = individualList.begin(); itr != individualList.end(); ++itr) {
            if ((*itr).first == key) {
                table[index].clear();
                numEntries--;
            }
        }
    }

    void clear() {
        table.clear();
        numBuckets = 0;
        numEntries = 0;
    }

    int bucket_count() {
        return numBuckets;
    }

    int bucket_size(int n) {
        list<pair<K,V>> index = table[n];
        return index.size();
    }

    int bucket(const K& key) {
        int index = hash(key);
        list<pair<K, V>> individualList = table[index];
        typename list<pair<K, V>>::iterator itr;
        for (itr = individualList.begin(); itr != individualList.end(); ++itr) {
            if ((*itr).first == key)
                return index;
        }
        return -1;
    }

    float load_factor() {
        float lf;
        lf = float(numEntries);
        lf = lf / (float)numBuckets;
        return lf;
    }

    void rehash() {
        rehash(findNextPrime(2 * (numBuckets + 1)));
    }

    void rehash(int n) {
        auto oldTable = table;
        int newTableSize = n;
        numBuckets = newTableSize;
        table.resize(newTableSize);
        for (int i = 0; i < table.size(); i++)
            table[i].clear();

        numEntries = 0;
        for (int j = 0; j < oldTable.size(); j++) {
            typename list<pair<K, V>>::iterator itr = oldTable[j].begin();
            while (itr != oldTable[j].end())
                insert(*itr++);
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

#endif //__CHAINING_HASH_H
