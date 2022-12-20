class Solution {
public:
    bool
    canVisitAllRooms(vector<vector<int>>& rooms) {
        
        // Problem reduces to commencing a DFS/BFS traversal from room 0,
        // collecting keys available there; then visiting unvisited rooms
        // whose keys are available; while marking all the rooms which are
        // visited during the traversal
        _nVisitedRooms = 0;
        _visited.resize(rooms.size(), false);
    
        visitRoomsViaDFS(rooms, 0);
    
        // All rooms should have been visited in
        // the traversal starting from room 0
        return rooms.size() == _nVisitedRooms;
    }
    
private:
    
    void
    visitRoomsViaDFS(vector<vector<int>>& rooms, int currRoomId) {
        
        // Current room is being visited for first time
        _visited[currRoomId] = true;
        ++_nVisitedRooms;
        
        // Get the room keys of rooms which can be visited from 'currRoomId'        
        auto & roomKeysVec = rooms[currRoomId]; 
        // Visit all unvisited rooms and explore further
        for (auto roomKey : roomKeysVec) {
            // Visit the room with given key if unexplored
            if (!_visited[roomKey]) {
                visitRoomsViaDFS(rooms, roomKey);
            }
        }
    }
    
    // Data members
    vector<bool> _visited;
    int _nVisitedRooms;
    
};
