// n => pref.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    vector<int>
    findArray(vector<int>& pref) {

        // By definition, pref[i] = arr[0] ^ arr[1] ^ arr[2] .... ^ arr[i - 1] ^ arr[i]
        // => pref[i - 1] ^ pref[i] = 
        // {arr[0] ^ arr[1] ^ .... ^ arr[i - 2] ^ arr[i - 1]} ^ {arr[0] ^ arr[1] ^ .... ^ arr[i - 1] ^ arr[i]}
        // => pref[i - 1] ^ pref[i] = 
        // {(arr[0] ^ arr[0]) ^ (arr[1] ^ arr[1]).....^ (arr[i - 1] ^ arr[i - 1])} ^ arr[i]
        // => pref[i - 1] ^ pref[i] = arr[i]; with pref[0] = arr[0]
        
        auto arrSz = pref.size();
        if (arrSz <= 1) {
            // Base case of single element/empty prefix array
            return pref;
        }
        
        // Build the original array 'arr' step by step using prefix array and the relation
        // arr[i] = pref[i - 1] ^ pref[i]
        vector<int> arr(arrSz);
        arr[0] = pref[0];
        for (auto i = 1; i < arrSz; ++i) {
            arr[i] = pref[i - 1] ^ pref[i];
        }
        return arr;
    }
};
