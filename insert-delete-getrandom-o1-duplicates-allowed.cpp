// Time complexity :
// insert() : O(1) per call
// remove() : O(1) per call
// getRandom() : O(1) per call
// Space complexity : O(n), n => number of elements inserted so far

class RandomizedCollection {
public:
    RandomizedCollection() {
        _randEng.seed(time(0));
    }
    
    bool
    insert(int val) {
        bool elemNotPresentEarlier = true;
        if (_elemToArrIndicesTbl.find(val) != _elemToArrIndicesTbl.end()) {
            // Element already present
            elemNotPresentEarlier = false;
        }
        
        // Insert element
        // Add the element to end of vector
        _elemsV.emplace_back(val);
        // Add the element location in the vector to hash table
        _elemToArrIndicesTbl[val].insert(_elemsV.size() - 1);
        return elemNotPresentEarlier;
    }
    
    bool
    remove(int val) {
        auto iter = _elemToArrIndicesTbl.find(val);
        if (iter == _elemToArrIndicesTbl.end()) {
            // Element not present
            return false;
        }    
        
        // Locations where the element in stored in vector
        auto & indices = iter->second;
        
        // Last element located at end of vector
        int lastElemIdx = _elemsV.size() - 1;
        int lastElem = _elemsV[lastElemIdx];
        if (lastElem == val) {
            // Value of Last element in the array is identical to that of element being removed
            // => Remove the last element in array and remove the corresponding entry in the
            // hash table
            _elemsV.pop_back();
            indices.erase(lastElemIdx);
            if (indices.empty()) {
                _elemToArrIndicesTbl.erase(iter);
            }
        } else {
            // Last element in the array is not identical to the element to be removed
            // => Swap the locations of last element and an instance of element to be removed 
            // Then remove the element to be removed from the array end
            auto idxOfElemToBeRemoved = *(indices.begin());
            // Move the last element to location of element to be removed
            auto & lastElemIndices = _elemToArrIndicesTbl[lastElem];
            lastElemIndices.erase(lastElemIdx);
            lastElemIndices.insert(idxOfElemToBeRemoved);
            _elemsV[idxOfElemToBeRemoved] = lastElem;
            // Remove the element to be removed (from array end)
            _elemsV.pop_back();
            indices.erase(idxOfElemToBeRemoved);
            if (indices.empty()) {
                _elemToArrIndicesTbl.erase(iter);
            }
        }
        
        return true;
    }
    
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
    
    // Hash table mapping element in the set of locations in vector where element is stored
    unordered_map<int, unordered_set<int> > _elemToArrIndicesTbl;
    
    // Vector/array holding all the inserted elements which yet to be removed
    vector<int> _elemsV;

    // Random number generator
    default_random_engine _randEng;
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
