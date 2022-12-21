class Solution {
public:
    int
    assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        
        return assignBikesDFS(workers, bikes);
    }
    
private:
    
    inline int
    manhattanDist(vector<vector<int>>& workers, vector<vector<int>>& bikes,
                  int wId, int bId) {
        return abs(workers[wId][0] - bikes[bId][0]) + 
            abs(workers[wId][1] - bikes[bId][1]);
    }
    
    void
    assignBikesDFS(vector<vector<int>>& workers, vector<vector<int>>& bikes,
                   int workerId, int currDistSum) {
        
        if (currDistSum >= _minTaxiDistSum) {
            return;
        }
        
        if (workerId == _nWorkers) {
            _minTaxiDistSum = min(_minTaxiDistSum, currDistSum);
            return;
        }
        
        for (int bikeId = 0; bikeId != _nBikes; ++bikeId) {
            if (!_bikeAssignedV[bikeId]) {
                _bikeAssignedV[bikeId] = true;
                assignBikesDFS(workers, bikes, workerId + 1,
                               currDistSum + _distV[workerId][bikeId]);
                _bikeAssignedV[bikeId] = false;
            }
        }
    }

    void
    init(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        _minTaxiDistSum = numeric_limits<int>::max();
        _nWorkers = workers.size();
        _nBikes = bikes.size();
        _bikeAssignedV.resize(_nBikes, false);
        
        _distV.resize(_nWorkers, vector<int>(_nBikes));
        for (int wId = 0; wId != _nWorkers; ++wId) {
            for (int bId = 0; bId != _nBikes; ++bId) {
                _distV[wId][bId] =
                    manhattanDist(workers, bikes, wId, bId);
            }
        }
    }

    int
    assignBikesDFS(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        
        init(workers, bikes);
        int workerId = 0;
        int currDistSum = 0;
        assignBikesDFS(workers, bikes, workerId, currDistSum);
        
        return _minTaxiDistSum;
    }
    
    // Data members
    int _nWorkers;
    int _nBikes;
    int _minTaxiDistSum;
    vector<bool> _bikeAssignedV;
    vector<vector<int> > _distV;
};
