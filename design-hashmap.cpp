// n => total number of all possible keys stored
// b => num predefined buckets
// k => num unique keys
// Time complexity : O(n / b)
// Space complexity : O(b + k)

#define _BUCKETS_AS_LIST_

#ifdef _BUCKETS_AS_BST_

class Bucket {
public:
    void
    insert(int k, int v) {
        // Insert/update value against specified key in BST
        _itemsTbl[k] = v;
    }
    
    int
    get(int k) {
        // Lookup key entry in BST
        map<int, int>::iterator it = _itemsTbl.find(k);
        if (it == _itemsTbl.end()) {
            // Key not found
            return -1;
        }
        // Return value against specified key in BST
        return it->second;
    }
    
    void
    remove(int k) {
        // Lookup key entry in BST
        map<int, int>::iterator it = _itemsTbl.find(k);
        if (it == _itemsTbl.end()) {
            // Key not found
            return;
        }
        // Remove entry against specified key from BST
        _itemsTbl.erase(it);
    }
    
private:
    
    // <key, value> pairs stored as a BST/Rb tree
    map<int, int> _itemsTbl;
};

#endif


#ifdef _BUCKETS_AS_LIST_

class Bucket {
public:
    void
    insert(int k, int v) {
        // Iterate through all list entries in current bucket
        for (auto & le : _itemsList) {
            if (le.first == k) {
                // List entry for given key found
                // Update value for specified key and return
                le.second = v;
                return;
            }
        }
        
        // List entry not found for given key. Add new key/value entry to list
        _itemsList.emplace_front(pair<int, int>(k, v));
    }
    
    int
    get(int k) {
        // Iterate through all list entries in current bucket
        for (auto & le : _itemsList) {
            if (le.first == k) {
                // List entry for given key found. Return value against key
                return le.second;
            }
        }
        // List entry not found for given key
        return -1;
    }
    
    void
    remove(int k) {
        // Iterate through all list entries in current bucket
        list<pair<int, int> >::iterator it = _itemsList.begin();
        list<pair<int, int> >::iterator endIt = _itemsList.end();
        while (it != endIt) {
            if (it->first == k) {
                // List entry for given key found
                // Detele entry and return
                _itemsList.erase(it);
                return;
            }
            ++it;
        }
    }
    
private:
    
    // <key, value> pairs stored as a list of pairs per bucket
    list<pair<int, int> > _itemsList;
};

#endif

class MyHashMap {
public:
    MyHashMap() {
        // Initailized to a prime number l.e. 10^6
        _nBuckets = 967;//769;
        _hashTbl.resize(_nBuckets);
    }
    
    void
    put(int key, int value) {
        // Get the bucket id for given key using hash function and
        // add the <key, value> pair to appropriate bucket
        size_t bId = bucketId(key);
        _hashTbl[bId].insert(key, value);
    }
    
    int
    get(int key) {
        // Get the bucket id for given key using hash function and
        // return the value for given key from appropriate bucket
        size_t bId = bucketId(key);
        return _hashTbl[bId].get(key);
    }
    
    void
    remove(int key) {
        // Get the bucket id for given key using hash function and
        // Remove given key entry from appropriate bucket if it exists
        size_t bId = bucketId(key);
        return _hashTbl[bId].remove(key);
    }
    
private:
    
    inline size_t
    bucketId(int key) {
        return key % _nBuckets;
    }
    
    // Data members
    // Hash map is implemented as an array of buckets. Each <key, value> pair
    // is hashed into a bucket using a hash function on the key. Each bucket
    // can be implemented as a BST of <key, value> pairs or a linked list
    // of <key, value> pairs
    vector<Bucket> _hashTbl;
    size_t _nBuckets;
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
