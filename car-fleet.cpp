class Solution {
public:
    int
    carFleet(int target, vector<int>& position, vector<int>& speed) {
        // A car closer to destination cannot be overtaken by a car from rear.
        // All cars which reach/come up to any car (which was closer to
        // destination initially at start) form a fleet and travel to destination
        // together.
        
        // So all we need to do is, for every car get the travel time to reach the
        // destination assuming no cars were there to block it. Then commencing
        // from the car closer to target and moving towards cars away from target;
        // for each car compute the set of cars in its rear which will catch
        // up to it by the time it reaches the destination. These form a car fleet
        
        return carFleetViaSort(target, position, speed);
        //return carFleetViaMap(target, position, speed);
    }
    
private:
    
    int
    carFleetViaMap(int target, vector<int>& position, vector<int>& speed) { 
        map<int, double, greater<int> > startPosToTravelTimeTbl;
        int nCars = position.size();
        for (int i = 0; i != nCars; ++i) {
            auto & startLoc = position[i];
            double virtualTravelTime = double(target - startLoc) / speed[i];
            startPosToTravelTimeTbl[startLoc] = virtualTravelTime;
        }
        
        map<int, double>::iterator it = startPosToTravelTimeTbl.begin();
        map<int, double>::iterator endIt = startPosToTravelTimeTbl.end();
        int nCarFleet = 0;
        double carAtFrontTravelTime = 0.0;
        for (; it != endIt; ++it) {
            double rearCarTravelTime = it->second;
            if (rearCarTravelTime > carAtFrontTravelTime) {
                carAtFrontTravelTime = rearCarTravelTime;
                ++nCarFleet;
            }
        }
        return nCarFleet;
    }
    
    int
    carFleetViaSort(int target, vector<int>& position, vector<int>& speed) {
        
        // Vector of tuples holding the (start position, travel time to target) for
        // each car.
        int nCars = position.size();
        vector<pair<int, double> > startPosTravelTimePairV(nCars);
        for (int i = 0; i != nCars; ++i) {
            auto & startLoc = position[i];
            double virtualTravelTime = double(target - startLoc) / speed[i];
            startPosTravelTimePairV[i] = pair<int, double>(startLoc, virtualTravelTime);
        }
        
        // Now sort the tuples vector on the basis of location in ascending order
        sort(startPosTravelTimePairV.begin(), startPosTravelTimePairV.end());
        
        // Iterate through the sorted car start position/virtual travel time
        // tuples array sequentially from target to 0 -- i.e from cars closest to
        // target to cards farthest from target, since car near destination blocks
        // car coming up its rear
        int i = nCars - 1;
        int nCarFleet = 0;
        while (i >= 0) {
            auto & currCarInfo = startPosTravelTimePairV[i];
            double timeToReachTargetForCurrCar = currCarInfo.second;
            ++nCarFleet; // New car fleet commences with this car
            
            // All cars at rear of this car which catch up by the time it reaches
            // destination would form a fleet with this car. Skip all cars at
            // the rear of current car which will form a fleet with this car
            int j = i - 1;
            while (j >= 0) {
                if (startPosTravelTimePairV[j].second > timeToReachTargetForCurrCar) {
                    // This particular car at rear of current car requires more time
                    // to reach destination than current car 'i', so cars in range
                    // [0, j] are not a part of this fleet
                    break;
                } 
                // Car 'j' at rear of current car requires same or lesser
                // time to reach destination than current car 'i', so it is
                // a part of current car 'i' fleet
                // Advance to previous car
                --j;
            }
            
            // Advance to previous located car for next fleet formation
            i = j;
        }
        
        return nCarFleet;
    }
};
