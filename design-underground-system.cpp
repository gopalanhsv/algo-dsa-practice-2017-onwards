// Time complexity : O(1) for all calls
// Space complexity : O(num journeys in progress) + O(num src and dst station pairs)

class UndergroundSystem {
    
    // Object which tracks trip data for a particular start and end station pair
    typedef struct _TripInfoT {
        // Running average of all journey times for all trips made
        // between a particular start and end station
        double averageTransitTime;
        // Number of customers who have done the journey between
        // the start and end station
        int nCustomersTransited;
    } TripInfoT;
    
public:
    UndergroundSystem() {
    }
    
    void
    checkIn(int id, string stationName, int t) {
        // Add data of the new starting trip to hash table
        // holding data of trips currently in progress
        _checkinInfoTbl[id] = pair<string, int>(stationName, t);
    }
    
    void
    checkOut(int id, string stationName, int t) {
        // Find the journey start details for the customer from
        // table holding data of journeys currently in progress
        auto iter = _checkinInfoTbl.find(id);
        auto & customerCheckinInfo = iter->second;
        
        auto & srcStn = customerCheckinInfo.first;
        // Compute the trip/journey time for this trip
        // Get the start and end stations
        auto & checkInTime = customerCheckinInfo.second;
        auto tripTime = t - checkInTime;
        auto & dstStn = stationName;
        
        // Update the average time for trip between the start and
        // end station (for this particular journey) with the current
        // trip details. Also increment the number of customers
        // for this same journey
        auto & srcDstTripInfo = _tripInfoTbl[srcStn][dstStn];
        srcDstTripInfo.averageTransitTime = 
            (srcDstTripInfo.averageTransitTime * srcDstTripInfo.nCustomersTransited + tripTime) /
            (++srcDstTripInfo.nCustomersTransited);
        
        // Remove the data for this trip from current journeys in progress
        // for optimal memory usage
        _checkinInfoTbl.erase(iter);
    }
    
    double
    getAverageTime(string startStation, string endStation) {
        return _tripInfoTbl[startStation][endStation].averageTransitTime;
    }
    

private:
    // Data members
    
    // Hash table holding the data of current journeys in progress
    // Maps <customer id> ===> <start station, journey start time>
    unordered_map<int, pair<string, int> > _checkinInfoTbl;
    
    // Hash table holding the journey data for each start/end station pair
    // between which a journey has been done in the system
    // Maps (start station, end station) ==> journey data
    unordered_map<string, unordered_map<string, TripInfoT> > _tripInfoTbl; 
};

/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */
