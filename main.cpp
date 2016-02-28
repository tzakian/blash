// For testing
#include <iostream>
#include <fstream>
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
 */

int main(void)
{
  bloomhash::BloomHash<string, string> hash;
  return 0;
}
