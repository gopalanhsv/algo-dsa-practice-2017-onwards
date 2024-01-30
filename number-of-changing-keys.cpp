// n => s.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    countKeyChanges(string s) {
        int nKeyChanges = 0;
        auto prevKey = tolower(s[0]);
        // Iterate over the keys sequentially from L->R
        for (auto & key : s) {
            // Convert each key to lowercase
            auto currKey = tolower(key);
            if (currKey != prevKey) {
                ++nKeyChanges;
                prevKey = currKey;
            }
        }
        return nKeyChanges;
    }
};
