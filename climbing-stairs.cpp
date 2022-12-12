class Solution {
public:
    int
    climbStairs(int n) {
        if ( n < 3) {
            return n;
        }
        
        //return waysToClimbMemoization(n);
        return waysToClimbDpIterative(n);
    }
    
private:
    int
    waysToClimbMemoizationRec(int n, vector<int>& waysToClimbTbl) {
        if (-1 != waysToClimbTbl[n]) {
            return waysToClimbTbl[n];
        }
        
        // n steps can be climbed by either taking n - 1 steps and
        // then 1 step OR n - 2 steps then 2 steps
        // Num ways to climb 'n' steps to top is sum of -
        // num ways to climb  'n - 1' + 1 steps, and
        // num ways to climb 'n - 2' + 2 steps
        waysToClimbTbl[n] =
            waysToClimbMemoizationRec(n - 2, waysToClimbTbl) + 
            waysToClimbMemoizationRec(n - 1, waysToClimbTbl);
        
        return waysToClimbTbl[n];
    }
    
    int
    waysToClimbMemoization(int n) {
        // Init memoization cache tracking number of ways
        // to climb stairs
        vector<int> waysToClimbTbl(n + 1, -1);
        waysToClimbTbl[1] = 1; // 1 step
        waysToClimbTbl[2] = 2; // 1 + 1, 2 steps
        
        return waysToClimbMemoizationRec(n, waysToClimbTbl);
    }
    
    int
    waysToClimbDpIterative(int n) {
        // W(x) -> num ways to climb x steps
        // n steps can be climbed by either taking n - 1 steps and
        // then 1 step OR n - 2 steps then 2 steps
        // Num ways to climb 'i' steps to top is sum of -
        // num ways to climb  'i - 1' + 1 steps, and
        // num ways to climb 'i - 2' + 2 steps
        // W(i) = W(i - 2) + W(i - 1)
        int W_i_2 = 1; // W(1) -> W(i-2)
        int W_i_1 = 2; // W(2) -> W(i-1)
        int W_i; // W(i)
        for (int i = 3; i <= n; ++i) {
            W_i = W_i_2 + W_i_1;
            W_i_2 = W_i_1;
            W_i_1 = W_i; 
        }
        
        return W_i;
    }
};
