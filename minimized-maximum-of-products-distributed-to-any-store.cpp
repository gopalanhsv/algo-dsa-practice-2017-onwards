class Solution {
public:
    int
    minimizedMaximum(int n, vector<int>& quantities) {
        // Since a store holds products only of a single type, a store can hold
        // at min 1 product of a given type
        int minStoreCapacity = 1;
        // Since a store holds products only of a single type, a store can be
        // hold at most all products of a given type. Max possible number
        // of products which can be held by a store would be those product(s)
        // having the max qty 
        int maxStoreCapacity = 0;
        for (auto & qty : quantities) {
            maxStoreCapacity = max(qty, maxStoreCapacity);
        }
        
        // Find the minimum store capacity for which all products can be stocked
        // across all 'n' stores by doing a binary search in the range
        // [minStoreCapacity, maxStoreCapacity]. Done by reducing the search range
        // via a pincer movement till the range has only a single value
        int l = minStoreCapacity;
        int r = maxStoreCapacity;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (capacitySufficientToStockAllProducts(mid, n, quantities)) {
                // 'mid' becomes the upper boudn for the search range 
                r = mid;
            } else {
                // Capacity insufficient to stock all products. Search
                // in the upper half of the range 
                l = mid + 1;
            }
        }
        
        return l;
    }
    
private:
    
    bool
    capacitySufficientToStockAllProducts(
        int storeCapacity, int nStoresAvl, vector<int>& quantities) {
        
        // Compute the minimum number of stores needed to to distribute
        // all products limited by stored capacity and product type constraint
        int totalStoresReqd = 0;
        // Iterate over each product type
        for (auto & qty : quantities) {
            // Compute the min number of stores needed to hold current product type
            int minStoresReqdForCurrProd = ceil(double(qty) / storeCapacity);
            // Update the total number of stored reqd
            totalStoresReqd += minStoresReqdForCurrProd;
        }
        
        // Stores required should not exceed the # of available stores
        return totalStoresReqd <= nStoresAvl;
    }
};
