class Solution {
public:
    string
    getHint(string secret, string guess) {
        
        //return getHintTwoPass(secret, guess);
        return getHintOnePass(secret, guess);
    }
    
private:
    
    string
    getHintOnePass(string& secret, string& guess) {
        // Maintain 2 tables having frequency count for all non matching
        // characters in the guess and secret string
        vector<int> nonMatchSecretCharFreqCntTbl('0' + 10, 0);
        vector<int> nonMatchGuessCharFreqCntTbl('0' + 10, 0);
        int nBulls = 0;
        int nCows = 0;
        
        // Examine each char of secret and guess in tandem
        for (int i = 0; i != secret.size(); ++i) {
            auto & secretChar = secret[i];
            auto & guessChar = guess[i];
            if (secretChar == guessChar) {
                // Match between guess and secret char => bull
                ++nBulls;
            } else {
                // Mismatch between guess and secret char
                // Check for cow
                
                if (nonMatchSecretCharFreqCntTbl[guessChar] > 0) {
                    // Current guess char was seen earlier in the secret string
                    // Cow found
                    ++nCows;
                    // Decrement the frequency count of found char in secret string
                    // frequency count table to account for matched cow
                    --nonMatchSecretCharFreqCntTbl[guessChar];
                } else {
                    // Increment frequency count of guess char in guess string frequency count table
                    ++nonMatchGuessCharFreqCntTbl[guessChar];
                }
                
                if (nonMatchGuessCharFreqCntTbl[secretChar] > 0) {
                    // Current secret char was seen earlier in the guess string
                    // Cow found
                    ++nCows;
                    // Decrement the frequency count of found char in guess string
                    // frequency count table to account for matched cow
                    --nonMatchGuessCharFreqCntTbl[secretChar];
                } else {
                    // Increment frequency count of secret char in secret string frequency count table
                    ++nonMatchSecretCharFreqCntTbl[secretChar];
                }
            }
        }
        
        return to_string(nBulls) + "A" + to_string(nCows) + "B";
    }
    
    string
    getHintTwoPass(string& secret, string& guess) {
        // Build a hash table of the secret string character frequency
        // count (excluding the characters which have a positional
        // match between guess and secret)
        int nBulls = 0;
        vector<int> nonMatchCharFreqCntTbl('0' + 10, 0);
        for (int i = 0; i != guess.size(); ++i) {
            auto & secretChar = secret[i];
            if (secretChar == guess[i]) {
                // Current char is present in guess and secret at same
                // location - so is a bull
                ++nBulls;
            } else {
                // Mismatch between guess and secret. Update the frequency count
                nonMatchCharFreqCntTbl[secretChar]++;
            }
        }
        
        int nCows = 0;
        // Iterate through the chars in the guess string sequentially
        for (int i = 0; i != guess.size(); ++i) {
            auto & guessChar = guess[i];
            if (guessChar != secret[i]) {
                // Current guess char is not matching with secret.
                // Check if there is an instance of this char in
                // the guess in a non matching location
                if (nonMatchCharFreqCntTbl[guessChar] > 0) {
                    ++nCows;
                    // Update frequency count table to update
                    // for this char becoming a cow. Dont want
                    // stale stuff
                    --nonMatchCharFreqCntTbl[guessChar];
                }
            }
        }
        
        return to_string(nBulls) + "A" + to_string(nCows) + "B";
    }
        
};
