// n => chalk.size()
// Time Complexity : O(nlogn)
// Space Complexity : O(n)

class Solution {
public:
    int
    chalkReplacer(vector<int>& chalk, int k) {
        // Num students
        int n = chalk.size();
        // prefixSumV[i] => total number of chalks reqd by all students in range [0, i]
        vector<long> prefixSumV(n, 0);
        prefixSumV[0] = chalk[0];
        for (auto i = 1; i < n; ++i) {
            prefixSumV[i] = prefixSumV[i - 1] + chalk[i];
        }
        
        // Num chalks used up in one complete round from 0 to 'n - 1' th student
        long nChalksPerRound = prefixSumV[n - 1];
        // Adjust 'k' to account for chalks used up in each round except the last;
        // as the last round has the chalk replacement event
        k %= nChalksPerRound;
        if (0 == k) {
            return 0;
        }
        
        // Exec a binary search to determine the student who has to replace the chalk
        int lo = 0, hi = n;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (k == prefixSumV[mid]) {
                return mid + 1;
            } else if (k > prefixSumV[mid]) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        
        return lo;
    }
};
