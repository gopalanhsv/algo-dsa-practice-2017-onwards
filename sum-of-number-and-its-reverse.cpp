class Solution {
public:
    bool
    sumOfNumberAndReverse(int num) {
        
        // Iterate over the possible values of +ve candidate numbers in
        // the range [1, n) s.t. candidate and its reverse add upto the
        // given number
        for (int candidateNum = 0; candidateNum <= num; ++candidateNum) {
            
            // Compute the expected value of the complement
            // for the given candidate number (s.t the candidate
            // and its complement add up to the specified number)
            int expectedComplement = num - candidateNum;

            // Check if the complement is the reverse of the candidate
            if (reversedNumbers(candidateNum, expectedComplement)) {
                // Candidate number found satifying the given constraint 
                return true;
            }
        }
        
        // No numbers possible s.t. number + reverse equals the specified number
        return false;
    }
    
private:
    
    inline bool
    reversedNumbers(int num1, int num2) {
        // Compute the reverse of 'num1'
        long reverseNum1 = 0;
        while (num1 > 0) {
            auto num1Digit = num1 % 10;
            num1 /= 10;
            reverseNum1 = (reverseNum1 * 10) + num1Digit;
            if (reverseNum1 > num2) {
                // Additional check for fast exit
                return false;
            }
        }
        
        // Return true if num1 is reverse of num2
        return reverseNum1 == num2;
    }
    
};
