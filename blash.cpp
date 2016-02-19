#include "blash.hpp"

namespace bloomhash {
  template<class KeyType,
    class  ValueType,
    class  Hash,
    class  KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      void BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::insertInChain(size_t idx, const KeyType& key, const ValueType& val) {
        // We will get a low set of false-positives here
        if (filters[idx].Contain(key) == cuckoofilter::Ok) { // it is _in_ the chain so we need to search through and updat the val
          Node* curr = buckets[idx];
          while (curr) {
            if (curr->key == key) {
              curr->val = val;
            }
          }
        } else { // not in the chain so add it at the beginning
          filters[idx].Add(key);
          Node* newStart = new Node();
          newStart->key = key;
          newStart->val = val;
          newStart->next = buckets[idx];
          buckets[idx] = newStart;
        }
      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      void BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::rehashResize() {
        size_t newSize = size * 2;
        Node* newHash = calloc(sizeof(Node), newSize);
        for (int i = 0; i < size; ++i) {
          newHash[hasher()]
        }
      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      void BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::deleteInChain(size_t idx, const KeyType& key) {

      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      bool BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::chainContains(size_t idx, const KeyType& key) {

      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::BloomHash() {

      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::BloomHash(BloomHash& other) {

      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::BloomHash(BloomHash&& other) {

      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>& BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::operator=(BloomHash& other) {

      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>& BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::operator=(BloomHash&& other) {

      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::~BloomHash() {

      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      void BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::insert(const KeyType& key, const ValueType& val) {

      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      void BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::erase(const KeyType& key) {

      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      ValueType& BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::find(const KeyType& key) {
        //BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::Iter
        //BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::find(const KeyType& key) {
      }
      }


