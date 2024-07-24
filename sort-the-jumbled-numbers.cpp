// n => nums.size()
// Time complexity : O(nlogn)
// Space complexity : O(n)

class Solution {
public:
    vector<int>
    sortJumbled(vector<int>& mapping, vector<int>& nums) {

        // Iterate over each number. Convert each number into its mapped value
        // and store the (mapped number, original array index) tuple
        int nNums = nums.size();
        vector<pair<int, int> > mappedNumsV;
        for (auto i = 0; i != nNums; ++i) {
            auto num = nums[i];
            // Convert number to its mapped value
            string numStr(to_string(num));
            int mappedVal = 0;
            for (auto x : numStr) {
                mappedVal = (10 * mappedVal) + mapping[int(x - '0')];
            }
            mappedNumsV.push_back({mappedVal, i});
        }
        
        // Sort the numbers in the new array in ascending order of mapped numbers
        // (using index to/ ensure that mapped numbers with same values are sorted
        // based on original array index positions
        sort(mappedNumsV.begin(), mappedNumsV.end(),
             [&](const auto& p1, const auto& p2) {
                 if (p1.first == p2.first) {
                     // Identical mapped values => sort based on indices
                     return p1.second < p2.second;
                 }
                 return p1.first < p2.first;
             });
        
        // Convert array of sorted mapped numbers back to their original value
        vector<int> sortedV(nNums);
        int i = 0;
        for (auto & mappedNum : mappedNumsV) {
            sortedV[i++] = nums[mappedNum.second];
        }
        
        return sortedV;
    }
};
