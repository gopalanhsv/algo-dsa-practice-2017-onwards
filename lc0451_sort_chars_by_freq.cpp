class Solution {
public:
    string
    frequencySort(string s) {
        // Construct character to frequency table
        unordered_map<char, int> charFreqTbl;
        for (auto & c : s) {
            charFreqTbl[c]++;
        }
        
        // Convert the frequency count table of <char, frequency> mappings to
        // reverse mapping of frequency count to character list s.t chars
        // of same frequency get grouped together
        unordered_map<int, vector<char> > freqToCharTbl;
        int maxFreq = 0;
        for (auto & hte : charFreqTbl) {
            // hte => hash table entry
            freqToCharTbl[hte.second].emplace_back(hte.first);
            if (hte.second > maxFreq) {
                maxFreq = hte.second;
            }
        }
        
        // Iterate the freq to char list mappings in descending order of frequency count
        string sortedStr;
        for (int freq = maxFreq; freq >= 1; --freq) {
            auto iter = freqToCharTbl.find(freq);
            if (iter != freqToCharTbl.end()) {
                auto & vc = iter->second;
                for (auto c : vc) {
                    sortedStr += string(freq, c);
                }
            }
        }
        
        return sortedStr;
    }
};
