// f => flowers.size(), p => persons.size()
// Time complexity : O(flogf + plogf)
// Space complexity : O(f)

class Solution {
public:
    vector<int>
    fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& persons) {
        processBloomEvents(flowers);
        
        int nPeople = persons.size();
        vector<int> nBloomedFlowersV(nPeople);
        for (int i = 0; i != nPeople; ++i) {
            auto & arrivalTime = persons[i];
            nBloomedFlowersV[i] = numBloomedFlowersAtTimeInstant(arrivalTime);
        }

        return nBloomedFlowersV;
    }
    
private:
    
    void
    processBloomEvents(vector<vector<int>>& flowers) {
        // Iterate over the bloom events and store them in non-decreasing order of time
        map<int, int> bloomEventsTbl;
        for (auto & flower : flowers) {
            auto & st = flower[0];
            auto & et = flower[1];
            // Current flower is in full bloom over time [st, et]
            // => Number of flowers in full bloom increases
            // by 1 at time 'st' & decreases by 1 at time 'et'
            bloomEventsTbl[st] += 1;
            bloomEventsTbl[et + 1] -= 1;
        }

        // Iterate over the bloom event in the ascending order of time.
        // Compute the number of flowers in full bloom at each event
        // time using prefix sum technique
        int nFlowersInBloom = 0;
        _firstEventTime = (bloomEventsTbl.begin())->first;
        for (auto & entry : bloomEventsTbl) {
            auto & eventTime = entry.first;
            auto & nFlowersDelta = entry.second;
            nFlowersInBloom += nFlowersDelta;
            _eventTimeToNumFlowersTbl[eventTime] = nFlowersInBloom;
        }
    }
    
    int
    numBloomedFlowersAtTimeInstant(int time) {
        // Lookup the number of flowers in full bloom at time instant 'time'
        // via binary search 
        auto lbIter = _eventTimeToNumFlowersTbl.lower_bound(time);
        if ((lbIter == _eventTimeToNumFlowersTbl.end()) ||
            (time < _firstEventTime)) {
            // 'time' is out of range of flowers in full bloom
            return 0;
        }
        
        if ((lbIter->first) > time) {
            --lbIter;
        }
        
        return lbIter->second;
    }
    
    // Data members
    // RB-tree/BST table mapping an event time (full bloom start/end) to
    // the number of flowers in full bloom at that instant
    map<int, int> _eventTimeToNumFlowersTbl;
    // Occurence time of first bloom event
    int _firstEventTime;
};
