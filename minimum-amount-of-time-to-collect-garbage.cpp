// n => garbage.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    garbageCollection(vector<string>& garbage, vector<int>& travel) {
        auto nHouses = garbage.size();
        
        // Garbage truck TM collects only metal 'M' garbage
        // Garbage truck TP collects only paper 'P' garbage
        // Garbage truck TG collects only glass 'G' garbage
        // All are initially stationed at house-0, must visit each house in
        // order and only one of the trucks can be in motion at any time

        // => only time optimization possible is to have the garbage truck collecting a
        // particular garbage type reduce its travel time by not visiting the houses which
        // dont have that garbage type i.e. go upto only the rightmost house having the
        // particular garbage type and halt there
        
        // To simplify the computation, we will start trucks TM/TP/TG from the rightmost
        // houses having 'M'/'P'/'G' garbage respectively and move all of them to house 0
        // collecting garbage on the way
        
        auto totalTravelTime = 0;
        auto totalCollectionTime = 0;
        bool houseWithPaperSeen = false;
        bool houseWithMetalSeen = false;
        bool houseWithGlassSeen = false;
        // Iterate over last house garbage to commence appropriate garbage trucks
        for (auto & c : garbage[nHouses - 1]) {
            if (c == 'G') {
                houseWithGlassSeen = true;
            }
            if (c == 'M') {
                houseWithMetalSeen = true;
            }
            if (c == 'P') {
                houseWithPaperSeen = true;
            }
        }
        // Update the garbage collection time to account for last house
        totalCollectionTime += garbage[nHouses - 1].size();
        
        for (int hId = nHouses - 2; hId >= 0; --hId) {    
            // Update travel time to account for truck travel times from previous house to current
            if (houseWithGlassSeen) {
                totalTravelTime += travel[hId];
            }
            if (houseWithMetalSeen) {
                totalTravelTime += travel[hId];
            }
            if (houseWithPaperSeen) {
                totalTravelTime += travel[hId];
            }
            
            // Update the garbage collection time to account for current house
            auto & currHouseGarbage = garbage[hId];
            totalCollectionTime += currHouseGarbage.size();
            // Start the garbage truck collection particular garbage if current house
            // is rightmost house with the particular garbage
            for (auto & c : currHouseGarbage) {
                if (c == 'G') {
                    houseWithGlassSeen = true;
                }
                if (c == 'M') {
                    houseWithMetalSeen = true;
                }
                if (c == 'P') {
                    houseWithPaperSeen = true;
                }
            }
        }
        
        return totalTravelTime + totalCollectionTime;
    }
};
