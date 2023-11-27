// n => nums.size()
// QuickSelect Approach1
// Time complexity : O(n + klogk)
// Space complexity : O(n)

// QuickSelect Approach2
// Time complexity : O(n + k)
// Space complexity : O(n)

class Solution {
public:
    vector<int>
    maxSubsequence(vector<int>& nums, int k) {
        if ((0 == k) || (k > nums.size())) {
            // Base case of sequence len being zilch/g.t array size => error
            return vector<int>();    
        }
        
        return maxSubsViaQuickSelectApproach2(nums, k);
    }
    
private:

    vector<int>
    maxSubsViaQuickSelectApproach1(vector<int>& nums, int k) {
        // Construct tuple of array elements with respect array index
        vector<pair<int, int> > numIdxPairV;
        for (auto i = 0; i != nums.size(); ++i) {
            numIdxPairV.push_back({nums[i], i});
        }
        
        // Subsequence of length 'k' with the largest sum will consist
        // of the 'k' maximum array elements
        
        // Perform quickselect on the entire array s.t. the greatest 'k' elements
        // of the array get recolated to numIdxPairV[0, k - 1]
        nth_element(numIdxPairV.begin(), numIdxPairV.begin() + k - 1, numIdxPairV.end(),
                    [&](const auto & p1, const auto & p2) {
                        if (p1.first == p2.first) {
                            return p1.second < p2.second;
                        }
                        return p1.first > p2.first;
                    });
        // Drop all elements other than the 'k' greatest elements => these would form the
        // required subsequence; except they need to be rearranged as per input array order
        numIdxPairV.resize(k);
        // Rearrange the 'k' greatest elements as per input array order
        sort(numIdxPairV.begin(), numIdxPairV.end(),
             [&](const auto & p1, const auto & p2) {
                 return p1.second < p2.second;
             });
        
        // Dump the k greatest elements to output
        vector<int> outV;
        for (auto & [elem, idx] : numIdxPairV) {
            outV.emplace_back(elem);
        }
        return outV;
    }

    vector<int>
    maxSubsViaQuickSelectApproach2(vector<int>& nums, int k) {
        // Construct copy of array elements
        vector<int> numsV(nums.begin(), nums.end());
        
        // Subsequence of length 'k' with the largest sum will consist
        // of the 'k' maximum array elements
        
        // Perform quickselect on the entire array copy s.t. the greatest 'k' elements
        // of the array get recolated to numsV[0, k - 1]
        nth_element(numsV.begin(), numsV.begin() + k - 1, numsV.end(),
                    [&](const auto & e1, const auto & e2) {
                        return e1 > e2;
                    });
        // Drop all elements other than the 'k' greatest elements => these would form the
        // required subsequence; except they need to be rearranged as per input array order
        numsV.resize(k);
        
        // Count the number of elements equal to the 'k'th greatest element (as there may be
        // multiple instances of same) which occur in set of 'k' greatest elements
        // i.e. in numsV[0, k - 1]
        auto & kthGreatestElem = numsV[k - 1];
        auto kthGreatestElemCnt = 0;
        for (auto i = 0; i < k; ++i) {
            if (numsV[i] == kthGreatestElem) {
                ++kthGreatestElemCnt;
            }
        }
        
        // Hash table of the 'k' greatest elements
        unordered_set<int> kGreatestElemsTbl(numsV.begin(), numsV.end());
        
        // Since output has only the 'k' greatest elements, retain all elements g.t.
        // the 'kthGreatestElem' and as many of 'kthGreatestElem' elements which
        // occur in the required set
        vector<int> outV;
        // Iterate over original array and buid the reqd subsequence
        for (auto & num : nums) {
            // Since out
            if ((num > kthGreatestElem) || ((num == kthGreatestElem && kthGreatestElemCnt-- > 0))) {
                outV.emplace_back(num);
            }
        }
        return outV;
    }

};
