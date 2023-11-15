// M => num calls, n => size/window capacity

// Time complexity :
// Constructor : O(n)
// next() : O(M)
// Space complexity : O(n)

class MovingAverage {
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        _qCapacity = size;
        _sWindowQ.resize(_qCapacity);
        _qTail = -1;
        
        _sWindowSum = 0.0;
        _nElements = 0;
    }
    
    double next(int val) {

        // Update the sliding window circular Q tail location
        _qTail = (_qTail + 1) % _qCapacity;
        
        if (_nElements < _qCapacity) {
            // Q is not full
            ++_nElements;    
        } else {
            // Q is full, so remove element at head of circular Q
            // The head of Q would be the location of new Tail
            // after insertion
            _sWindowSum -= _sWindowQ[_qTail];
        }

        // Add the new value to Q and update the window sum
        _sWindowQ[_qTail] = val;
        _sWindowSum += val;
        
        // Return the sliding window average
        return _sWindowSum / _nElements;
    }
    
private:
    
    // Moving average is implemented as a circularQ/
    // sliding window on a circular Q
    vector<int> _sWindowQ;
    int _qTail; // New element always inserted at tail
    int _qCapacity;
    int _nElements;
    double _sWindowSum;
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
