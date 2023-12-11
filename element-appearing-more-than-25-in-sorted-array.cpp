// n => arr.size()
// Time complexity : O(logn)
// Space complexity : O(1)

class Solution {
public:
    int
    findSpecialInteger(vector<int>& arr) {
        // Since there is only one element which takes more than
        // 1/4th of array space, that element will definitely be
        // present at one of the quartile locations i.e
        // either at n/4, n / 2 or 3n/4 indices since array is sorted
        // So we just need to find the frequency count of each of theelements
        // located at quartile points (frequency count determined by
        // finding the lowest and highest indices of elements via binary
        // search); and select element with highest frequency
        
        int n = arr.size();
        vector<int> quartileIdxV({n / 4, n / 2, 3 * n / 4});
        int maxFreqCnt = 0;
        int elemWithMaxFreq = -1;
        for (auto i : quartileIdxV) {
            auto rangeEndIdx = equal_range(arr.begin(), arr.end(), arr[i]);
            if (rangeEndIdx.second - rangeEndIdx.first > maxFreqCnt) {
                elemWithMaxFreq = arr[i];
                maxFreqCnt = rangeEndIdx.second - rangeEndIdx.first;
            }
        }
        
        return elemWithMaxFreq;
    }
};
