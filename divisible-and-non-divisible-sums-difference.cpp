// Time complexity : O(1)
// Space complexity : O(1)

class Solution {
public:
    int
    differenceOfSums(int n, int m) {
        
        // Sum of all in range [1, n] => allSum
        // Sum of nums divisible by 'm' in range [1, n] => mSum
        // Sum of nums not divisible by 'm' in range [1, n] => non-mSum
        // allSum = mSum + non-mSum
        // => non-Sum = allSum - mSum
        
        // We have to compute 'non-mSum - mSum' = 'allSum - mSum - mSum'
        // = allSum - 2mSum
        // Sum of all ints in range [1, n]
        int allSum = n * (1 + n) / 2;
        // Number of ints in range [1, n] divisible by 'm'
        int nDivisibleInts = n / m;
        // First and last term of series divisible by 'm' in range [1, n]
        int firstDivisibleInt = m;
        int lastDivisibleInt = m + (nDivisibleInts - 1) * m;
        // Sum if all ints in range [1, n] divisible by 'm'
        int sumOfDivisibleInts = nDivisibleInts * (firstDivisibleInt + lastDivisibleInt) / 2;
        
        return allSum - (2 * sumOfDivisibleInts);
    }
};
