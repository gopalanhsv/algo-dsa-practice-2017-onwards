// n => batteryPercentages
// Time complexity : O(n)
// Space complexity : O(1)
class Solution {
public:
    int
    countTestedDevices(vector<int>& batteryPercentages) {
        // Tracks the count of devices with +ve battery percentages seen so far
        // which would also be the count of devices which be tested
        auto nTestedDevicesSeenSoFar = 0;
        // Tracks the decrement to be applied to teh battery percentage of all
        // devices post the current device
        auto decrementToBeApplied = 0;
        // Iterate over the devices from L->R sequentially
        for (auto & battery : batteryPercentages) {
            // Update battery %age of current device to reflect
            // decrement due to succesfully tested devices seen so far
            auto netBattery = max(0, battery - decrementToBeApplied);
            if (netBattery > 0) {
                // Current device can be tested
                ++nTestedDevicesSeenSoFar;
                // All device post current device need to have their
                // battery %age decremented by an updated value
                ++decrementToBeApplied;
            }
        }
        
        return nTestedDevicesSeenSoFar;
    }
};
