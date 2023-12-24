// n => word.size()
// Time complexity : O(n)
// Space complexity : O(1)
class Solution {
public:
    int
    removeAlmostEqualCharacters(string word) {
        auto & w = word;
        auto wSz = w.size();
        // Tracks min operations applied to remove all adjacent almost-equal chars
        auto nOps = 0;
        // Iterate over the string chars from L->R sequentially
        for (auto i = 0; i < wSz; ++i) {
            // Adjust substring s[0, i + 1] to have no almost equal chars
            if ((i > 0) && (abs(int(w[i - 1] - w[i])) <= 1))  {
                // Current char is almost equal to the previous char
                // Replace the current char with a value s.t. 
                // it is not at all equal to both its adjacent chars
                // (i.e. previous and next chars if any)
                ++nOps;
                // Next char need not be examined/changed as the current replacement
                // operation takes care of the same
                ++i;
            }
        }
        
        return nOps;
    }
};
