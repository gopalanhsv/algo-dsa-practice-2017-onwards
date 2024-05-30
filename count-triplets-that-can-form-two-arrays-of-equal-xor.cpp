// n => arr.size()
// Time complexity : O(n ^ 2)
// Time complexity : O(n)

class Solution {
public:
    int
    countTriplets(vector<int>& arr) {
        auto arrSz = arr.size();
        
        // Triplets (i, j, k) with (0 <= i < j <= k < arrSz)
        // a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
        // b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
        // resulting in a == b
        // Since a == b, a ^ b = 0
        // => arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1] ^ arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
        // i.e. xor of all elements in the subarray [i, k] is 0
        // => required Triplets (i, j, k) are formed for every subarray [i, k] with
        // i < j <= k for which XOR of all elements in [i, j] is 0
        
        // Another corrollary of above is if all element xor of subarray [i, j] is 0
        // => arr[i] ^ arr[i + 1] ^ ... ^ arr[p - 1] ^ arr[p] ^ arr[p + 1] ^ ... ^ arr[k] = 0
        // => A ^ B = 0 (where A is arr[i, p - 1] & B is arr[p, k])
        // => A ^ A ^ B = A ^ 0 = > 0 ^ B = A ^ 0
        // => A = B for all partitions of subarray [i, j] with all element xor as 0
        
        // XOR prefix sum xorPSum[i] = arr[0] ^ arr[1] ^ .... ^ arr[i]
        // with xorPSum[0] = arr[0]
        
        int nTriplets = 0;
        unordered_map<int, vector<int> > xorPfxSumToIndicesTbl;
        // xorPSum[-1] = 0 to account for subarrays starting from 0th index i.e. [0, x]
        // whose all element xor is 0
        xorPfxSumToIndicesTbl[0].emplace_back(-1); 
        // xorPSum[0] = arr[0]
        xorPfxSumToIndicesTbl[arr[0]].emplace_back(0); 
        int xorPfxSum = arr[0];
        // Iterate over the array from L->R sequentially
        for (auto k = 1; k < arrSz; ++k) {
            xorPfxSum ^= arr[k];
            
            auto it = xorPfxSumToIndicesTbl.find(xorPfxSum);
            if (it != xorPfxSumToIndicesTbl.end()) {
                // Current xor prefix sum at index 'k' is identical to
                // that seen earlier at prior indices say 'i', 'q', etc
                // => xorPSum[k] = xorPSum[i] ^ (xor of all elements in subarray[i + 1, k])
                // => 0 = xor of all elements in subarray[i + 1, k]
                // => required triplets can be formed using subarray [i + 1, k]
                // Triplets consist of all [i + 1, j, k] wherein i + 1 < j <= k
                // i.e. k - (i + 1) + 1 - 1 = k - i - 1 triplets
                auto & prevIdxV = it->second;
                for (auto & i : prevIdxV) {
                    nTriplets += (k - i - 1);
                }
            }
            
            // Add current index to the appropiate xor prefix sum
            xorPfxSumToIndicesTbl[xorPfxSum].emplace_back(k);
        }
        
        return nTriplets;
    }
};
