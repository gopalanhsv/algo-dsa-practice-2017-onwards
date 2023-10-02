// Time complexity : O(colors.size())
// Space complexity : O(1)

class Solution {
public:
    bool
    winnerOfGame(string colors) {
        // An 'A' can be removed only by Alice i.f.f there are 2 'A's adjacent to it;
        // A 'B' can be removed only by Bob i.f.f there are 2 'B's adjacent to it 
        // => Alice's moves are unaffected by Bob's moves as Bob cannot rearrange/touch any
        // of the 'A''s which are removable by Alice since these 'A's have an 'A' wall; AND
        // Bob's moves are unaffected by Alice's moves as Alice cannot rearrange/touch any
        // of the 'B''s which are removable by Bob since these 'B's have an 'B' wall
        
        // Num moves possible for Alice is the number of 'A''s enclosed between 2 'A' walls +
        // Num moves possible for Bob is the number of 'B''s enclosed between 2 'B' walls
        auto colorSz = colors.size();
        // Compute the possible number of removals both for Alice and Bob  
        auto nAliceMoves = 0;
        auto nBobMoves = 0;
        for (auto i = 2; i < colorSz; ++i) {
            if (('A' == colors[i]) && ('A' == colors[i - 1]) && ('A' == colors[i - 2])) {
                // Color at 'i - 1' is removable by Alice
                ++nAliceMoves;
            }
            if (('B' == colors[i]) && ('B' == colors[i - 1]) && ('B' == colors[i - 2])) {
                // Color at 'i - 1' is removable by Bob
                ++nBobMoves;
            }
        }

        // Alice gets first turn to move,
        // => Alice always wins if number of Alice's possible turns exceeds that of Bobs'; AND
        // Bob always wins if number of Bob's possible turns exceeds or equals that of Alices'
        // They above also works if Alice cannot do any removals as in this particular case
        // Bob wins by default as Bob's moves will be g.e that of Alice
        return nAliceMoves > nBobMoves ? true : false;
    }
};
