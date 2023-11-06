// n => Net numbers stored in system

// Space complexity : O(n)

// change()
// Time complexity : O(logn)
// find()
// Time complexity : O(logn)

class NumberContainers {
public:
    NumberContainers() {
        
    }
    
    void
    change(int index, int number) {
        auto iter = _idxToNumTbl.find(index);
        if (iter != _idxToNumTbl.end()) {
            // Number stored against given index
            auto oldNumAtIdx = iter->second;
            if (oldNumAtIdx == number) {
                // No change in number stored against given index
                return;
            }

            // Decrement an instance of earlier stored number against the index
            auto & oldNumIndices = _numToIndicesTbl[oldNumAtIdx];
            oldNumIndices.erase(index);
            if (oldNumIndices.empty()) {
                // All instances of earlier stored number against index becom zilch
                // => Remove earlier stored number from system
                _numToIndicesTbl.erase(oldNumAtIdx);
            }
        }
        
        // Update the storage system with new number at given index
        _idxToNumTbl[index] = number;
        // Update/add the index for stored number in system
        _numToIndicesTbl[number].insert(index);
    }
    
    int
    find(int number) {
        auto iter = _numToIndicesTbl.find(number);
        if (iter == _numToIndicesTbl.end()) {
            // No instance of number stored in system
            return -1;
        }
        // List of Indices at which number is stored in system
        auto & indicesSet = iter->second;
        // Return smallest index
        return *(indicesSet.begin());
    }
    
private:
    
    // Data members
    // Hash table mapping indices to numbers
    unordered_map<int, int> _idxToNumTbl;
    // Hash table mapping a number to the set of indices at which the number is stored
    // in system. Indices are stored using a RB tree in ascending order
    unordered_map<int, set<int> > _numToIndicesTbl;
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */
