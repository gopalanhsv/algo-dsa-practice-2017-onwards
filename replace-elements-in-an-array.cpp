class Solution {
public:
    vector<int>
    arrayChange(vector<int>& nums, vector<vector<int>>& operations) {
        // Since each array element is unique, each value maps to a
        // single location. Build a hash table mapping each array
        // element to its index location
        unordered_map<int, int> elemToIdxTbl;
        for (int i = 0; i != nums.size(); ++i) {
            elemToIdxTbl[nums[i]] = i;
        }
        
        // Iterate through each replacement operation in sequence
        for (auto & oper : operations) {
            auto & numToBeReplaced = oper[0];
            auto & newNum = oper[1];
            // As per input gurantees, at the time of each operation,
            // there is only a single instance of the number to be replaced
            // and no instances of the new number
            // Lookup the location of the number to be replaced in array
            auto idx = elemToIdxTbl[numToBeReplaced];
            // Replace with new number at lookup result location in array
            nums[idx] = newNum;
            // Update the hash table to reflect insertion of new element
            elemToIdxTbl[newNum] = idx;
        }
        
        return nums;
    }
};
