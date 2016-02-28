// TODO: make pointers be unique and shared
#pragma once
#include "./cuckoofilter/src/cuckoofilter.h"
#include <iostream>
#include <vector>

namespace bloomhash {

  template<class KeyType,
    class  ValueType,
    class  Hash = std::hash<KeyType>,
    class  KeyEqual = std::equal_to<KeyType>,
    size_t numBitsToUse = 12,
    size_t defaultSize = 21>
      class BloomHash {
        private:
          // possible TODO: add in end-pointers here
          struct Node {
            KeyType key;
            ValueType val;
            Node* next;
            Node(const KeyType& key, const ValueType& val) : key(key), val(val), next(nullptr) {}
            Node() {}
          };

          Hash hasher;
          KeyEqual eq;

          std::vector<Node*> buckets;
          std::vector<cuckoofilter::CuckooFilter<KeyType, numBitsToUse>> filters;

          size_t size = defaultSize;
          size_t used = 0;

          void insertInChain(size_t index, const KeyType& key, const ValueType& val);
          void deleteInChain(size_t index, const KeyType& key);
          void rehashResize();
        public:
          typedef Node* Iter;
          BloomHash();
          // copy constr
          BloomHash(BloomHash& other);
          // move constr
          BloomHash(BloomHash&& other);
          // copy assignment
          BloomHash& operator=(BloomHash& other);
          // move assignment
          BloomHash& operator=(BloomHash&& other);
          // No virtual functions, so no need for this to be virtual
          ~BloomHash();
          void insert(const KeyType& key, const ValueType& val);
          //ValueType& find(const KeyType& key);
          auto find(const KeyType& key);
          void erase(const KeyType& key);
          // Find if the bucket contains anything
          // NOTE: probabilisit
          bool bucketContains(const KeyType& key);
      };
} // End bloomhash
