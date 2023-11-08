// P => max players seen so far
// M => max unique scores seen so far
// n => num calls

// Space complexity : O(P + M)

// addScore()/reset()
// Time complexity : O(nlogM)
// top()
// Time complexity : O(nKlogM)

class Leaderboard {
public:
    Leaderboard() {
        
    }
    
    void
    addScore(int playerId, int score) {
        
        // Clear the pre-existing mappings/table entries for 'playerId'
        auto oldScore = resetPlayerEntry(playerId, false);
        // Determine updated score
        auto newScore = oldScore + score;
        // Update table entries for 'playerId'
        _playerToScoreTbl[playerId] = newScore;
        _scoresToPlayerCntTbl[newScore]++;
        
    }
    
    int
    top(int K) {
        int scoreSum = 0;
        int nTopKPlayersRemaining = K;
        // Iterate over the scores to occurence count table in descending
        // order of score values
        for (auto & ent : _scoresToPlayerCntTbl) {
            // Score val and num players in leader board with that score
            auto & currScore = ent.first;
            auto & nPlayers = ent.second;
            // Update score sum (count scores of only 'K' players and not more)
            scoreSum += (currScore * min(nTopKPlayersRemaining, nPlayers));
            nTopKPlayersRemaining -= min(nTopKPlayersRemaining, nPlayers);
            if (nTopKPlayersRemaining <= 0) {
                break;
            }
        }
        
        return scoreSum;
    }
    
    void
    reset(int playerId) {
        resetPlayerEntry(playerId, true);
    }
    
private:
    
    int
    resetPlayerEntry(int playerId, bool erase = false) {
        
        // 
        auto oldScore = 0;
        auto iter = _playerToScoreTbl.find(playerId);
        if (iter != _playerToScoreTbl.end()) {
            // A score entry exists for player
            oldScore = iter->second;
            // Decrement player count against the earlier player score
            auto mapIter = _scoresToPlayerCntTbl.find(oldScore);
            if (--(mapIter->second) == 0) {      
                // Player count for older score drops to zilch => erase entry
                _scoresToPlayerCntTbl.erase(mapIter);
            }
            
            if (erase) {
                // Erase player entry
                _playerToScoreTbl.erase(iter);
            }
        }
        
        return oldScore;
    }
    
    // Data members
    // Hash table mapping each unique player to their latest scores
    unordered_map<int, int> _playerToScoreTbl;
    // RB/Binary Tree Mapping the current scores to the number of players
    // in the system with the respective score. The tree is organized with
    // key vals/scores sorted in descending order from larger to smaller scores
    map<int, int, greater<int> > _scoresToPlayerCntTbl; 
};

/**
 * Your Leaderboard object will be instantiated and called as such:
 * Leaderboard* obj = new Leaderboard();
 * obj->addScore(playerId,score);
 * int param_2 = obj->top(K);
 * obj->reset(playerId);
 */
