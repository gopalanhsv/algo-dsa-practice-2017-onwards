// E => roads.size(), N => n
// Time complexity : O(NlogN + E)
// Space complexity : O(N)

class Solution {
public:
    long long
    maximumImportance(int n, vector<vector<int>>& roads) {
        // Compute degree of each city (i.e number of roads incident on a city)
        vector<long long> cityDegreeV(n, 0);
        for (auto & road : roads) {
            cityDegreeV[road[0]]++;
            cityDegreeV[road[1]]++;
        }
        
        // Greedy approach
        // Assign each city with value in range [1, n] s.t. that cities with higher
        // degree/connectivity (terminating more roads) are given higher values
        // compared to those with lesser degree/connectivity (terminating less roads)
        // Assigning higher values to cities terminating more roads leads to higher values
        // getting added more while computing total importance
        // Use a max heap sorted based on city degrees; or by sorting based on city degrees
        
        // Combine a city and its degree information
        typedef struct _CityInfoT {
            int idx; // original city index/number
            long long degree; // road connectivity/degree of the city
        } CityInfoT;

        vector<CityInfoT> cityInfoV;
        for (int i = 0; i != n; ++i) {
            CityInfoT ci;
            ci.idx = i;
            ci.degree = cityDegreeV[i];
            cityInfoV.emplace_back(ci);
        }

        // Sort the cities in the descending order of city degrees
        typedef struct _CityInfoCmpObj {
            bool
            operator()(const CityInfoT& ci1, const CityInfoT& ci2) {
                return ci1.degree > ci2.degree;
            }
        } CityInfoCmpObj;
        sort(cityInfoV.begin(), cityInfoV.end(), CityInfoCmpObj());
        
        // Assign the cities integer values in range [1, n]
        // Higher values to more connected cities, lower values to
        // less connected i.e. from 'n' down to '1'
        vector<int> cityValV(n);
        int val = n;
        for (auto & ci : cityInfoV) {
            cityValV[ci.idx] = n--;
        }

        // Compute total road importance
        long long totalImp = 0;
        // Iterate over each road
        for (auto & road : roads) {
            // Get the assigned city values for road source and destination
            long long srcCityVal = cityValV[road[0]];
            long long dstCityVal = cityValV[road[1]];
            // Add the vals to total importance
            totalImp += srcCityVal + dstCityVal;
        }

        return totalImp;
    }
};
