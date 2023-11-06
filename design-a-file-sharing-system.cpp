// n => num calls
// u => max users in the system at any point in time
// m => max chunks

// Space complexity : O(mu)

// join()
// Time complexity : O(nmlogu)
// leave()
// Time complexity : O(nmlogu)
// request()
// Time complexity : O(nu)


class FileSharing {
public:
    FileSharing(int m) {
        _minChunkId = 1;
        _maxChunkId = m;
        _smallestUnAssignedUserId = 1;
    }
    
    int
    join(vector<int> ownedChunks) {
        auto userId = allocSmallestAvlUserId();
        associateChunksWithUser(userId, ownedChunks);
        return userId;
    }
    
    void
    leave(int userID) {
        if (_userToChunksTbl.find(userID) == _userToChunksTbl.end()) {
            // No user in the system given id
            return;
        }
        removeUserAndAssociatedChunks(userID);
        // Make the user id of user available for next allocation
        releaseUserId(userID);
    }
    
    vector<int>
    request(int userID, int chunkID) {
        if ((chunkID > _maxChunkId) || (chunkID < _minChunkId)) {
            // Invalid chunk => invalid request
            return vector<int>();
        }

        // Get the list of users owning the given chunk
        auto iter = _chunkToUsersTbl.find(chunkID);
        if (iter == _chunkToUsersTbl.end()) {
            // Users owning the given chunk are not registered in sharing system
            return vector<int>();
        }
        
        auto & chunkUsersSet = iter->second;
        vector<int> usersV(chunkUsersSet.begin(), chunkUsersSet.end());
        _chunkToUsersTbl[chunkID].insert(userID);
        _userToChunksTbl[userID].emplace_back(chunkID);
            
        return usersV;
    }
    
private:
    
    int
    allocSmallestAvlUserId() {
        auto userId = 0;
        if (_availableUserIdsSet.empty()) {
            userId = _smallestUnAssignedUserId++;
        } else {
            userId = *(_availableUserIdsSet.begin());
            _availableUserIdsSet.erase(userId);
        }
        return userId;
    }
    
    void
    releaseUserId(int userId) {
        _availableUserIdsSet.insert(userId);
    }
    
    void
    associateChunksWithUser(int userId, vector<int>& chunks) {
        // Associate specified file chunks with the specified use in the
        // file sharing system making them available to other users
        
        // Add entry for chunks owned by new user
        _userToChunksTbl[userId] = chunks;
        // Iterate over the chunks owned by user
        for (auto & chunkId : chunks) {
            // Associate the chunk with the new user  
            _chunkToUsersTbl[chunkId].insert(userId);
        }
    }
    
    void
    removeUserAndAssociatedChunks(int userId) {
        // Get the list of chunks owned by user
        auto & userChunks = _userToChunksTbl[userId];

        // Iterate over the chunks ownned by the user
        for (auto chunkId : userChunks) {
            // Updated the internal state to account for chunk 'chunkId'
            // no longer associated with user 'userId'
            auto & chunkUsersSet = _chunkToUsersTbl[chunkId];
            chunkUsersSet.erase(userId);
            if (chunkUsersSet.empty()) {
                // No users for chunk 'chunkId' => chunk is no longer available
                _chunkToUsersTbl.erase(chunkId);
            }
        }
        // Remove user entry from system
        _userToChunksTbl.erase(userId);
    }
        
    // Data members
    
    set<int> _availableUserIdsSet;
    int _smallestUnAssignedUserId;
    int _minChunkId;
    int _maxChunkId;
    
    unordered_map<int, set<int> > _chunkToUsersTbl;
    unordered_map<int, vector<int> > _userToChunksTbl;
    
};

/**
 * Your FileSharing object will be instantiated and called as such:
 * FileSharing* obj = new FileSharing(m);
 * int param_1 = obj->join(ownedChunks);
 * obj->leave(userID);
 * vector<int> param_3 = obj->request(userID,chunkID);
 */
