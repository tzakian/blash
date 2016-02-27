# blash
Open hash table (separate chaining) with a bloom filter for quick checking of membership in chains.

# Why blash?
There are of course many different types of hash table implementations out
there. This seeks to solve the case where the key values for our hash table
incur costly comparisons (and are therefore usually quite large). To solve this, we use
bloom filters to track membership in the chains for a given hash bucket. We
decided to use open hashing as opposed closed hashing since for large
objects, open hashing is usually (...) more efficient then closed hashing.

# Possible cool extensions:
Try to use the fact that if we can guarantee a uniform collision pattern in
the hash table coupled with the hashing in the bloom filter to try and do a
version of double hashing on the chain (i.e., the bloom filter hash will
also serve to guide our search in the chain as well).

# Why is this better than the other types of hash tables?
Beats me. I just thought this would be cool.
