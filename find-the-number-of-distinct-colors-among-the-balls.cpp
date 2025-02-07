// q => queries.size()
// Time Complexity : O(q)
// Space Complexity : O(limit) 

class Solution {
public:
    vector<int>
    queryResults(int limit, vector<vector<int>>& queries) {
        auto nQueries = queries.size();
        vector<int> resultsV(nQueries);
        unordered_map<int, int> ballColorsTbl;
        unordered_map<int, int> color2NumBallsTbl;
        for (auto i = 0; i < nQueries; ++i) {
            auto & query = queries[i];
            auto ball = query[0];
            auto newColor = query[1];
            auto it = ballColorsTbl.find(ball);
            if (it != ballColorsTbl.end()) {
                auto oldColor = it->second;
                if (0 == --color2NumBallsTbl[oldColor]) {
                    color2NumBallsTbl.erase(oldColor);
                }
            }
            ballColorsTbl[ball] = newColor;
            color2NumBallsTbl[newColor]++;
            resultsV[i] = color2NumBallsTbl.size();
        }

        return resultsV;
    }
};
