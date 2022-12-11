class Solution {
public:
    int
    numberOfCuts(int n) {
        // VImp special case : single slice => no cut
        if (1 == n) {
            return 0;
        }
        
        // Odd number of slices, no cuts along diameter possible
        // which will result in equal slices
        // all cuts have to be done from circumference to radius
        if (1 == (n & 1)) {
            return n;
        }
        
        // Even number of slices, all cuts along diameter possible
        // resulting in equal slices. Half the number of cuts 
        return n >> 1;
    }
};
