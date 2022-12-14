class Solution {
public:
    int
    rob(vector<int>& nums) {

        // Base case of no houses
        if (nums.empty()) {
            return 0;
        }
        
        // Base case of 1 house
        if (nums.size() == 1) {
            return nums[0];
        }
        
        // Base case of 2 houses
        if (nums.size() == 2) {
            return max(nums[0], nums[1]);
        }

        // Num houses
        int nh = nums.size();

        // Due to houses being arranged in a circle,
        // If house 0 is selected, house 'nh - 1' is dropped
        // If house 'nh - 1' is selected, house '0' is dropped
        // i.e. robber should consider either one of the two ranges [0, nh - 2] OR
        // [1, nh - 1] for robbing. So the problem reduces to applying the house robber
        // problem to the two ranges to determine the max money which can be robbed in
        // either range; and choosing the maximum value pilfered 
        return
            max(robDpApproachOptimized(nums, 0, nh - 2),
                robDpApproachOptimized(nums, 1, nh - 1));
    }

private:
    int
    robDpApproachOptimized(vector<int>& nums, int lo, int hi) {
        
        // maxMoney_i is the max amt of money to be made by
        // robbing houses in range [lo, i]
        int maxMoney_i = 0;
        // maxMoney_i_2 is the max amt of money to be made
        // by robbing houses in range [lo, i - 2]
        int maxMoney_i_2 = 0;
        // maxMoney_i_1 is the max amt of money to be made
        // by robbing houses in range [lo, i - 1]
        int maxMoney_i_1 = 0;
        
        // At house 'i', robber has 2 options:-
        // 1. Rob house 'i', if he has not robbed house 'i - 1'
        // (i.e only robbed houses in range [lo, i - 2])
        // Money made would be nums[i] + maxMoney_i_2
        // 2. Not rob house 'i', if he has robbed house 'i - 1'
        // (i.e only robbed houses in range [lo, i - 1])
        // Money made would be maxMoney_i_1
        // So robber makes the choice which leads to max amt of money
        // So maxMoney_i = max(nums[i] + maxMoney_i_2, maxMoney_i_1);
        
        // Max money for [lo, lo] initialized to house 0 cash
        maxMoney_i_2 = nums[lo];
        // Max money for [lo, 1] Initialized to max of house lo or
        // house lo + 1 cash (as both cannot robbed together)
        maxMoney_i_1 = max(nums[lo + 1], maxMoney_i_2);
        maxMoney_i = maxMoney_i_1;
        // Iterate over houses 'lo' to 'hi', computing the max money which
        // can be robbed from houses in the range [lo, i] at each step
        for (int i = lo + 2; i <= hi; ++i) {
            // Max money for [lo, i]
            maxMoney_i = max(nums[i] + maxMoney_i_2, maxMoney_i_1);
            // Prep for shifting 1 house to right in next step
            // Update max money two houses prior
            maxMoney_i_2 = maxMoney_i_1;
            // Update max money one house prior
            maxMoney_i_1 = maxMoney_i;
        }
        
        return maxMoney_i;
    }
};
