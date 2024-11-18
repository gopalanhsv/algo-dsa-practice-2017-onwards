// n => code.size()
// Time Complexity : O(n)
// Space Complexity : O(1)

class Solution {
public:
    vector<int>
    decrypt(vector<int>& code, int k) {
        vector<int> decryptV;
        if (code.empty()) {
            // Empty code vector
            return decryptV;
        }
        
        int codeVLen = code.size();
        decryptV.resize(codeVLen, 0);

        if (0 == k) {
            // Base case of  0 == k => all 0s in decrypted vector
            return decryptV;
        }
        
        // Problem reduces to a sliding window variant. Decrypted code is
        // based on sum of elements in either succeeding sliding window
        // or preceeding sliding window of length k
        int winStart = (k > 0) ? 1 : codeVLen + k;
        int winEnd = (k > 0) ? k : codeVLen - 1;
        int windowSum = 0;
        // Decrypted code for the first element
        for (int i = winStart; i <= winEnd; ++i) {
            windowSum += code[i];
        }
        decryptV[0] = windowSum;
        // Iterate over each element sequentially
        for (int i = 1; i != codeVLen; ++i) {
            // Slide window by 1 element ahead
            // Remove outgoing element and add incoming element
            windowSum -= code[winStart];
            winStart = (++winStart) % codeVLen;
            winEnd = (++winEnd) % codeVLen;
            windowSum += code[winEnd];
            // Update code
            decryptV[i] = windowSum;
        }
        
        return decryptV;
    }
};
