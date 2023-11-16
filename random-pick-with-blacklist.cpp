// b => blacklist.size()

// Time complexity : 
// Constructor : O(b)
// pick() : O(1)

// Space complexity : O(b)

class Solution {
public:
    Solution(int n, vector<int>& blacklist) {
        auto b = blacklist.size();
        // Since the random integer to be picked is to be in the range
        // [0, n - 1] excluding 'b' unique elements in the 'blacklist',
        // there are a total of 'n - b' whitelisted numbers in the
        // range [0, n - 1]
        
        // Remap the selection array range of numbers [0, n - 1] to
        // the range [0, n - 1 - b]; s.t all blacklisted numbers lying the
        // range [0, n - 1 - b] get mapped to unique whitelisted numbers
        
        // Essentially fill the holes/gaps created by blacklisted numbers
        // in [0, n - 1] by whitelisted numbers which lie after the blacklisted
        // numbers; reducing the candidate selection set to [0, n - 1 - b]

        unordered_set<int> blacklistTbl(blacklist.begin(), blacklist.end());
        // Determine white list nums not in 'random pick' range
        // [0, n - b - 1] i.e. lying in [n - b, n - 1]
        vector<int> outOfRangeWhiteListNumsV; 
        for (auto num = n - b; num < n; ++num) {
            if (blacklistTbl.find(num) == blacklistTbl.end()) {
                outOfRangeWhiteListNumsV.emplace_back(num);
            }
        }
        
        // Remap all the blacklisted numbers in the 'random pick' range [0, n - 1 - b]
        // to unique whitelist numbers lying outside the range in [n - b, n - 1]
        int idx = 0;
        // Iterate over blacklist number
        for (auto & bNum : blacklistTbl) {
            if (bNum < n - b) {
                // ReMap blacklisted num to used whitelist number in [n - b, n - 1]
                _blackToWhiteNumsTbl[bNum] = outOfRangeWhiteListNumsV[idx++];
            }
        }
        _whiteListSz = n - b;
    }

    int
    pick() {
        // Randomly pick an number in the range of whitelist nums
        uniform_int_distribution<int> u(0, _whiteListSz - 1);
        auto num = u(_randEng);
        
        if (_blackToWhiteNumsTbl.find(num) != _blackToWhiteNumsTbl.end()) {
            // Number selected was in black list. Get remapped whitelist number
            return _blackToWhiteNumsTbl[num];
        }
        // Number not in blacklist
        return num;
    }
    
private:
    
    // Data members
    
    // Hash table mapping blacklisted numbers in [0, n - 1 - b] to unique 
    // whitelisted numbers in range [0, n - 1]
    unordered_map<int, int> _blackToWhiteNumsTbl;
    // Size of/nums in whitelist
    int _whiteListSz;
    default_random_engine _randEng;
    
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(n, blacklist);
 * int param_1 = obj->pick();
 */
