// c =>  num cities, p => paths.size()
// Time complexity : O(p)
// Space complexity : O(c)
class Solution {
public:
    string
    destCity(vector<vector<string>>& paths) {
    
        // Iterate through the path source/dest entries
        unordered_set<string> dstCities;
        for (auto & path : paths) {
            // Store 'to' city in hash table as it may be a final destination city
            dstCities.insert(path[1]);
            // Erase 'from' city from hash as it has outgoing paths =>
            // cannot be a final destination city
            dstCities.erase(path[0]);
        }
        // 2nd pass to purge any remaining 'from' cities
        for (auto & path : paths) {
            auto & srcCity = path[0];
            dstCities.erase(srcCity);
        }
        
        // Residual is the destination city
        return *(dstCities.begin());
    }
};
