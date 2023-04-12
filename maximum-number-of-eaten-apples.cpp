// n = apples.size()/days.size()
// Time complexity : O(nlogn)
// Space complexity : O(n)
class Solution {
public:
    int
    eatenApples(vector<int>& apples, vector<int>& days) {
        // Adopt the greedy strategy of maximising the number of apples available at
        // any day; to ensure that an apple is always present in the store to be
        // eaten (as per feasibility). This is easily done by ensuring that at any
        // given time, apples which rot/expire earlier are consumed prior to those
        // which rot/expire later -- leading to max number of apples being available
        // in hand at any given time
        
        // The above is easily accomplished by storing the unconsumed apples in a
        // heap/PQ; with those expiring earlier being at front of Q compared to
        // those expiring later
        // Tracks the info about a set/bunch of apples which grow on the
        // tree on a particular day
        typedef struct _AppleBunchInfoT {
            // number of apples in the current bunch
            int nApples;
            // Last day on which the current bunch stays fresh
            int expiryDay;
        } AppleBunchInfoT;
        struct AppleBunchCmpObj {
            bool
            operator()(AppleBunchInfoT& abi1, AppleBunchInfoT& abi2) {
                // Apples towards the end/bottom of the heap/PQ expire later
                // compared to those at front/top => apples which rot earlier
                // are selected for eating earlier
                return  abi1.expiryDay > abi2.expiryDay;
            }
        };
        // PQ/heap which models the apple storeroom
        priority_queue<AppleBunchInfoT, vector<AppleBunchInfoT>, AppleBunchCmpObj> appleStorePQ;
        
        int nApplesConsumed = 0;
        // Iterate over each of the days in sequence
        int nDays = apples.size();
        for (int d = 0; d != nDays; ++d) {
            
            // Add todays bunch to the apple storeroom
            if ((apples[d] > 0) && (days[d] > 0)) {
                // Params for the current bunch of apples grown on current day
                AppleBunchInfoT abInfo;
                abInfo.nApples = apples[d];
                abInfo.expiryDay = days[d] + d - 1;
                appleStorePQ.push(abInfo);
            }
            
            // Dump all rotten apples in the storeroom till a fresh apple bunch
            // (if any) is found. Eat an apple from the fresh bunch
            while (!appleStorePQ.empty()) {
                // Select the apple bunch which rots earliest
                auto appleBunch = appleStorePQ.top();
                appleStorePQ.pop();
                if (appleBunch.expiryDay >= d) {
                
                    // Found a fresh apple bunch. Select one apple for eating
                    // and add bunch back to store
                    ++nApplesConsumed;
                    
                    if ((--appleBunch.nApples > 0) && (appleBunch.expiryDay > d)) {
                        appleStorePQ.push(appleBunch);
                    }
                    // Move to next day
                    break;
                }
            }
        }

        // Consume the apples remaining in the storeroom, preferring apples
        // which expire earlier
        int dayId = nDays;
        // Dump all rotten apples in the storeroom till a fresh apple bunch
        // (if any) is found. Eat an apple from the fresh bunch
        while (!appleStorePQ.empty()) {
            // Select the apple bunch which rots earliest
            auto & appleBunch = appleStorePQ.top();
            if (appleBunch.expiryDay >= dayId) {
                // Found a fresh apple bunch. Select the max apples possible
                // from this bunch to eating
                int nSelectedApples =
                    min(appleBunch.nApples, appleBunch.expiryDay - dayId + 1);
                nApplesConsumed += nSelectedApples;
                // Advance day counter by the number of apples selected in this bunch
                dayId += nSelectedApples;
            }
            
            // Done with the current apple bunch
            appleStorePQ.pop();
        }

        return nApplesConsumed;
    }
};
