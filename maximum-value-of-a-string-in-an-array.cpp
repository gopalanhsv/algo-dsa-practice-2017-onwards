class Solution {
public:
    int
    maximumValue(vector<string>& strs) {
        int maxVal = 0;
        // Iterate over each string in array sequentially
        for (auto & str : strs) {
            // Compute string value for current string and 
            // update the max string value
            maxVal = max(maxVal, stringValue(str));
        }
        return maxVal;
    }
    
private:
    
    inline int
    stringValue(string & s) {
        int val = 0;
        for (auto & c : s) {
            if (isalpha(c)) {
                // String has non-digit chars
                // Value will be the length
                return s.size();
            }
            // String has digits seen so far - so base 10 representation
            val = val * 10 + int(c - '0');
        }
        return val;
    }
};
