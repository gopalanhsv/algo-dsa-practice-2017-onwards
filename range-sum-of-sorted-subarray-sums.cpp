// Brute Force Approach
// Time Complexity : O(n^2logn)
// Space Complexity : O(n ^ 2)

class Solution {
public:
    int
    rangeSum(vector<int>& nums, int n, int left, int right) {
        return rangeSumBruteForceApproach(nums, n, left, right);
    }
    
private:
    
    int
    rangeSumBruteForceApproach(vector<int>& nums, int n, int left, int right) {
        // Create all possible contiguous subarray sums of the original array
        vector<int> subArrSumsV;
        for (auto i = 0; i < n; ++i) {
            int subArrSum = 0;
            for (auto j = i; j < n; ++j) {
                subArrSum += nums[j];
                subArrSumsV.push_back(subArrSum);
            }
        }
        // Sort the subarray sums in non decreasing order
        sort(subArrSumsV.begin(), subArrSumsV.end());
        // Compute the required range sum of subarray sum
        const int moduloFactor = 1000000000 + 7;
        long rSum = 0;
        for (auto i = left - 1; i < right; ++i) {
            rSum += subArrSumsV[i];
            rSum %= moduloFactor;
        }
        
        return rSum;
    }
    
    int rangeSumPQApproach(vector<int>& nums, int n, int left, int right) {
        	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> mqueue;
	for (int i=0; i<n; i++)
		mqueue.push({nums[i], i+1});

	int ans = 0, mod = 1e9+7;
	for (int i=1; i<=right; i++) {
		auto p = mqueue.top();
		mqueue.pop();
		if (i >= left)
			ans = (ans + p.first) % mod;
		if (p.second < n) {
			p.first += nums[p.second++];
			mqueue.push(p);
		}
	}
	return ans;
        
    }
};
