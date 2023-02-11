class Solution {
public:
    vector<int>
    separateDigits(vector<int>& nums) {
        vector<int> outV;
        // Iterate over the array elements from L->R sequentially
        for (auto & num : nums) {
            // Current array element converted to digit string
            string numStr = to_string(num);
            // Iterate over digit string from L->R
            for (auto & digitChr : numStr) {
                outV.emplace_back(int(digitChr - '0'));
            }
        }
        
        return outV;
    }
};
