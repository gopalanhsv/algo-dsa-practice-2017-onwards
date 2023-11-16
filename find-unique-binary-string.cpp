// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    string
    findDifferentBinaryString(vector<string>& nums) {
        // Since each of the 'n' binary string are of length 'n', there are a total
        // of 2 ^ n possible binary strings out of which only 'n' are present in 'nums'
        
        // Construct a new binary string of length 'n' which is different from the
        // pre-existing 'n' strings one character at a time, as follows:-
        // 1st char different from 1st string nums[0] 1st char
        // 2nd char different from 2nd string nums[1] 2nd char
        // 3rd char different from 3rd string nums[2] 3rd char
        // 4th char different from 4th string nums[3] 4th char
        // .......................................................
        // xth char different from xth string nums[x - 1] xth char
        // .......................................................
        // nth char different from nth string nums[n - 1] nth char
        // Above technique ensures that the new string of length 'n' is different
        // from each of the pre-existing 'n' string in at least 1 position
        // => it is different from each of the pre-exisiting strings
        auto n = nums.size();
        auto strLen = n;
        // Init new binary string to all zeroes of length 'n' 
        string newBinStr(strLen, '0');
        int pos = 0;
        // Iterate over each of the pre-exisiting 'n' string
        for (auto & num : nums) {
            // Ensure that char in new string at [pos] is not same as nums[pos][pos] 
            if (num[pos] == '0') {
                newBinStr[pos] = '1';
            }/* else {
                newBinStr[pos] = '0';
            }*/
            ++pos;
        }
        
        return newBinStr;
    }
};
