// n => details.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    int
    countSeniors(vector<string>& details) {
        // Since seat/phone numbers are distinct, use either of the two to filter out
        // duplicate entries. Using the seat number as it has only 2 digits => less processing
        // 'Seat number' at chars 13, 14
        const int seatIdxOffset = 13;
        // 'Age' at chars 11, 12
        const int ageIdxOffset = 11;
        int nSeniors = 0;
        // Hash table of senior passengers already processed
        unordered_set<int> seenSeatsTbl;
        // Process each passenger
        for (auto & detail : details) {
            auto age = 
                int(detail[ageIdxOffset] - '0') * 10 + int(detail[ageIdxOffset + 1] - '0');
            if (age <= 60) {
                // Filter out non-seniors
                continue;
            }
            // Filter out duplicate senior passsengers based on seat numbers
            auto seatId =
                int(detail[seatIdxOffset] - '0') * 10 + int(detail[seatIdxOffset + 1] - '0');
            if (seenSeatsTbl.find(seatId) == seenSeatsTbl.end()) {
                // New senior passenger
                seenSeatsTbl.insert(seatId);
                ++nSeniors;
            }
        }
        
        return nSeniors;
    }
};
