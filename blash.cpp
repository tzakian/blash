#include "blash.hpp"

namespace bloomhash {
  template<class KeyType,
    class  ValueType,
    class  Hash,
    class  KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      void BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::insertInChain(size_t idx, const KeyType& key, const ValueType& val) {

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


