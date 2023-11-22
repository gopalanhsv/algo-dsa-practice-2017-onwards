// n => num dictionary words (including dups)
// n1 => max number of instances/indices of a word in dictionary
// n2 => second max number of instances/indices of a word in dictionary
// Time complexity :
// Constructor : O(n)
// M => num calls to shortest
// shortest() : O(M(n1 + n2))
// Space complexity : O(n)

class WordDistance {
public:
    WordDistance(vector<string>& wordsDict) {
        // Insert all the dictionary words into a hash table along
        // with their array index locations
        int idx = 0;
        for (auto & word : wordsDict) {
            _wordToIndicesTbl[word].emplace_back(idx);
            ++idx;
        }
    }
    
    int
    shortest(string word1, string word2) {
        auto iter1 = _wordToIndicesTbl.find(word1);
        auto iter2 = _wordToIndicesTbl.find(word2);
        if ((iter1 == _wordToIndicesTbl.end()) ||
            (iter2 == _wordToIndicesTbl.end())) {
            // One/both of the words not present in table
            return -1;
        }
        
        // Get the sorted list of word locations for both
        auto & w1IdxV = iter1->second;
        auto & w2IdxV = iter2->second;
        
        // Since arranging of the indices in sorted order places the closest
        // indices adjacent to each other, employ merge operation (merge sort)
        // to go through 2 different sorted arrays and compute the shortest
        // distance between 2 array values (word indices) lying in 2 sorted arrays
        auto arr1Sz = w1IdxV.size();
        auto arr2Sz = w2IdxV.size();
        auto i = 0;
        auto j = 0;
        auto minDist = numeric_limits<int>::max();
        // Adjust indices 'i' & 'j' at each step in orderd to
        // make w1IdxV[i] as close to w2IdxV[j] as possible
        while ((i < arr1Sz) && (j < arr2Sz)) {
            auto w1Idx = w1IdxV[i];
            auto w2Idx = w2IdxV[j];
            minDist = min(minDist, abs(w1Idx - w2Idx));
            if (w1Idx < w2Idx) {
                ++i;
            } else if (w1Idx > w2Idx) {
                ++j;
            } else {
                break;
            }
        }
        return minDist;
    }

private:
    
    // Data members
    // Hash table mapping each word in dictionary to the list of array indices
    // where word is located, with the indices arranged in ascending order
    unordered_map<string, vector<int> > _wordToIndicesTbl;
};

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance* obj = new WordDistance(wordsDict);
 * int param_1 = obj->shortest(word1,word2);
 */
