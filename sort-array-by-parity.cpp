// Time complexity : O(nums.size())
// Space complexity : O(1)

class Solution {
public:
    vector<int>
    sortArrayByParity(vector<int>& nums) {

        if (nums.size() < 2) {
            // Base case of empty/single element array
            return nums;
        }
        
        // Even elems ptr commencing from leftmost array location
        // Odd elems ptr commencing from rightmost array location
        int evenElemsPtr = 0;
        int oddElemsPtr = nums.size() - 1;
        
        while (evenElemsPtr < oddElemsPtr) {
            // Advance the even pointer sequentially to the right skipping
            // all even elements till an odd element is encountered
            while ((evenElemsPtr < oddElemsPtr) &&
                   ((nums[evenElemsPtr] & 1) == 0)) {
                ++evenElemsPtr;
            }
            
            // Advance the odd pointer sequentially to the left skipping
            // all odd elements till an even element is encountered
            while ((evenElemsPtr < oddElemsPtr) &&
                   ((nums[oddElemsPtr] & 1) == 1)) {
                --oddElemsPtr;
            }
            
            // Swap the elements located at pointer locations
            swap(nums[evenElemsPtr], nums[oddElemsPtr]);
        }
        
        return nums;
    }
};
