// Time complexity :
// insert() : O(1) per call
// remove() : O(1) per call
// getRandom() : O(1) per call
// Space complexity : O(n), n => number of elements inserted so far

class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() { 
        _randEng.seed(time(0));
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool
    insert(int val) {
        if (_elemToVecIdxTbl.find(val) !=
            _elemToVecIdxTbl.end()) {
            // Element already present
            return false;
        }
        
        // Insert element
        // Add the element to end of vector
        _elemsV.emplace_back(val);
        // Add the element to hash table along with its
        // location in the vector
        _elemToVecIdxTbl[val] = _elemsV.size() - 1;

        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool
    remove(int val) {
        auto iter = _elemToVecIdxTbl.find(val);
        if (iter == _elemToVecIdxTbl.end()) {
            // Element not present
            return false;
        }    
        
        // Location where element in stored in vector
        auto idxOfElemToBeRemoved = iter->second;
        
        // Swap the element at end of vector with element to be removed
        int lastElem = _elemsV.back();
        _elemToVecIdxTbl[lastElem] = idxOfElemToBeRemoved;
        _elemsV[idxOfElemToBeRemoved] = lastElem;
        
        // Remove the element to be removed (from end of array)
        _elemsV.pop_back();
        _elemToVecIdxTbl.erase(iter);
        
        return true;
    }
    
    /** Get a random element from the set. */
    int
    getRandom() {
    
        // Generate a uniform random number in the range of indices of elements stored in array
        uniform_int_distribution<int> ud(0, _elemsV.size() - 1);
        auto idx = ud(_randEng);
        // Return the element stored in that index
        return _elemsV[idx];
    }
    
private:
    
    // Data members
    
    // Hash table mapping element in the set to location in
    // vector where element is stored
    unordered_map<int, int> _elemToVecIdxTbl;
    
    // Vector/array holding all the inserted elements which yet to be removed
    vector<int> _elemsV;

    // Random number generator
    default_random_engine _randEng;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
