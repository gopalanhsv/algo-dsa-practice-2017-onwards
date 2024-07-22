// n => names.size()
// Time complexity : O(nlogn)
// Space complexity : O(n)

class Solution {
public:
    vector<string>
    sortPeople(vector<string>& names, vector<int>& heights) {
        // Build array of <person height, person index> tuples
        int nPeople = names.size();
        vector<pair<int, int> > heightIdxPairV;
        for (int i = 0; i != nPeople; ++i) {
            heightIdxPairV.emplace_back(pair<int, int>(heights[i], i));
        }
        // Sort the array of tuples in descending order of the height values
        sort(heightIdxPairV.begin(), heightIdxPairV.end(), greater<pair<int, int> >());
        
        // Construct the people names in descending order of their heights
        vector<string> sortedNamesV;
        for (auto & htIdxP : heightIdxPairV) {
            sortedNamesV.emplace_back(names[htIdxP.second]);
        }
        
        return sortedNamesV;
    }
};
