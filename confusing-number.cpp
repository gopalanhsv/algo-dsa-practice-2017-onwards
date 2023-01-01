class Solution {
public:
    bool
    confusingNumber(int n) {
        // Mapping table from a digit to its rotated value
        // (if rotation yields a valid number)
        unordered_map<int, int> confusingNumTbl(
            {
                {0, 0}, {1, 1}, {6, 9}, {8, 8}, {9, 6}
            });
        
        // Split the given number into its digits. Rotate each digit and
        // build the number in reversed form (i.e. reverse orginal number
        // and rotate each of its digit if possible)
        unordered_map<int, int>::iterator iter;
        long long rotatedNumber = 0;
        int norig = n;
        while (n) {
            // Rightmost digit
            int d = n % 10;
            n /= 10;
            // If digit becomes invalid after rotation, not a confusing number
            iter = confusingNumTbl.find(d);
            if (iter == confusingNumTbl.end()) {
                return false;
            }
            // Rotated digit
            int rd = iter->second;
            rotatedNumber = (10 * rotatedNumber) + rd;
        }
        
        // Rotated number not same as original number is a confusing number
        return rotatedNumber != norig;
    }
};
