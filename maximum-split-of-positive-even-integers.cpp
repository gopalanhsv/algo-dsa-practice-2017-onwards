class Solution {
public:
    vector<long long>
    maximumEvenSplit(long long finalSum) {
        
        vector<long long> outV;
        
        if (1 == (finalSum & 0x1)) {
            // Final sum is odd => no way to decompose into a 
            // set of only even numbers
            return outV;
        }

        // To split 'finalSum' into the maximum number of unique even
        // integers adding upto it, adopt the greedy approach of splitting
        // into the smallest set of even integers possible.
        
        // At each step, split the remaining portion of final sum into the
        // 2 numbers, one of which should be the smallest possible even
        // number (which has not been used earlier for splitting).
        // So the smallest even numbers into which the 'finalSum' should
        // be split would be obviously 2, 4, 6, 8, ...and so on.
        // Split the 'finalSum' successively increasing even numbers 2, 4, 6, ..
        // till even number into which it should be split exceeds the
        // remainder 'finalSum' value
        for (long long evenNum = 2; evenNum <= finalSum; evenNum += 2) {
            outV.emplace_back(evenNum);
            finalSum -= evenNum;
        }
        
        // Add the remainder value of 'finalSum' (which is even) to the
        // largest even number into which orginal number was split
        long long remainder = finalSum;
        auto & finalEvenNum = outV.back();
        finalEvenNum += remainder;
        
        return outV;
    }
};
