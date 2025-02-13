// n => nums.size()
// Time Complexity : O(nlogn)
// Space Complexity : O(n)

class Solution {
public:
    int
    minOperations(vector<int>& nums, int k) {
        priority_queue<long, vector<long>, greater<long> > minHeap;
        for (auto & x : nums) {
            minHeap.push(x);
        }

        int nOps = 0;
        while (minHeap.size() >= 2) {
            auto x = minHeap.top();
            if (x >= k) {
                break;
            }

            minHeap.pop();
            auto y = minHeap.top();
            minHeap.pop();
            auto newNum = min(x, y) * 2 + max(x, y);
            minHeap.push(newNum);

            ++nOps;
        }

        if (minHeap.top() >= k) {
            return nOps;
        }

        // Impossible to make all array elements g.e. 'k'
        return -1;
    }
};
