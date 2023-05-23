// n => nums seen so far in stream
// Time complexity : O(nlogk)
// Space complexity : O(k)

class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) : _maxAllowedHeapSize(k) {
        for (auto & x : nums) {
            // Add new element to min heap
            _minHeapV.push(x);
            // Restrict min-heap size to 'k'
            if (_minHeapV.size() > _maxAllowedHeapSize) {
                _minHeapV.pop();
            }
        }
    }
    
    int
    add(int val) {
        // Min-heap holds the largest 'k' elements seen so far in the stream.
        // Add new element and trim the heap size to 'k' if required (by removing
        // the smallest element)
        _minHeapV.push(val);
        if (_minHeapV.size() > _maxAllowedHeapSize) {
            _minHeapV.pop();
        }
        return _minHeapV.top();
    }
    
private:
    
    // Min-heap which stores a maximum of 'k' elements from the stream.
    // Element at heap top would be the kth largest element after its size g.e 'k'
    priority_queue<int, vector<int>, greater<int> > _minHeapV;
    int _maxAllowedHeapSize;
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
