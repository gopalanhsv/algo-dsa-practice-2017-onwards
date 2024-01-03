// nr => num grid rows, nc => num grid cols
// Time complexity : O(nr x nc)
// Space complexity : O(1)

class Solution {
public:
    int
    numberOfBeams(vector<string>& bank) {
        
        // Num rows/cols in bank floor plan
        auto nr = bank.size();
        auto nc = bank[0].size();
        
        // Tracks the total number of laser beams
        auto nTotalLaserBeams = 0;
        // Tracks the number of security devices (in a row with security devices)
        // in the nearest row towards the top from any row being considered
        auto nDevicesInUpperRow = 0;
        // Move along the top to bottom of bank floor plan sequentially; computing
        // the number of laser beams between nearest rows having security devices
        for (auto r = 0; r != nr; ++r) {
            // Compute the number of security devices in the current row
            int nDevicesInCurrRow = 0;
            for (auto c = 0; c != nc; ++c) {
                nDevicesInCurrRow += int(bank[r][c] - '0');
            }
            
            // If the current row has security devices; form laser beams between
            // current row devices and the devices in the closest single row
            // towards the grid top (if there are any such devices)
            if (nDevicesInCurrRow > 0) {
                // Compute the number of laser beams pointing from current row
                // devices towards top
                auto nLaserBetweenCurrAndUpperRow =
                    nDevicesInCurrRow * nDevicesInUpperRow;
                // Update the total number of lasers
                nTotalLaserBeams += nLaserBetweenCurrAndUpperRow;
                // Setup for advancing to next row towards grid bottom, by making
                // current row with devices as the closest upper row with devices
                nDevicesInUpperRow = nDevicesInCurrRow;
            }
        }
        
        return nTotalLaserBeams;
    }
};
