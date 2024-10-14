// n => nums.size()
// Time Complexity : O(nlogn + klogn)
// Space Complexity : O(n)

class Solution {
public:
    long long
    maxKelements(vector<int>& nums, int k) {
        
        
        long long score = 0;
        // Adopt the greedy approach of maximizing the score at each
        // step by always choosing the number with the max value from 
        // amongst those present => easily doable via a max heap
        priority_queue<int, vector<int>, less<int> > maxHeap(nums.begin(), nums.end());
        
        // Simulate the 'k' operations
        while (!maxHeap.empty() && (k-- > 0)) {
            // Remove the max element from heap
            auto maxElem = maxHeap.top();
            maxHeap.pop();
            // Update score
            score += maxElem;
            // Replace the removed element with updated value
            int newVal = (maxElem + 2) / 3;
            maxHeap.push(newVal);
        }
        
        return score;
    }
};
