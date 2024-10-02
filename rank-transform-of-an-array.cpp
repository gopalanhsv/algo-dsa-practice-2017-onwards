// n => arr.size()
// Time Complexity : O(nlogn)
// Space Complexity : O(n)

class Solution {
public:
    vector<int>
    arrayRankTransform(vector<int>& arr) {
        // Base case of empty/single element vector
        if (arr.empty()) {
            return vector<int>();
        }
        if (arr.size() == 1) {
            return vector<int>({1});
        }

        // Create a new array with the (array element, index position) tuple
        // Sort it on the basis of array element value in ascending order
        vector<pair<int, int> > elemPosPairV(arr.size());
        for (int i = 0; i != arr.size(); ++i) {
            elemPosPairV[i] = pair<int, int>(arr[i], i);
        }
        sort(elemPosPairV.begin(), elemPosPairV.end(),
             [&](const auto & p1, const auto & p2) {
                 return p1.first < p2.first;
             });
        
        // Iterate through the sorted <elem, index position> array and assign ranks
        vector<int> rankV(arr.size());
        // Assign rank for 1st element
        int rank = 1;
        rankV[elemPosPairV[0].second] = rank;
        int prevElemVal = elemPosPairV[0].first;
        int prevElemRank = rank;
        // Assign rank for other elements
        for (auto i = 1;  i != elemPosPairV.size(); ++i) {
            auto & currElemPosPair = elemPosPairV[i];
            if (currElemPosPair.first == prevElemVal) {
                // Current element is duplicate of previous => rank remains same
                rankV[currElemPosPair.second] = prevElemRank;
            } else {
                // Current element value is new => rank changes
                rankV[currElemPosPair.second] = ++rank;
                prevElemRank = rank;
                prevElemVal = currElemPosPair.first;
            }
        }
        return rankV;
    }
};
