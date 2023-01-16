class Solution {
public:
    bool
    sumOfNumberAndReverse(int num) {
        
        // Iterate over the possible values of +ve candidate numbers in
        // the range [num/2, num] s.t. candidate and its reverse add upto the
        // given number
        for (int cn = num / 2; cn <= num; ++cn) {
            
            // Check if candidate number and its reversed value equal the given number
            // Check if the complement is the reverse of the candidate
            if (cn + reversedNumber(cn) == num) {
                // Candidate number found satifying the given constraint 
                return true;
            }
        }
        
        // Iterate over the possible values of +ve candidate numbers in
        // the range [0, num/2] s.t. candidate and its reverse add upto the
        // given number
        for (int cn = num / 2; cn >= 0; --cn) {
            
            // Check if candidate number and its reversed value equal the given number
            // Check if the complement is the reverse of the candidate
            if (cn + reversedNumber(cn) == num) {
                // Candidate number found satifying the given constraint 
                return true;
            }
        }
        
        // No numbers possible s.t. number + reverse equals the specified number
        return false;
    }
    
private:
    
    inline long
    reversedNumber(int num) {
        // Compute the reverse of 'num'
        long rn = 0;
        while (num > 0) {
            auto d = num % 10;
            num /= 10;
            rn = (rn * 10) + d;
        }
        
        return rn;
    }
    
};
