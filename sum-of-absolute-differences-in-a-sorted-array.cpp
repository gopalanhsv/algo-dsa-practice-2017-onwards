// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    vector<int>
    getSumAbsoluteDifferences(vector<int>& nums) {
        // Since the array is sorted in non-decreasing order,
        // Summation of absolute differences between nums[i]
        // and all other elements is 
        // S[i] = (nums[i] - nums[0]) + (nums[i] - nums[1]) + (nums[i] - nums[2]) + ....
        // ...... + (nums[i] - nums[i - 1]) + {nums[i] - nums[i]} + nums[i + 1] - nums[i]
        // + (nums[i + 2] - nums[i]) + .....+ (nums[n - 2] - nums[i]) + (nums[n - 1] - nums[i])
        // => 
        // S[i] = {i * nums[i]} - {nums[0] + nums[1] + .. + nums[i - 1]} +
        //        {nums[i + 1] +  ..... + nums[n - 1]} - {(n - 1 - i - 1 + 1) * nums[i]}
        // => S[i] = {i * nums[i]} - {sum of elems prior to nums[i]} +
        //           {sum of elems post nums [i]} - {(n - i - 1) * nums[i]}
        // => S[i] = {i - n + 1 + i} * nums[i] -
        //           {sum of elems prior to nums[i]} + {sum of elems post nums [i]}
        // => S[i] = {2i + 1 - n} * nums[i] - {sum of elems prior to nums[i]} + {sum of elems post nums[i]}

        // All elements sum
        long long arrSum = accumulate(nums.begin(), nums.end(), 0LL);
        
        auto arrSz = nums.size();
        vector<int> resultV(arrSz, 0);
        // At an index 'i', suffix sum tracks sum of all array elements post index 'i'
        long long prefixSum = 0;
        // At an index 'i', prefix sum tracks sum of all array elements prior to index 'i'
        long long suffixSum = arrSum;
        for (auto i = 0; i != arrSz; ++i) {
            long long e = nums[i];
            // Update suffix sum (sum of elements post current element i.e. range [i + 1, n - 1])
            suffixSum -= e;
            // Determine sum of absolute differences at current index
            resultV[i] = ((2 * i + 1 - arrSz) * e) - prefixSum + suffixSum;
            // Update prefix sum to include current element (sum of elements upto current element i.e. range [0, i])
            prefixSum += e;
        }
        
        return resultV;
    }
};
