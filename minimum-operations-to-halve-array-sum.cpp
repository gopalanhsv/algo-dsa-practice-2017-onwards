class Solution {
public:
    int
    halveArray(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        // To halve the array sum in the minimum number of iterations
        // possible, adopt the greedy approach of always selecting the
        // array element with maximum value to halve (from the remaining
        // elements) in each iteration. This is easily accomplished by
        // employing a max heap for storing the current set of array elements
        
        // Insert all array elements to the max heap
        priority_queue<double, vector<double>, less<double> > maxHeap;
        double arrSum = 0;
        for (auto & num : nums) {
            maxHeap.push(num);
            arrSum += num;
        }
        
        double origArrSumHalf = arrSum / 2;
        int minOps = 0;
        // Iterate as long as the sum of arrays elements exceeds half the
        // original array sum
        while (arrSum > origArrSumHalf) {
            // Increment num operations
            ++minOps;
            
            // Select array element with max value
            auto e = maxHeap.top();
            maxHeap.pop();
            
            // Halve selected element and add it back to array
            e /= 2;
            arrSum -= e;
            maxHeap.push(e);
        }
        
        return minOps;
    }
};
