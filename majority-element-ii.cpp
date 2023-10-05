// Time complexity : O(nums.size())
// Space complexity : O(1)
class Solution {
public:
    vector<int>
    majorityElement(vector<int>& nums) {
        
        // Employing the Boyer-Moore majority vote algo here
        // (https://gregable.com/2013/10/majority-vote-algorithm-find-majority.html)

        // There can be at most 2 majority elements s.t. their frequency count is more than
        // array size / 3. 
        // Iterate over the elements and pick 2 candidates. Each time a number is
        // encountered which matches one of those candidates increase that particular candidate
        // count; otherwise reduce the frequency of current candidates. Whenever candidate
        // frequency count drops to 0, purge that candidate and pick the next number which
        // comes in the stream as new candidate
        
        int candidate1;
        int candidate2;
        int candidate1Cnt = 0;
        int candidate2Cnt = 0;
        
        for (auto & x : nums) {
            
            // New number is one of existing candidate majority elems   
            if (candidate1Cnt > 0 && x == candidate1) {
                // Current number matches existing 'candidate1'
                ++candidate1Cnt;
            } else if (candidate2Cnt > 0 && x == candidate2) {
                // Current number matches existing 'candidate1'
                ++candidate2Cnt;
            } else if (candidate1Cnt == 0) {
                // No valid candidate1 assigned => current number choosen as majority candidate1
                candidate1 = x;
                candidate1Cnt = 1;
            } else if (candidate2Cnt == 0) {
                // No valid candidate2 assigned => current number choosen as majority candidate2
                candidate2 = x;
                candidate2Cnt = 1;
            } else {
                // Current number is not either of the majority candidate numbers
                // Reduce frequency count of both candidates to account for mismatch
                --candidate2Cnt;
                --candidate1Cnt;
            }
        }
        
        // Do a second pass to get correct frequency count of the candidates found
        bool candidate1Valid = (candidate1Cnt != 0);
        bool candidate2Valid = (candidate2Cnt != 0);
        candidate1Cnt = 0;
        candidate2Cnt = 0;
        for (auto & x : nums) {
            if (candidate1Valid && x == candidate1) {
                ++candidate1Cnt;
            }
            
            if (candidate2Valid && x == candidate2) {
                ++candidate2Cnt;
            }
        }
        
        // Add candidates into the output vector if their frequency count exceeds array size / 3
        vector<int> outV;
        if (candidate1Cnt > nums.size() / 3) {
            outV.emplace_back(candidate1);
        }
        if (candidate2Cnt > nums.size() / 3) {
            outV.emplace_back(candidate2);
        }
        
        return outV;
    }
};
