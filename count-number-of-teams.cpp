// n => rating.size()
// Brute force
// Time complexity : O(n ^ 2)
// Space complexity : O(1)

class Solution {
public:
    int
    numTeams(vector<int>& rating) {
        return numTeamsBruteForce(rating);
    }

private:
    
    int
    numTeamsBruteForce(vector<int>& ratingV) {
        // Since we need to select soldiers i, j, k
        // s.t. i < j < k <=n
        // For case R[i] < R[j] < R[k], where R[x] = rating of soldier at index 'x'
        // num teams = num soldiers in [1, j - 1] with rating < R[j] multiplied by
        //             num soldiers in [j + 1, n] with rating > R[j]
        // For case R[i] > R[j] > R[k], where R[x] = rating of soldier at index 'x'
        // num teams = num soldiers in [1, j - 1] with rating > R[j] multiplied by
        //             num soldiers in [j + 1, n] with rating < R[j]
        
        // 1. Select middle soldier with rating R
        // 2. Soldier to left of middle with rating < R can be paired with
        //    soldiers to right of middle with rating > R 
        // 3. Soldier to left of middle with rating > R can be paired with
        //    soldiers to right of middle with rating < R 
        
        int nTeams = 0;
        auto nSoldiers = ratingV.size();
        // Select middle soldier 'j'
        for (auto j = 1; j <= nSoldiers - 2; ++j) {
            // Compute the number of all possible soldiers to left of 'j'
            // That is, all soldiers 'i' with rating R[i] s.t.
            // (1) R[i] < R[j] (2) R[i] > R[j]
            int nGreaterRatingsToLeft = 0;
            int nLowerRatingsToLeft = 0;
            for (auto i = 0; i < j; ++i) {
                if (ratingV[i] < ratingV[j]) {
                    ++nLowerRatingsToLeft;
                } else {
                    ++nGreaterRatingsToLeft;
                }
            }

            // Compute the number of all possible soldiers to right of 'j'
            // That is, all soldiers 'k' with rating R[k] s.t.
            // (1) R[k] < R[j] (2) R[k] > R[j]
            int nGreaterRatingsToRight = 0;
            int nLowerRatingsToRight = 0;
            for (auto k = j + 1; k < nSoldiers; ++k) {
                if (ratingV[j] < ratingV[k]) {
                    ++nGreaterRatingsToRight;
                } else {  
                    ++nLowerRatingsToRight;              
                }
            }
            // Compute the number of possible teams with middle soldier at 'j'
            nTeams += 
                (nLowerRatingsToLeft * nGreaterRatingsToRight +
                 nGreaterRatingsToLeft * nLowerRatingsToRight);
        }
        
        return nTeams;
    }
};
