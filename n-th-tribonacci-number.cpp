class Solution {
public:
    int
    tribonacci(int n) {
        // Base case for n = 0/1/2
        if (0 == n) {
            return 0;
        }
        if ((1 == n) || (2 == n)) {
            return 1;
        }
        
        int t_i; // T(i)
        int t_i_1; // T(i - 1)
        int t_i_2; // T(i - 2)
        int t_i_3; // T(i - 3)
        
        t_i_3 = 0; // T(0)
        t_i_2 = 1; // T(1)
        t_i_1 = 1; // T(2)
        
        for (int i = 3; i <= n; ++i) {
            // As per formula
            // T(n + 3) = T(n) + T(n + 1) + T(n + 2) OR
            // Replacing 'n' by 'n - 3' above, we get
            // T(n) = T(n - 3) + T(n - 2) + T(n - 1)
            // T(i) = T(i - 3) + T(i - 2) + T(i - 1)
            t_i = t_i_3 + t_i_2 + t_i_1;
            
            // Update the values of T(i - 3), T(i - 2), T(i - 1)
            // for next iteration
            // T(i - 3) = T(i - 2)
            t_i_3 = t_i_2;
            // T(i - 2) = T(i - 1)
            t_i_2 = t_i_1;
            // T(i - 1) = T(i)
            t_i_1 = t_i;
        }
        
        return t_i;
    }
};
