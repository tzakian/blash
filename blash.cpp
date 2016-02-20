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
      // TODO: try to make this whole thing re-use the pre-existing memory
      // that we have already allocated for @buckets and @filters
      Node* newHash = calloc(sizeof(Node), newSize);
      // Chains are getting moved around so we need to re-do our filters
      cuckoofilter::CuckooFilter<KeyType, numBitsToUse>* newFilters = calloc(sizeof(cuckoofilter::CuckooFilter<KeyType, numBitsToUse>), newSize);

      // Go through our old buckets and filters
      for (int i = 0; i < size; ++i) {
        // Nodes get reused
        Node* chain = buckets[i];
        // Filters on the other hand do not. So free the filter
        delete filters[i];
        // Go through our chain and re-hash them
        while (chain) {
          Node* tmp = chain->next;
          // Evict from chain
          chain->next = nullptr;
          // Get it's new hash
          size_t newHsh = hasher(chain->key) % newSize;
          // If it collides
          if (newHash[newHsh] != nullptr) { // collision
            // Go down that chain and insert it
            // FYI: if it collides, we will already be there, so we don't
            // need to add a new filter.
            chain->next = newHash[newHsh];
            newHash[newHsh] = chain;
          } else {
            // No collision, so we simply add it. Also since we're updating
            // (i.e. re-doing) the filters, we need to create one here
            newHash[newHsh] = chain;
            newFilters[newHash] = new cuckoofilter::CuckooFilter<KeyType, numBitsToUse>();
          }
          newFilters[newHash].Add(chain->key);
          chain = tmp;
        }
      }
      // update size now
      size = newSize;

      // free our buckets
      free(buckets);
      // Now point them at the new one
      buckets = newHash;

      // free the filter-array memory
      free(filters);
      // Now point them at the new filters
      filters = newFilters;
    }

template<class KeyType,
  class ValueType,
  class Hash,
  class KeyEqual,
  size_t numBitsToUse,
  size_t defaultSize>
    void BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::deleteInChain(size_t idx, const KeyType& key) {
      // This returns cuckoofilter::Ok then there is a very strong
      // probability of it being in the chain so go searching for it. If it
      // returns something else, then it's definitely _not_ in the chain so
      // don't do anything
      if (filters[idx].Contain(key) == cuckoofilter::Ok) {
        // Note: don't delete till we _know_ it's in the chain -- the bloom
        // filter saying it's in the chain doesn't necessariy mean that it
        // actually is in the chain.

        // Grab the head of the chain
        Node* curr = buckets[idx];
        // Grab a prev pointer for eas-of-use
        Node* prev = nullptr;
        while (curr) {
          // Found it
          if (curr->key == key) {
            // So delete it from the filter
            filters[idx].Delete(key);
            // This was at the head of the chain. So simply replace what
            // the bucket points to as the head of the chain
            if (prev == nullptr) {
              buckets[idx] = curr->next;
            } else {
              // else have the pointers skip-over that node
              prev->next = curr->next;
            }
            // don't forget to be good and free the memory!
            delete curr;
            break;
          }
          // haven't found it yet -- keep searching!
          curr = curr->next;
        }
      }
    }

template<class KeyType,
  class ValueType,
  class Hash,
  class KeyEqual,
  size_t numBitsToUse,
  size_t defaultSize>
    bool BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::bucketContains(size_t idx, const KeyType& key) {

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


