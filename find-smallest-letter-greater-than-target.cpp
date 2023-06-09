// Time complexity : O(letters.size()) / O(n)
// Space complexity : O(1)
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        
        // Employ binary search for smallest letter g.t target 
        int l = 0, r = letters.size() - 1;
        if ((target < letters[l]) || (target >= letters[r])) {
            // Target beyond range, return 1st letter in range
            return letters[l];
        }
        
        // Find the minimum letter x in the vector s.t. letters[x] > target
        // by narrowing the search range by half in each iteration
        while (l < r) {
            int mid = l + (r - l) / 2;
            
            if (letters[mid] <= target) {
                // 'target' lies in the array range [mid, r]. So potential
                // search candidate lies in the upper half of the search range.
                // Continue search in upper half of the range
                l = mid + 1;
            } else {
                // 'target' lies in the array range [l, mid). So element
                // at 'mid' is a potential search candidate. Continue
                // search in lower half of the range
                r = mid;
            }
        }
        
        // Search terminates when l & r converge in a pincer movement s.t letters[r] > target
        return letters[l];
    }
};
