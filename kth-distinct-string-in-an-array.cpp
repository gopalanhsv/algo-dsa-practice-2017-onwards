// n => arr.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    string
    kthDistinct(vector<string>& arr, int k) {
        // Construct a frequency count table of all array strings
        unordered_map<string, int> freqCntTbl;
        for (auto & s : arr) {
            freqCntTbl[s]++;
        }
        
        // Iterate over the strings in the array from L -> R
        // Find the 'kth' string which occurs with frequency count of 1
        int distinctStringPosition = 0;
        for (auto & s : arr) {
            if (1 == freqCntTbl[s]) {
                ++distinctStringPosition;
                if (distinctStringPosition == k) {
                    return s;
                }
            }
        }
        
        return "";
    }
};
