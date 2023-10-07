// Time complexity : O(nk(m^2))
// Space complexity : O(nkm)

const int moduloFactor = 1000000000 + 7;

class Solution {
public:
    int
    numOfArrays(int n, int m, int k) {
        // Problem reduces to finding the number of arrays of size 'n' which can be
        // built using elements in the range [1, m] with exactly 'k' maximums on
        // scanning the array sequentially from L->R
        
        // Since there are multiple options to build the array, employ DP to cache stored
        // computations while exploring options
        
        return numOfArraysViaTopDownMemoization(n, m, k);
    }
    
private:
    
    int
    numArraysViaTopDownMemoizationRec(int nextIdx, int maxSeenSoFar, int nRemainingMax) {
        
        // Determine the number of candidate arrays extending over [nextIdx, _arrSz - 1]
        // with values [1, _maxElem] having exactly 'nRemainingMax' maximums on scanning
        // from L->R over subrange with all maximum values g.t. 'maxSeenSoFar'
        if (nextIdx >= _arrSz) {
            // Array size [0, nextIdx - 1] is max allowed size
            // If it already has '_nMaximums', there will be 0 remianing maximums and
            // array is valid candidate array, otherwise no
            return 0 == nRemainingMax ? 1 : 0;
        }
        
        if (nRemainingMax < 0) {
            return 0;
        }
        
        if (-1 == _memoTbl[nextIdx][maxSeenSoFar][nRemainingMax]) {
            // State not hit earlier => compute it
            
            // 2 options possible
            // 1) 'nextIdx' does not have a max value
            // 'nextIdx' value possibilities over the range [1, maxSeenSoFar] as it
            // has to be l.e the 'maxSeenSoFar' encountered over [0, nextIdx - 1]
            long nArrays = 0;
            for (auto val = 1; val <= maxSeenSoFar; ++val) {
                nArrays += 
                    numArraysViaTopDownMemoizationRec(nextIdx + 1, maxSeenSoFar, nRemainingMax);
                nArrays %= moduloFactor;
            }

            // 2) 'nextIdx' has a max value
            // 'nextIdx' value possibilities over therange [maxSeenSoFar + 1, _maxElem]
            // as it has to be g.t the 'maxSeenSoFar' encountered over [0, nextIdx - 1]
            for (auto val = maxSeenSoFar + 1; val <= _maxElem; ++val) {
                nArrays += numArraysViaTopDownMemoizationRec(nextIdx + 1, val, nRemainingMax - 1);
                nArrays %= moduloFactor;
            }
            
            // Update cache with number of candidate arrays possible
            _memoTbl[nextIdx][maxSeenSoFar][nRemainingMax] = nArrays;
        }
        
        return _memoTbl[nextIdx][maxSeenSoFar][nRemainingMax];
    }
    
    int
    numOfArraysViaTopDownMemoization(int n, int m, int k) {
        // Init
        _arrSz = n;
        _maxElem = m;
        _nMaximums = k;
        _memoTbl.resize(
            _arrSz, vector<vector<int> >(_maxElem + 1, vector<int>(_nMaximums + 1, -1)));

        // Recursively compute all options
        return numArraysViaTopDownMemoizationRec(0, 0, _nMaximums);
    }
    
    // Data members
    // Fixed array size of candidate array to be built
    int _arrSz;
    // Candidate array range [1, _maxElem]
    int _maxElem; 
    // Number of maximums encountered on an L->R scan of candidate array
    int _nMaximums;
    
    // _memoTbl[i][maxSeenSoFar][nRemMax] is the number of candidate arrays extending over
    // indices [i, _arrSz - 1] with 'nRemMax' maximums on scanning from L->R in the range
    // with a max value of 'maxSeenSoFar' seen earlier over range [0, i - 1]
    vector<vector<vector<int> > > _memoTbl;
};
