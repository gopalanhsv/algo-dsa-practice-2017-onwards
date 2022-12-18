class Solution {
public:
    vector<int>
    dailyTemperatures(vector<int>& temperatures) {
        
        // Iterate over the temperature vector from L to R.
        int n = temperatures.size();
        
        // Monostack storing indices of temperature vector whose
        // warmer temperature are yet to be determined
        stack<int> stk;
        vector<int> distanceToWarmerTempV(n, 0);
        for (int i = 0; i != n; ++i) {

            int currTemp = temperatures[i];
            
            // For all indices to the left whose warmer temp is not determined;
            // and whose temperature is lesser than current, update distances
            while (!stk.empty() && 
                   (currTemp > temperatures[stk.top()]) ) {
                distanceToWarmerTempV[stk.top()] = i - stk.top();
                stk.pop();
            }
                   
            // Add index of current element to stack top, as its warmer temperature
            // to right is yet to be examined.
            stk.push(i);
        }
                   
        return distanceToWarmerTempV;
    }
};
