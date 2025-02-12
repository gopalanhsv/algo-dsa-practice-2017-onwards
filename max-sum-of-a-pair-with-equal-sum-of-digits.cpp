// n => nums.size()
// M => max element in nums array
// Time Complexity : O(nlogM)
// Space Complexity : O(n)

class Solution {
public:
    int
    maximumSum(vector<int>& nums) {
        auto arrSz = nums.size();
        if (arrSz < 2) {
            // Base case of less than 2 numbers in array
            return -1;
        }

        int maxSum = -1;
        unordered_map<int, pair<int, int> > sumTo2MaxNumsTbl;
        for (auto i = 0; i < arrSz; ++i) {
            int currDigitSum = digitSum(nums[i]);
            int currNum = nums[i];
            auto it = sumTo2MaxNumsTbl.find(currDigitSum);
            if (it != sumTo2MaxNumsTbl.end()) {
                auto firstMax = it->second.first;
                auto secondMax = it->second.second;
                if (currNum >= firstMax) {
                    it->second.second = firstMax;
                    it->second.first = currNum;
                } else if (currNum > secondMax) {
                    it->second.second = currNum;   
                }

                maxSum = max(maxSum, it->second.first + it->second.second);
            } else {
                sumTo2MaxNumsTbl[currDigitSum] = {currNum, numeric_limits<int>::min()};
            }
        }

        return maxSum;
    }

private:
    int
    digitSum(int n) {
        int dSum = 0;
        while (n > 0) {
            dSum += (n % 10);
            n /= 10;
        }
        return dSum;
    }
};
