#pragma once
#include "./cuckoofilter/src/cuckoofilter.h"
#include <iostream>

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
          };

          Node* buckets;
          size_t size = defaultSize;
          cuckoofilter::CuckooFilter<KeyType, numBitsToUse>* filters;

          void insertInChain(size_t index, const KeyType& key, const ValueType& val);
          void deleteInChain(size_t index, const KeyType& key);
          bool chainContains(size_t index, const KeyType& key);
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
          ValueType& find(const KeyType& key);
          //Iter find(const KeyType& key);
          void erase(const KeyType& key);
      };
} // End bloomhash
