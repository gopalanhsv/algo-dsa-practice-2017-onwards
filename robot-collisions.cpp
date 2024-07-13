// n => positions.size()
// Time complexity : O(nlogn)
// Space complexity : O(n)
class Solution {
public:
    vector<int>
    survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        
        typedef struct {
            int idx;
            int startPos;
            int health;
            char dir;
        } RobotInfoT;
        
        vector<RobotInfoT> rInfoV;
        auto nRobots = positions.size();
        for (auto i = 0; i != nRobots; ++i) {
            RobotInfoT ri;
            ri.idx = i;
            ri.startPos = positions[i];
            ri.health = healths[i];
            ri.dir = directions[i];
            rInfoV.emplace_back(ri);
        }
        sort(rInfoV.begin(), rInfoV.end(),
             [&](const auto & rInfo1, const auto & rInfo2) {
                return rInfo1.startPos < rInfo2.startPos;
             });

        // Use the rInfoV like a inplace stack getting rid of robots which get
        // removed due to collisions
        auto wrIdx = 0;
        // Iterate over the robots sequentially from L->R in ascending order
        // of their start locations
        for (auto & currRobotInfo : rInfoV) {
            // 
            if ((0 == wrIdx) || ('R' == currRobotInfo.dir)) {
                rInfoV[wrIdx++] = currRobotInfo;
            } else {
                bool currRobotRemoved = false;
                while (wrIdx >= 1) {
                    auto & seenRobotInfo = rInfoV[wrIdx - 1];
                    if (seenRobotInfo.dir == 'L') {
                        break;
                    } else if (seenRobotInfo.health < currRobotInfo.health) {
                        --wrIdx;
                        --currRobotInfo.health;
                    } else {
                        if (seenRobotInfo.health > currRobotInfo.health) {
                            --seenRobotInfo.health;
                        } else {
                            --wrIdx;
                        }
                        currRobotRemoved = true;
                        break;
                    }
                }
                if (!currRobotRemoved) {
                    rInfoV[wrIdx++] = currRobotInfo;
                }
            }
        }
        
        rInfoV.resize(wrIdx);
        sort(rInfoV.begin(), rInfoV.end(),
             [&](const auto & rInfo1, const auto & rInfo2) {
                return rInfo1.idx < rInfo2.idx;
             });
        
        vector<int> survivorHealthV;
        for (auto & rInfo : rInfoV) {
            survivorHealthV.emplace_back(rInfo.health);
        }
        return survivorHealthV;
    }
};
