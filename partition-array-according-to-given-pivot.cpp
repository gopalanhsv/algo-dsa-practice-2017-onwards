// n => nums.size()
// Time Complexity : O(n)
// Space Complexity : O(1) {excluding output array}

class Solution {
public:
    vector<int>
    pivotArray(vector<int>& nums, int pivot) {
        //return pivotArrayMethod1(nums, pivot);
        return pivotArrayMethod2(nums, pivot);
        //return pivotArrayMethod3(nums, pivot);
    }
    
private:
    
    vector<int>
    pivotArrayMethod1(vector<int>& nums, int pivot) {
        // Single array, 3 pointers, 2 passes
        
        // Compute the number of elements less than, equal to and more than pivot
        int nLessThanPivot = 0;
        int nEqualToPivot = 0;
        for (auto & num : nums) {
            if (num == pivot) {
                ++nEqualToPivot;
            } else if (num < pivot) {
                ++nLessThanPivot;
            }
        }
        
        vector<int> rearrangedV(nums.size(), pivot);
        // Compute the start locations in the rearranged elements vector wherein
        // elements less than, equal to and more than pivot should be commenced
        // written to
        int lessThanPivotWrIdx = 0;
        int equalToPivotWrIdx = nLessThanPivot;
        int greaterThanPivotWrIdx = nLessThanPivot + nEqualToPivot;
        // Iterate over the array elements and store elements at the appropriate
        // write pointer locations as per element value; incrementing the respective
        // pointers at each step
        for (auto & num : nums) {
            if (num == pivot) {
                //rearrangedV[equalToPivotWrIdx++] = num;
                // Already taken care of on array construction
                ++equalToPivotWrIdx;
            } else if (num < pivot) {
                rearrangedV[lessThanPivotWrIdx++] = num;
            } else {
                rearrangedV[greaterThanPivotWrIdx++] = num;
            }
        }
        
        return rearrangedV;
    }
    
    vector<int>
    pivotArrayMethod2(vector<int>& nums, int pivot) {
        // Single array, 2 pass
        vector<int> rearrangedV(nums.size(), pivot);
        int wrIdx = 0;
        // Add elements less than pivot to rearranged array
        for (auto & num : nums) {
            if (num < pivot) {
                rearrangedV[wrIdx++] = num;
            }
        }

        wrIdx = nums.size() - 1;
        // Add elements greater than pivot to rearranged array from back to front
        for (int i = nums.size() - 1; i >= 0; --i) {
            auto & num = nums[i];
            if (num > pivot) {
                rearrangedV[wrIdx--] = num;
            }
        }

        return rearrangedV;
    }
    
    vector<int>
    pivotArrayMethod3(vector<int>& nums, int pivot) {
        // 3 arrays, 1 pass followed by 1 merge
        vector<int> lesserV;
        vector<int> equalV;
        vector<int> greaterV;
        
        // Add elements less than pivot, equal to pivot and greater than pivot
        // to the respective designated arrays 
        for (auto & num : nums) {
            if (num < pivot) {
                lesserV.emplace_back(num);
            } else if (num == pivot) {
                equalV.emplace_back(num);
            } else {
                greaterV.emplace_back(num);
            }
        }

        // Other arrays are telescoped to the back of array containing
        // 'lesser' than pivot
        auto & rearrangedV = lesserV;
        
        // Append elements equal to pivot to rearranged array
        copy(equalV.begin(), equalV.end(), back_inserter(rearrangedV));
        
        // Append elements greater than pivot to rearranged array
        copy(greaterV.begin(), greaterV.end(), back_inserter(rearrangedV));

        return rearrangedV;
    }
};
