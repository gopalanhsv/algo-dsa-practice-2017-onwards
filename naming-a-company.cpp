class Solution {
public:
    long long
    distinctNames(vector<string>& ideas) {
    
        int nUniqueNames = ideas.size();
        
        // Each of the name can be split into 1st letter and the
        // remaining letters as follows
        // idea = prefix of 1 letter + suffix of remaining letters
        
        // Group each of the idea words by the first letter prefix
        // via a hash table
        const int nFirstLetters = 26;
        
        // Hash table mapping the possible first letter prefix
        // to the set of unique idea suffixes for idea words 
        // with that first letter
        vector<unordered_set<string> > pfxToUniqSuffixesTbl('a' + nFirstLetters);
        for (auto & idea : ideas) {
            pfxToUniqSuffixesTbl[idea[0]].insert(idea.substr(1));
        }

        // Number of distinct valid company names
        long long nValidNames = 0;
        
        for (char A = 'a'; A < 'z'; ++A) {
            
            auto & uniqSuffixesWithPfxA = pfxToUniqSuffixesTbl[A];
            if (uniqSuffixesWithPfxA.empty()) {
                continue;
            }            
            long long nUniqSuffixesWithPfxA = uniqSuffixesWithPfxA.size();
            
            for (char B = A + 1; B <= 'z'; ++B) {
             
                auto & uniqSuffixesWithPfxB = pfxToUniqSuffixesTbl[B];
                if (uniqSuffixesWithPfxB.empty()) {
                    continue;
                }            
                long long nUniqSuffixesWithPfxB = uniqSuffixesWithPfxB.size();
                
                int nCommonSuffixesWithPfxAPfxB = 0;
                for (auto & suffixWithPfxA : uniqSuffixesWithPfxA) {
                    if ((uniqSuffixesWithPfxB.count(suffixWithPfxA) > 0)) {
                        ++nCommonSuffixesWithPfxAPfxB;
                    }
                }
                
                nValidNames += 
                    (nUniqSuffixesWithPfxA - nCommonSuffixesWithPfxAPfxB) *
                    (nUniqSuffixesWithPfxB - nCommonSuffixesWithPfxAPfxB);
            }
        }
        
        return nValidNames * 2;
    }
};
