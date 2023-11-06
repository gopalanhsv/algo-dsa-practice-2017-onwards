// Space complexity : O(n) 

// Constructor
// Time complexity : O(nlogn)

// reserve() / unreserve()
// Time complexity : O(logn)

class SeatManager {
public:
    SeatManager(int n) {
        // Add all the available seats to min heap
        for (auto sId = 1; sId <= n; ++sId) {
            _minHeap.push(sId);
        }
    }
    
    int
    reserve() {
        if (_minHeap.empty()) {
            // Free seats are unavailable
            return -1;
        }
        
        // Get the lowest numbered free seat and reserve it
        auto sId = _minHeap.top();
        _minHeap.pop();
        _reservedSeatsTbl.insert(sId);
        return sId;
    }
    
    void
    unreserve(int seatNumber) {
        auto iter = _reservedSeatsTbl.find(seatNumber);
        if (iter == _reservedSeatsTbl.end()) {
            // Specified seat number was either freed earlier or out of range
            return;
        }
        
        // Return the given seat to available seat pool
        _reservedSeatsTbl.erase(iter);
        _minHeap.push(seatNumber);
    }
    
private:
    
    // Data members
    // Priority Q/min heap pool of available unreserved seats
    // (smaller valued seats are at top of Q compared to larger valued seats)
    priority_queue<int, vector<int>, greater<int> > _minHeap;
    // Hash table of reserved seat values
    unordered_set<int> _reservedSeatsTbl;
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */
