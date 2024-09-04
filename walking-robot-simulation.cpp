// n => commands.size(), k => obstacles.size()
// Time Complexity : O(n)
// Space Complexity : O(k)

class Solution {
public:
    int
    robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        // Hash table of obstacles
        unordered_map<int, unordered_set<int> > obsTbl;
        for (auto & obstacle : obstacles) {
            auto x = obstacle[0];
            auto y = obstacle[1];
            obsTbl[x].insert(y);
        }
        
        // N => -2 -> (-1, 0), -1 -> (1, 0)
        // E => -2 -> (0, 1), -1 -> (0, -1)
        // S => -2 -> (1, 0), -1 -> (-1, 0)
        // W => -2 -> (0, -1), -1 -> (0, 1)
        
        vector<pair<int, int> > dirOffsetsV = {
            {0, 1}, // N - 0
            {1, 0}, // E - 1
            {0, -1}, // S - 2
            {-1, 0}, // W - 3
        };
        
        int X = 0, Y = 0;
        int currDirection = 0;
        int maxDist = 0;
        for (auto & cmd : commands) {
            if (-2 == cmd) {
                // Turn 90 deg to left
                // 0 -> 3, 1 -> 0, 2 -> 1, 3 -> 2
                currDirection += 4;
                --currDirection;
                currDirection %= 4;
            } else if (-1 == cmd) {
                // Turn 90 deg to right
                // 0 -> 1, 1 -> 2, 2 -> 3, 3 -> 4
                ++currDirection;
                currDirection %= 4;

            } else {
                // Move 'nSteps' as per offset if no blocks encountered
                int nSteps = cmd;
                int pathX = X, pathY = Y;
                auto xOffset = dirOffsetsV[currDirection].first;
                auto yOffset = dirOffsetsV[currDirection].second;
                while (nSteps-- > 0) {
                    pathX += xOffset;
                    pathY += yOffset;
                    auto it = obsTbl.find(pathX);
                    if (it != obsTbl.end()) {
                        auto & obsTblY = it->second;
                        if (obsTblY.find(pathY) != obsTblY.end()) {
                            break;
                        }
                    }
                    X = pathX;
                    Y = pathY;
                }
                
                maxDist = max(maxDist, (X * X) + (Y * Y));
            }
        }
        
        return maxDist;
    }
};
