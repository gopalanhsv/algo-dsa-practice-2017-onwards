class Solution {
public:
    int
    calculateTime(string keyboard, string word) {
    
        // Build a hash table of keyboard keys to their locations
        //unordered_map<char, int> kbCharToLocationTbl;
        //for (int locId = 0; locId != keyboard.size(); ++locId) {
        //    kbCharToLocationTbl[keyboard[locId]] = locId;
        //}
        // Hash table built using vector as problem has constraint of all lower
        // case english letters; we do 'a' + business to avoid unnecessary
        // for normalization for each character
        vector<int> kbCharToLocationTbl('a' + 26, 0);
        int locId = 0;
        for (auto & kbChar : keyboard) {
            kbCharToLocationTbl[kbChar] = locId++;
        }
        
        // Iterate through each character in word sequentially and determine the
        // amount of time take to move to that char from previous char. Add all
        // times up
        int totalTime = 0;
        int prevFingerLocation = 0;
        for (auto & k : word) {
            auto & currLocation = kbCharToLocationTbl[k];
            totalTime += abs(currLocation - prevFingerLocation);
            prevFingerLocation = currLocation;
        }
        
        return totalTime;
    }
};
