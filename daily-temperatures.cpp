// n => temperatures.size()
// Time complexity : O(n)
// Space complexity : O(n)
class Solution {
public:
    vector<int>
    dailyTemperatures(vector<int>& temperatures) {
        
        // Problem reduces to finding the location of next greater element
        // for each element (easily done via a monotonic stack)
        auto n = temperatures.size();
        
        // Monostack storing indices of elements in the array whose
        // next warmer temperatures are yet to be determined
        stack<int> stk;
        vector<int> distanceToWarmerTempV(n, 0);
        // Iterate over the temperature vector from L to R sequentially
        for (auto i = 0; i != n; ++i) {

            auto currTemp = temperatures[i];
            
            // For all indices to the left whose warmer temp is not yet determined
            // and whose temperature is lesser than current, the current temperature
            // becomes the next warmer temperature
            while (!stk.empty() && 
                   (currTemp > temperatures[stk.top()]) ) {
                distanceToWarmerTempV[stk.top()] = i - stk.top();
                stk.pop();
            }
                   
            // Add index of current element to stack top, as its warmer temperature
            // to right is yet to be determined
            stk.push(i);
        }
                   
        return distanceToWarmerTempV;
    }
};
