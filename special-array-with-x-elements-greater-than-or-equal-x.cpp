// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    int
    specialArray(vector<int>& nums) {
        // Num elems in array
        int n = nums.size();
        
        // Solve this problem via counting sort.
        // Build frequency count table of elements [0, 1000]
        vector<int> freqCnt(1001, 0);
        int maxElem = -1;
        for (auto & x: nums) {
            freqCnt[x]++;
            maxElem = max(maxElem, x);
        }
        
        // Now the special element 'x' is s.t exactly 'x' elems in array are g.e x
        // Iterate throught the frequency count table from max element down to smallest,
        // stopping at the first element satisfying above criteria
        int nElemsGtEqX = 0;
        for (int x = maxElem; x >= 0; --x) {
            nElemsGtEqX += freqCnt[x];
            if (nElemsGtEqX == x) {
                return x;
            }
        }
        
        return -1;
    }
};
