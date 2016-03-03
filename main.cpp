// For testing
#include <iostream>
#include <fstream>
#include "./cuckoofilter/src/cuckoofilter.h"
#include "blash.hpp"

using cuckoofilter::CuckooFilter;
using bloomhash::BloomHash;
using namespace std;

/*
 *int main(void)
 *{
 *
 *  string s;
 *  size_t total_items  = 1000000;
 *  cin >> s;
 *  ifstream fin(s, ifstream::in);
 *  CuckooFilter<string, 12> filter(total_items);
 *
 *  size_t numInserted = 0;
 *  while (fin >> s && numInserted < total_items) {
 *    if (filter.Add(s) != cuckoofilter::Ok) {
 *      break;
 *    }
 *  }
 *
 *  fin.close();
 *
 *  while (true) {
 *    cout << "Enter a word to query: ";
 *    cin >> s;
 *
 *    if (filter.Contain(s) == cuckoofilter::Ok) {
 *      cout << endl << "Found word" << endl;
 *    } else {
 *      cout << endl << "Word not found" << endl;
 *    }
 *  }
 *
 *  return 0;
 *}
 *
 */

int main(void)
{
  bloomhash::BloomHash<string, string> hash;
  hash.insert("one", "two");
  hash.insert("one", "two");
  hash.insert("one", "two");
  hash.insert("three", "four");

  for (int i = 0; i < 30; ++i) {
    hash.insert(to_string(i), to_string(i+1));
  }

  cout << "----------------------" << endl;

  for (int i = 0; i < 35; ++i) {
    cout << hash.bucketContains(to_string(i)) << endl;
  }


  cout << "----------------------" << endl;
  auto t = hash.find("three");

  cout << t->val << endl;

  cout << "----------------------" << endl;
  hash.erase("three");
  t = hash.find("three");

  // this had better be null now!
  cout << t << endl;

  cout << "----------------------" << endl;
  hash.erase("10");
  t = hash.find("10");

  // this had better be null now!
  cout << t << endl;

  for (int i = 0; i < 30; ++i) {
    hash.erase(to_string(i));
  }

  // We seem to be getting more false-positives than I was expecting here.
  // Need to check and make sure that the logic is OK
  for (int i = 0; i < 35; ++i) {
    cout << hash.bucketContains(to_string(i)) << endl;
    cout << hash.find(to_string(i)) << endl;
  }

  return 0;
}
