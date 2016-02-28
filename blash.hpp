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

          size_t size = defaultSize;
          size_t used = 0;
          static constexpr size_t chainSize = 1024;

          std::vector<Node*> buckets;
          std::vector<cuckoofilter::CuckooFilter<KeyType, numBitsToUse>> filters =
            std::vector<cuckoofilter::CuckooFilter<KeyType, numBitsToUse>>(size,
              cuckoofilter::CuckooFilter<KeyType, numBitsToUse>(chainSize));


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
          auto find(const KeyType& key);
          void erase(const KeyType& key);
          // Find if the bucket contains anything
          // NOTE: probabilisit
          bool bucketContains(const KeyType& key);
      };

  template<class KeyType,
    class  ValueType,
    class  Hash,
    class  KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      void BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::insertInChain(size_t idx, const KeyType& key, const ValueType& val) {
        // We will get a low set of false-positives here
          std::cout << "IN insertInChain" << std::endl;
          // XXX: The filter is segfaulting
        if (filters[idx].Contain(key) == cuckoofilter::Ok) { // it is _in_ the chain so we need to search through and updat the val
          std::cout << "IN insertInChain" << std::endl;
          Node* curr = buckets[idx];
          while (curr) {
            if (eq(curr->key,key)) {
              curr->val = val;
            }
          }
        } else { // not in the chain so add it at the beginning
          std::cout << "IN insertInChain" << std::endl;
          filters[idx].Add(key);
          Node* newStart = new Node();
          newStart->key  = key;
          newStart->val  = val;
          newStart->next = buckets[idx];
          buckets[idx]   = newStart;
        }
        std::cout << "IN insertInChain" << std::endl;
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
        std::vector<Node*> newHash(newSize);
        // Chains are getting moved around so we need to re-do our filters
        std::vector<cuckoofilter::CuckooFilter<KeyType, numBitsToUse>> newFilters(newSize,
            cuckoofilter::CuckooFilter<KeyType, numBitsToUse>(chainSize));

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
            } // end if

            newFilters[newHash].Add(chain->key);
            chain = tmp;

          } // end while
        }

        // update size now
        size = newSize;

        // Now point them at the new one
        buckets = newHash;

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
            if (eq(curr->key, key)) {
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
      // VERY similar to deleteInChain
      bool BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::bucketContains(const KeyType& key) {
        size_t idx = hasher(key) % size;
        // This returns cuckoofilter::Ok then there is a very strong
        // probability of it being in the chain so go searching for it. If it
        // returns something else, then it's definitely _not_ in the chain so
        // simply return false.
        if (filters[idx].Contain(key) == cuckoofilter::Ok) {
          // probabilistic! This gives a high certainting that something with
          // that key is in the bucket but it need not be the case (but this
          // is _highly_ unlikely).
          return true;
        } else {
          return false;
        }
      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      // We lazily allocate filters
      BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::BloomHash() : buckets(defaultSize) {
       // for (auto filt : filters) {
       //   filt = cuckoofilter::CuckooFilter<KeyType, numBitsToUse>(chainSize);
       // }
      }
  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      // REMEMBER: we create filters lazily!
      BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::BloomHash(BloomHash& other) {
        // State that needs to be copied:
        // * size of buckets -- DONE
        // * each node in the table -- DONE
        // * filters -- How to copy these? -- just create a new one and add -- DONE
        // * size -- DONE
        filters = std::vector<cuckoofilter::CuckooFilter<KeyType, numBitsToUse>>(other.size,
            cuckoofilter::CuckooFilter<KeyType, numBitsToUse>(chainSize));
        buckets = std::vector<Node*>(other.size);

        size = other.size;

        for (int i = 0; i < size; ++i) {
          // Copy the chain
          if (other.buckets[i] != nullptr) {
            Node* curr = other.buckets[i];

            // Add the data in
            filters[i].Add(curr->key);

            // Setup the head
            Node* newNode = new Node(curr->key, curr->val);
            buckets[i] = newNode;
            curr = curr->next;

            while (curr) {
              filters[i].Add(curr->key);
              Node* newNodeNext = new Node(curr->key, curr->val);
              newNode->next = newNodeNext;
              newNode = newNode->next;
            }
          }
        }
      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      // TODO: we should have unique_ptrs, and we should do move's here. As
      // is THIS IS UNSAFE AND WRONG
      BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::BloomHash(BloomHash&& other) {
        filters = other.filters;
        buckets = other.buckets;
        size    = other.size;
      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>&
      BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::operator=(BloomHash& other) {

        BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize> ret;

        // State that needs to be copied:
        // * size of buckets -- DONE
        // * each node in the table -- DONE
        // * filters -- How to copy these? -- just create a new one and add -- DONE
        // * size -- DONE
        ret.filters = std::vector<cuckoofilter::CuckooFilter<KeyType, numBitsToUse>>(other.size,
            cuckoofilter::CuckooFilter<KeyType, numBitsToUse>(chainSize));
        ret.buckets = std::vector<Node*>(other.size);

        ret.size = other.size;

        for (int i = 0; i < size; ++i) {
          // Copy the chain
          if (other.buckets[i] != nullptr) {
            Node* curr = other.buckets[i];

            // Add the data in
            ret.filters[i].Add(curr->key);

            // Setup the head
            Node* newNode = new Node(curr->key, curr->val);
            ret.buckets[i] = newNode;
            curr = curr->next;

            while (curr) {
              ret.filters[i].Add(curr->key);
              Node* newNodeNext = new Node(curr->key, curr->val);
              newNode->next = newNodeNext;
              newNode = newNode->next;
            }
          }
        }
        return ret;
      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>&
      BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::operator=(BloomHash&& other) {

        BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize> ret;
        ret.filters = other.filters;
        ret.buckets = other.buckets;
        ret.size    = other.size;
      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::~BloomHash() {
        // all the other stuff will (/should) be deleted by the C++ MM
        for (Node* bucket : buckets) {
          while (bucket) {
            Node* nxt = bucket->next;
            delete bucket;
            bucket = nxt;
          }
        }
      }


  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      void BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::insert(const KeyType& key, const ValueType& val) {
        insertInChain(hasher(key) % size, key, val);
      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      void BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::erase(const KeyType& key) {
        deleteInChain(hasher(key) % size, key);
      }

  template<class KeyType,
    class ValueType,
    class Hash,
    class KeyEqual,
    size_t numBitsToUse,
    size_t defaultSize>
      //Ick! uaing auto so I don't get complained at by the type system. For
      //some reason the class isn't exposing the typedef from inside the
      //class even though it's public.
      auto BloomHash<KeyType, ValueType, Hash, KeyEqual, numBitsToUse, defaultSize>::find(const KeyType& key) {
        size_t hsh = hasher(key) % size;
        Node* bucket = nullptr;
        if (filters[hsh].Contain(key)) {
          bucket = buckets[hsh];
          while (bucket) {
            if (eq(bucket->key, key)) {
              break;
            } else {
              bucket = bucket->next;
            }
          }
        }
        return bucket;
      }
} // End bloomhash
