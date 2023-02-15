class Solution {
public:
    vector<int>
    addToArrayForm(vector<int>& num, int k) {
        // Base case of k being 0
        if (k == 0) {
            return num;
        }    
        
        // Process array from right to left, adding individual digits
        // k is assumed as initial carry. StorE the least significant digit
        // of sum in output vector; and carry over the more significant
        // digits to be added to the array digit to the immediate left
        vector<int> outV;
        int carry = k;
        int i = num.size() - 1;
        while (carry || i >= 0) {
            int digitSum = carry;
            if (i >= 0) {
                digitSum += num[i--];
            }
            // Append least significant digit of current sum;
            // and carry over the remainder
            outV.emplace_back(digitSum % 10);
            carry = digitSum / 10;
        }
        
        // Reverse the output array so that it stores digits of sum from
        // most significant digit to least significant digit
        reverse(outV.begin(), outV.end());
        return outV;
    }
};
