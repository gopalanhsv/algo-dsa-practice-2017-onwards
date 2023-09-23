// n => time.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    int
    numPairsDivisibleBy60(vector<int>& time) {
        // If A & B are 2 numbers (number equivalent to song durations) s.t.
        // A = 60q1 + r1, B = 60q2 + r2, where q1/q2 are quotients and r1/r2
        // are remainders
        // A + B = 60(q1 + q2) + r1 + r2
        // => (A + B) % 60 is 0 if and only if (r1 + r2) % 60 is 0
        // That is, sum of any song pair duration is divisible by 60
        // if and only the sum of their remainders is divisible by 60
        
        // So we need to work only with remainders of the song durations and this
        // reduces to a variant of the two sum problem
        // Build an occurence count table of all the song pair durations
        // (remainder post divison by 60) 
        unordered_map<int, long long> durationToOccurenceCntTbl;
        for (auto & duration : time) {
            durationToOccurenceCntTbl[duration % 60]++;
        }

        auto nSongPairs = 0;
        // Iterate through each of the song durations (duration % 60) sequentially
        for (auto & entry : durationToOccurenceCntTbl) {
            // Current song duration (duration % 60)
            auto & duration = entry.first;
            // Compute the duration (duration % 60) of songs with which pairing is possible
            // (remainder duration for 0 is a unique case for song having durations of 60x)
            auto pairDuration = (duration != 0) ? 60 - duration : 0;
            auto iter = durationToOccurenceCntTbl.find(pairDuration);
            if (iter != durationToOccurenceCntTbl.end()) {
                // Pairing possible with current song(s)
                auto & cnt1 = entry.second;
                auto & cnt2 = iter->second;
                // Every song with remainder duration 'duration' forms a pair with the
                // songs with remainder duration 'pairDuration', except for the duration
                // pair 30 + 30 OR 60 multiple (these have same entry for pairs)
                if (duration == 30 || duration == 0) {
                    // Songs with a remiander duration of 0/30 form pairs with other
                    // unique songs with a remiander duration of 0/30 respectively
                    // Fallback to n-choose-2 formula
                    nSongPairs += (cnt1 * (cnt1 - 1)) / 2;
                } else {
                    nSongPairs += (cnt1 * cnt2);
                }
                
                // Update the pair duration hash table entry to avoid double counting
                iter->second = 0;
            }
        }
        
        return nSongPairs;
    }
};
