class Solution {
public:
    vector<int>
    shuffle(vector<int>& nums, int n) {
        
#ifdef ARRAY_MEMBERS_OF_ANY_VAL
        int shuffledArrSz = n << 1;
        vector<int> shuffledV(shuffledArrSz);
        int xPtr = 0, yPtr = n;
        for (int i = 0; i != shuffledArrSz; i += 2) {
            shuffledV[i] = nums[xPtr++];
            shuffledV[i + 1] = nums[yPtr++];
        }
        
        return shuffledV;
#endif
        
#define ARRAY_MEMBERS_AS_PER_PROBLEM_CONSTRAINTS
#ifdef ARRAY_MEMBERS_AS_PER_PROBLEM_CONSTRAINTS

        // The array elements are +ve and have max val 1000 which fits in 10 bits 
        // So in first pass we use upper unsed bits of of each array element to
        // store the final value of that array element
        // Lower 16 bits contain original array element and upper 16 bits contain
        // the shuffled array element
        int xPtr = 0, yPtr = n;
        for (int i = 0; i != nums.size(); i += 2) {
            nums[i] |= ((nums[xPtr++] & 0xFFFF) << 16);
            nums[i + 1] |= ((nums[yPtr++] & 0xFFFF) << 16);
        }
        
        // Make a second pass over the array and shift each array element to
        // right by 16 bits so that it contains the shuffled array element
        for (auto & e : nums) {
            e = e >> 16;
        }
        
        return nums;
#endif
    }
};
