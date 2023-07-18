// Time complexity :
// get() : O(1)
// put() : O(1)
// Space complexity :
// O(lru cache capacity)

// Problem description is an incorrect cluster-f**.
// LRU "Least Recently Used" implies keys which were accessed the earliest are the LRU keys
// instead of following:-
// "Least Recently Used" requires a use count to be associated with each key 
// Both the implementations/design are poles apart

class LRUCache {
public:
    
    // Entry in LRU cache for a particular key
    typedef struct _KeyCacheDataT {
        // Value associated with key
        int val;
        // pointer to the key entry in the LRU list
        list<int>::iterator lruListKeyElemPtr;
    } KeyCacheDataT;

    LRUCache(int capacity) {
        _capacity = capacity;
    }
    
    int
    get(int key) {
        // Locate presence of key in cache
        auto iter = _keyToCacheTbl.find(key);
        if (iter == _keyToCacheTbl.end()) {
            // Key not present
            return -1;
        }
        
        // Key present in cache. Get the entry associated with key
        auto & keyCacheData = iter->second;
        auto & keyPtrInLruList = keyCacheData.lruListKeyElemPtr;
        
        // Update the key location in LRU list as it has been recently accessed
        keyPtrInLruList = 
            addRecentlyAccessedKeyToList(key, keyPtrInLruList, true);
        
        return keyCacheData.val;
    }
    
    void
    put(int key, int value) {
        // Locate presence of key in cache
        auto iter = _keyToCacheTbl.find(key);
        
        if (iter != _keyToCacheTbl.end()) {
            // Key present in cache. Get the entry associated with key
            auto & keyCacheData = iter->second;
            // Update the value associate with the key
            keyCacheData.val = value;            
            auto & keyPtrInLruList = keyCacheData.lruListKeyElemPtr;
            
            // Update the key location in LRU list as it has been recently accessed
            keyPtrInLruList = 
                addRecentlyAccessedKeyToList(key, keyPtrInLruList, true);
            
        } else {
            
            // Key not present in cache. New to create a new LRU entry for key
            if (_keyToCacheTbl.size() == _capacity) {
                // Cache is full. So evict the oldest entry
                evictOldestEntry();
            }
 
            // Insert new key entry in cache and list
            addNewLRUEntry(key, value);
        }
    }
    
private:
    
    inline list<int>::iterator
    addRecentlyAccessedKeyToList(int key,
        list<int>::iterator keyPrevPtr = list<int>::iterator(),
        bool keyPresentEarlier = false) {
        
        // Add LRU key to the front of list
        _lruKeysList.push_front(key);

        if (keyPresentEarlier) {
            // Key was already in cache. Remove its marker from earlier position
            // in the list to avoid duplication
            _lruKeysList.erase(keyPrevPtr);
        }
        
        // Return a ptr to the location of LRU key
        return _lruKeysList.begin();
    }
    
    inline void
    evictOldestEntry() {
        // Oldest key is always at back of LRU list
        auto oldestKey = _lruKeysList.back();
        // Remove oldest key from list
        _lruKeysList.pop_back();
        // Remove oldest entry from cache
        _keyToCacheTbl.erase(oldestKey);
    }
    
    inline void
    addNewLRUEntry(int key, int value) {
        // Create entry for specified key
        KeyCacheDataT keyCacheData;
        keyCacheData.val = value;
        // Add the key to LRU list
        keyCacheData.lruListKeyElemPtr = 
            addRecentlyAccessedKeyToList(key);
        // Add the new entry associated with the key to the cache
        _keyToCacheTbl[key] = keyCacheData;
    }
    
    // Data members
    int _capacity;
    // Hash table mapping between a key stored in the cache to its respective value
    // and location in the access ordered LRU linked list 
    unordered_map<int, KeyCacheDataT> _keyToCacheTbl;
    // Linked list of keys currently stored in the cache ordered as per their access times
    // Keys which were accessed earlier are situated towards the list tail compared to those
    // keys which are accessed later. So the LRU list always has the recently accessed/used
    // key at list front at all times
    list<int> _lruKeysList;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
