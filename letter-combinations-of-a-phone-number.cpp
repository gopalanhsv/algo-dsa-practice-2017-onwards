// n => digits.size()
// Time complexity : O(n x (4 ^ n)) (assuming max of 4 letters mapped per digit)
// Space complexity : O(n)
class Solution {
public:
    vector<string>
    letterCombinations(string digits) {
        if (digits.empty()) {
            return vector<string>();    
        }
        
        // Initialize
        init();
        
        // Generate all possible letter combination for the given
        // digit string via DFS
        vector<string> outV;
        letterCombinationsDFS(digits, 0, outV);
        
        return outV;
    }

private:
    
    void
    init() {
        
        // Init the string tracking current letter combination being formed
        _currStr = "";
        
        // Init the hash table mapping digits to letters
        _digitsToLetterTbl['2'] = {'a', 'b', 'c'};
        _digitsToLetterTbl['3'] = {'d', 'e', 'f'};
        _digitsToLetterTbl['4'] = {'g', 'h', 'i'};
        _digitsToLetterTbl['5'] = {'j', 'k', 'l'};
        _digitsToLetterTbl['6'] = {'m', 'n', 'o'};
        _digitsToLetterTbl['7'] = {'p', 'q', 'r', 's'};
        _digitsToLetterTbl['8'] = {'t', 'u', 'v'};
        _digitsToLetterTbl['9'] = {'w', 'x', 'y', 'z'};
    }
    
    void
    letterCombinationsDFS(string& digits, int digitIdx,
                          vector<string> & outV) {
        
        if (digitIdx == digits.size()) {
            // All digits processed for this DFS branch
            outV.emplace_back(_currStr);
            return;
        }
        
        // Letters associated with current digit 
        auto & lettersV = _digitsToLetterTbl[digits[digitIdx]];

        // Iterate over all letters associated with current digit
        for (auto & l : lettersV) {
            
            // Add current letter to current combination string and explore
            // subsequent digits
            _currStr.push_back(l);
            letterCombinationsDFS(digits, digitIdx + 1, outV);
            
            // Backtrack and remove current letter from current combination string
            _currStr.pop_back();
        }
    }
    
    // Data members
    
    // Tracks the current letter combination string being formed during DFS
    string _currStr;
    // Hash table mapping phone number digits to the associated letters
    unordered_map<char, vector<char> > _digitsToLetterTbl;
};
