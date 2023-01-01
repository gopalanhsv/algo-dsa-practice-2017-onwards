class Solution {
public:
    int
    closetTarget(vector<string>& words, string target, int startIndex) {
        int n = words.size();
        
        // Tracks the min distance between target string and startindex
        int minDist = numeric_limits<int>::max();
        
        // Iterate over each element of the array sequentially
        for (int i = 0; i != n; ++i) {
            
            if (words[i] == target) {
                // Current word matches target
                // Determine both the linear distance and circular
                // distance between current location and start index
                // Update the min distance
                
                // Linear distance between the start index and
                // current location within the array
                int withinArrayDist = abs(i - startIndex);
                minDist = min(minDist, withinArrayDist);
                // Circular distance between the start index and
                // current location across the array bounds
                int acrossArrayDist = n - withinArrayDist;
                minDist = min(minDist, acrossArrayDist);
            }
        }
        
        return (numeric_limits<int>::max() == minDist) ? -1 : minDist;
    }
};
