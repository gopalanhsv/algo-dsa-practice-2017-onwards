// Sorting Approach
// n => nums.size()
// Time complexity : O(nlogn)
// Space complexity : O(n)

// Hash Table Optimized Approach
// Time complexity : O(nlogn)
// Space complexity : O(n)

class Solution {

public:
    int
    longestSquareStreak(vector<int>& nums) {
        return longestSquareStreakOptimized(nums);
    }
        
private:
    int
    longestSquareStreakViaSorting(vector<int>& nums) {
        // Since the contents of the selected subsequence are sorted prior to
        // finding the longest streak, initial order of elements is immaterial.
        // One can sort the entire input array and build the subsequence from
        // there as an alternative
        
        // Since there are no -ve numbers, multiple numbers with same magnitude
        // wont lead to same squares. Sort the numbers in ascending order
        sort(nums.begin(), nums.end());
        unordered_set<int> numsTbl(nums.begin(), nums.end());
        unordered_set<int> seenNumsTbl;
        
        auto maxStreakLen = 0;
        // Iterate over the sequence numbers in ascending order (automatically
        // enables selection of the longest streak as we commence from
        // smallest numbers towards larger numbers)
        for (auto & num : nums) {
            if (seenNumsTbl.find(num) != seenNumsTbl.end()) {
                // Skip current number if processed earlier (as part of a square
                // streak - as each streak would have unique numbers)
                continue;
            }
            
            // Compute the length of longest square streak commencing from
            // current number
            auto currStreakLen = 0;
            long square = num;
            do {
                // Mark current streak number as seen/processed and add it to streak
                seenNumsTbl.insert(square);
                ++currStreakLen;
                // Next number in streak
                square = square * square;
            } while ((square <= nums.back()) && (numsTbl.find(square) != numsTbl.end()));
            // Update max square streak len
            maxStreakLen = max(maxStreakLen, currStreakLen);
        }
        
        return (maxStreakLen >= 2) ? maxStreakLen : -1;
    }

    int
    longestSquareStreakOptimized(vector<int>& nums) {
        // Since the contents of the selected subsequence are sorted prior to
        // finding the longest streak, initial order of elements is immaterial.
        // Storing the elements in a hash table initially precludes the need
        // to sort the elements initially
        
        // Since there are no -ve numbers, multiple numbers with same magnitude
        // wont lead to same squares
        unordered_set<int> numsTbl;
        int maxElem = *nums.begin();
        for (auto & num : nums) {
            maxElem = max(num, maxElem);
            numsTbl.insert(num);
        }
        
        unordered_set<int> seenNumsTbl;
        auto maxStreakLen = 0;
        // Iterate over the sequence numbers
        for (auto & num : nums) {
            if (seenNumsTbl.find(num) != seenNumsTbl.end()) {
                // Skip current number as it was processed earlier (as part of a square
                // streak - as each streak would have unique numbers)
                continue;
            }
            
            // Compute the length of longest square streak commencing from
            // current number
            auto currStreakLen = 0;
            long square = num;
            do {
                // Mark current streak number as seen/processed and add it to streak
                seenNumsTbl.insert(square);
                ++currStreakLen;
                if ((maxElem / square) < square) {
                    // Check to avoid integer overflow
                    break;
                }
                // Next possible number in streak
                square = square * square;
            } while ((numsTbl.find(square) != numsTbl.end()));
            // Update max square streak len
            maxStreakLen = max(maxStreakLen, currStreakLen);
        }
        
        return (maxStreakLen >= 2) ? maxStreakLen : -1;
    }
};
