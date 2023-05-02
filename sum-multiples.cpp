// Time complexity : O(1)
// Space complexity : O(1)

class Solution {
public:
    int
    sumOfMultiples(int n) {
        // S(X) = sum of multiples of 'X' in range [1, n]
        // Using set theory, 
        // S(3) + S(5) = S(3 only excluding 5) + S(5 only excluding 3) + (2 x S(5 & 3))
        // Accounting for numbers which are divisible by both 3 & 5, we have
        // S(3, 5) = S(3) + S(5) - S(3 & 5) =  S(3) + S(5) - S(15)
        // So, 
        // S(3, 5, 7) = S(3) + S(5) + S(7) - S(3 & 5) - S(5 & 7) - S(3 & 7) + S(3 & 5 & 7)
        // => S(3, 5, 7) = S(3) + S(5) + S(7) - S(15) - S(35) - S(21) + S(105)
        
        return
            sumOfMultiple(n, 3) + sumOfMultiple(n, 5) + 
            sumOfMultiple(n, 7) - sumOfMultiple(n, 15) - sumOfMultiple(n, 35) -
            sumOfMultiple(n, 21) + sumOfMultiple(n, 105);
    }
    
private:
    
    int
    sumOfMultiple(int n, int multVal) {
        // Sum of numbers in the range [1, n] which are a multiple
        // of 'multVal'. This forms an arithmetic progression with
        // number which are multiples of 'multVal'
        int numMultiples = n / multVal;
        int minMultipleVal = multVal;
        int maxMultipleVal = numMultiples * multVal;
        return (numMultiples) * (minMultipleVal + maxMultipleVal) / 2;
    }
};
