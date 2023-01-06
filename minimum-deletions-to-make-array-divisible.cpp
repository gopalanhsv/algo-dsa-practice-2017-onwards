class Solution {
public:
    int
    minOperations(vector<int>& nums, vector<int>& numsDivide) {
        // First determine the largest number which divides all numbers in 
        // 'numsDivide'; in effect the GCD of all elements in 'numsDivide'
        int gcd = numsDivide[0];
        for (int i = 0; i != numsDivide.size(); ++i) {
            auto a = numsDivide[i];
            auto b = gcd;
            // Euclid algorithm to compute gcd(a, b)
            while (b != 0) {
                auto tmp = b;
                b = a % b;
                a = tmp;
            }
            // Update gcd from GCD(numsDivide[0, i - 1]) to GCD(numsDivide[0, i])
            gcd = a;
        }
        
        // Determine the smallest element in 'nums' which divides all elements
        // in 'numsDivide' => this would be the min element in 'nums' which
        // divides the gcd(numsDivide)
        int minElem = numeric_limits<int>::max();
        // Iterate over each element of 'nums'
        for (auto & e : nums) {
            if (0 == (gcd % e)) {
                // Current element divides GCD(numsDivide)
                // Update min element dividing all elements
                minElem = min(minElem, e);
            }
        }
        
        if (minElem == numeric_limits<int>::max()) {
            // Unable to find an element in 'num' which divides all elements of 'numsDivide'
            return -1;
        }
        
        // Determine the elements in 'nums' which should be deleted
        int ltMinElemCnt = 0;
        // Iterate over each element of 'nums'
        for (auto & e : nums) {
            if (e < minElem) {
                ++ltMinElemCnt;
            }
        }
        
        return ltMinElemCnt;
    }
};
