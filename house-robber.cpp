// n => nums.size()
// DP Iterative Approach
// Time complexity : O(n^2)
// Time complexity : O(n)

// DP Iterative Optimized Approach
// Time complexity : O(n)
// Time complexity : O(1)

class Solution {
public:
    int
    rob(vector<int>& nums) {

        if (nums.empty()) {
            // Base case of no houses
            return 0;
        }
        
        if (1 == nums.size()) {
            // Base case of single house
            return nums[0];
        }

        //return robDpIterativeApproach(nums);
        return robDpApproachOptimized(nums);
    }
    
private:

    int
    robDpIterativeApproach(vector<int>& nums) {

        int nh = nums.size(); // Num houses
        
        // houseRobbedDpTbl[i] represents the maximum money which can be made by
        // robbing house 'i' and any of the houses in range [i + 1, num houses - 1]
        // (Constraint of excluding adjacent houses applies)
        vector<int> houseRobbedDpTbl(nh, 0);
        
        // Tracks the maximum money which can be made by robbing
        int maxMoney = 0;
        
        // Iterate over the house from R -. L sequentially
        for (auto h = nh - 1; h >= 0; --h) {
            // Compute the max money which can be made by robbing the current house
            // and any of the subsequent houses in the range [h + 1, nh - 1]
            int money = nums[h];
            // Skip ajacent house at h + 1
            for (auto oh = h + 2; oh < nh; ++oh) {
                money = max(money, nums[h] + houseRobbedDpTbl[oh]);
            }
            
            // Store the max money made by robbing house 'h' and 0/multiple of
            // houses in range [h + 1, nh - 1] in cache
            houseRobbedDpTbl[h] = money;
            // Update max money made so far
            maxMoney = max(maxMoney, money);
        }
        
        return maxMoney;
    }
    
    int
    robDpApproachOptimized(vector<int>& nums) {
        // Num houses
        auto nh = nums.size();
        
        // maxMoney_i is the max amt of money made by
        // robbing houses in range [0, i]
        int maxMoney_i = 0;
        // maxMoney_i_2 is the max amt of money made
        // by robbing houses in range [0, i - 2]
        int maxMoney_i_2 = 0;
        // maxMoney_i_1 is the max amt of money made
        // by robbing houses in range [0, i - 1]
        int maxMoney_i_1 = 0;
        
        // At house 'i', robber can make 2 choices:-
        // 1. Rob house 'i', if he has not robbed house 'i - 1'
        // (i.e only robbed houses in range [0, i - 2])
        // Money made would be nums[i] + maxMoney_i_2
        // 2. Not rob house 'i', if he has robbed house 'i - 1'
        // (i.e only robbed houses in range [0, i - 1])
        // Money made would be maxMoney_i_1
        // So robber makes the choice which leads to max amt of money
        // So maxMoney_i = max(nums[i] + maxMoney_i_2, maxMoney_i_1);
        
        // Max money for [0, 0] initialized to house 0 cash
        maxMoney_i_2 = nums[0];
        // Max money for [0, 1] initialized to max of house 0 or
        // house 1 cash (as both cannot robbed together)
        maxMoney_i_1 = max(nums[1], maxMoney_i_2);
        maxMoney_i = maxMoney_i_1;
        // Iterate over houses 2 to 'n', computing the max money which
        // can be robbed from houses in the range [0, i] at each step
        for (auto i = 2; i < nh; ++i) {
            // Max money for [0, i]
            maxMoney_i = max(nums[i] + maxMoney_i_2, maxMoney_i_1);
            // Prep for moving 1 house to right in next step
            // Update max money two houses prior
            maxMoney_i_2 = maxMoney_i_1;
            // Update max money one house prior
            maxMoney_i_1 = maxMoney_i;
        }
        
        return maxMoney_i;
    }
};
