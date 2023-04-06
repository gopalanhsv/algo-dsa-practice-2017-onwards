// Time complexity
// O(num words)
// Space complexity
// O(1)

class Solution {
public:
    int
    shortestWordDistance(vector<string>& wordsDict, string word1, string word2) {
        // Separating out the code for the cases of the two words being same
        // and different for both performance and code complexity reduction
        if (word1 == word2) {
            // Words are same
            return shortestWordDistanceSameWords(wordsDict, word1);
        }
        
        // Words are different
        return shortestWordDistanceDiffWords(wordsDict, word1, word2);
    }
    
private :

    int
    shortestWordDistanceDiffWords(vector<string>& words, string& w1, string& w2) {
        int nWords = words.size();
        
        // Iterate over the words in the dictionary sequentially
        // Locate the first occurrence of 'word1' OR 'word2' whichever
        // comes second; and the other word (not the first occurence of
        // either of the two which comes second), which occurs prior to it
        int wIdx = 0;
        int w1Idx = -1;
        int w2Idx = -1;
        while ((wIdx < nWords) &&
               ((-1 == w1Idx) || (-1 == w2Idx))) {
            
            // Current word
            auto & cw = words[wIdx];
            if (cw == w1) {
                w1Idx = wIdx;
            } else if (cw == w2) {
                w2Idx = wIdx;
            }
            
            // Advance to next word
            ++wIdx;
        }
        
        // Minimum distance between the successive occurences of words 'w1' & 'w2'
        // updated to the first of the closest consecutive occurence of 'w1' & 'w2'
        int minDist = abs(w1Idx - w2Idx);

        // Iterate over the remainder of the words sequentially
        for (; wIdx < nWords; ++wIdx) {
            
            // Current word
            auto & cw = words[wIdx];
            
            if (cw == w1) {
                // 'w1' hit
                // Update the previous occurrence location of 'w1' to current location
                w1Idx = wIdx;
                // Compute the distance between current occurrence of 'w' and
                // previous occurrence of 'w2'. Update the minimum distance
                minDist = min(minDist, wIdx - w2Idx);
            } else if (cw == w2) {
                // 'w2' hit
                // Update the previous occurrence location of 'w2' to current location
                w2Idx = wIdx;
                // Compute the distance between current occurrence of 'w' and
                // previous occurrence of 'w1'. Update the minimum distance
                minDist = min(minDist, wIdx - w1Idx);
            }
        }
        
        return minDist;
    }
    
    int
    shortestWordDistanceSameWords(vector<string>& words, string& w) {
        int nWords = words.size();
        int prevWordIdx = -1;
        int minDist = numeric_limits<int>::max();
        // Iterate over the words sequentially
        for (int wIdx = 0; wIdx < nWords; ++wIdx) {
            // Current word
            auto & cw = words[wIdx];
            if (cw == w) {
                // Current words is identical to specified
                if (-1 != prevWordIdx) {
                    // Compute the distance between successive occurences of the word 'w'
                    // and update the min distance between the words
                    minDist = min(minDist, wIdx - prevWordIdx);
                }
                // Update the previous location of word 'w'
                prevWordIdx = wIdx;
            }
        }
        
        return minDist;
    }
};
