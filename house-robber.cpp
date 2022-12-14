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

        //return robDpApproach(nums);
        return robDpApproachOptimized(nums);
    }
    
private:

    int
    robDpApproach(vector<int>& nums) {

        // Let houseRobbedDpTbl[i] represent the maximum money which can
        // be made if house at index 'i' is robbed for sure followed by any
        // number of houses in the range [i, .., num houses - 1]
        // (Constraint of excluding adjacent houses applies)
        int nh = nums.size(); // Num houses
        vector<int> houseRobbedDpTbl(nh, 0);
        // Tracks the maximum money which can be made by robbing
        int maxMoney = 0;
        
        // Start from the last house and sequentially work towards the first house
        // At each house point, track the max money which can be made by robbing the current
        // house and any of the subsequent houses -- store this amount in DP table
        // Also track the max amount of money which can be made at each step
        for (int h = nh - 1; h >= 0; --h) {
            // Rob house 'h'
            int money = nums[h];
            // Find max money which can be made by robbing house 'h'
            // and any of possible houses from h + 1 to nh
            // Skip ajacent house at h + 1
            for (int oh = h + 2; oh < nh; ++oh) {
                money = max(money, nums[h] + houseRobbedDpTbl[oh]);
            }
            
            // Store the max money made by robbing house 'h' and 0/multiple of
            // houses h + 1 to nh - 1 in DP table
            houseRobbedDpTbl[h] = money;
            // Update max money made
            maxMoney = max(maxMoney, money);
        }
        
        return maxMoney;
    }
    
    int
    robDpApproachOptimized(vector<int>& nums) {
        // Num houses
        int nh = nums.size();
        
        // maxMoney_i is the max amt of money to be made by
        // robbing houses in range [0, i]
        int maxMoney_i = 0;
        // maxMoney_i_2 is the max amt of money to be made
        // by robbing houses in range [0, i - 2]
        int maxMoney_i_2 = 0;
        // maxMoney_i_2 is the max amt of money to be made
        // by robbing houses in range [0, i - 1]
        int maxMoney_i_1 = 0;
        
        // At house 'i', robber has 2 options:-
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
        // Max money for [0, 1] iInitialized to max of house 0 or
        // house 1 cash (as both cannot robbed together)
        maxMoney_i_1 = max(nums[1], maxMoney_i_2);
        maxMoney_i = maxMoney_i_1;
        // Iterate over houses 2 to 'n', computing the max money which
        // can be robbed from houses in the range [0, i] at each step
        for (int i = 2; i != nh; ++i) {
            // Max money for [0, i]
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
