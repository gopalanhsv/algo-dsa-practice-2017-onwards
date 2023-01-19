class Solution {
public:
    int
    minimizeXor(int num1, int num2) {
        unsigned int n1 = num1;
        unsigned int n2 = num2;
        
        // Determine the number of set bits in 'num2'
        int nBits = numSetBits(n2);
        
        // Number of bits in 'int type'
        int nBitsIntType = (sizeof(unsigned int)) << 3; 
        
        unsigned int x = 0;
        // For x XOR num1 to be minimal with the same number of bits as
        // num1; make 'x' identical to num1 as much as possible (limited
        // only by the number of bits as per 'num2') starting from the MSB
        // towards the LSB -- this ensures that x XOR num1 cancels out
        // as many bits possible from the MSB of result
        unsigned int bitMask = 1 << (nBitsIntType - 1);
        // Set bits in 'x' from MSB to LSB in same position as '1' in 'num1'
        // limited by the allowable number of bits which can be set
        for (int pos = nBitsIntType - 1; pos >= 0; --pos) {
            if (nBits) {
                if (bitMask & n1) {
                    x |= bitMask;
                    --nBits;
                }
            } else {
                break;
            }
            bitMask >>= 1;
        }
        
        // If there are allowable bits yet to be set, set the bits
        // corresponding to '0' bit positions in 'num1' from the LSB
        // to the MSB in 'x'; as these will contribute least to
        // magnitude of 'x
        // Set bits in 'x' from LSB to MSB in same position as '0' in
        // 'num1' limited by the allowable number of bits which can be set
        bitMask = 1;
        for (int pos = 0; pos < nBitsIntType; ++pos) {
            if (nBits) {
                if (0 == (bitMask & n1)) {
                    x |= bitMask;
                    --nBits;
                }
            } else {
                break;
            }
            bitMask <<= 1;
        }
        
        return x;
    }
    
private:
    
    int
    numSetBits(unsigned int n) {
        int cnt = 0;
        while (n) {
            // Toggles the rightmost set bit
            n = n & (n - 1);
            // Increment count of set bits
            ++cnt;
        }
        return cnt;
    }
};
