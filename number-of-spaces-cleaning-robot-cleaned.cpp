// Num room rows/cols = nr/nc
// Time complexity : O(nr x nc)
// Space complexity : O(nr x nc)

class Solution {
public:
    int
    numberOfCleanRooms(vector<vector<int>>& room) {
        // Num row and cols of grid representing room
        int nr = room.size();
        int nc = room[0].size();
        // Either use a 2D array of bools to mark a space/grid point as cleaned or
        // the input room grid itself (if modifying the input is allowed)
        // All spaces marked as not cleaned initially
        vector<vector<bool> > spacesCleaned(nr, vector<bool>(nc, false));

        // Movement offsets per step for each robot move direction
        // as per the appropriate order
        vector<vector<int> > movementDirOffsetV = {
            {0, 1}, // Left to right movement of robot
            {1, 0}, // Top to bottom movement of robot
            {0, -1}, // Right to left movement of robot
            {-1, 0}, // Bottom to top movement of robot
        };
        
        int nSpacesCleaned = 0;
        // Robot start coords
        int r = 0, c = 0;        
        // Flag which track if at least a cell gets cleaned after
        // robot movies in all 4 consective cw directions 
        bool singleSpaceCleaned = false;    
        // Keep robot moving and cleaning till it hits a point where no
        // new space is cleaned in any of the 4 directions
        do {

            singleSpaceCleaned = false;
            
            // Iterate over the directions in the following order 
            // left to right, followed by a 90deg cw turn
            // top to bottom, followed by a 90deg cw turn
            // right to left, followed by a 90deg cw turn
            // bottom to top, followed by a 90deg cw turn 
            for (auto & offsets : movementDirOffsetV) {
                // Movement direction offsets
                auto xOffset = offsets[0];
                auto yOffset = offsets[1];
                // Robot cleans in a single linear direction as specd above
                int nSpacesCleanedInCurrMove =
                    cleanSpaces(r, c, xOffset, yOffset, nr, nc, room, spacesCleaned);
                if (nSpacesCleanedInCurrMove > 0) {
                    singleSpaceCleaned = true;
                    nSpacesCleaned += nSpacesCleanedInCurrMove;
                }                
            }
            
        } while (singleSpaceCleaned);
        
        return nSpacesCleaned;
    }
    
private:
    
    int
    cleanSpaces(int& r, int& c, int rowOffset, int colOffset, int nr, int nc,
                vector<vector<int>>& room, vector<vector<bool> >& spacesCleaned) {
        
        // Move robot in the appropriate direction as per the offset pair(rowOffset, colOffset)
        // cleaning uncleaned spaces while tracking the number of new spaces cleaned
        int nSpacesCleaned = 0;
        while (true) {
            if (!spacesCleaned[r][c]) {
                spacesCleaned[r][c] = true;
                ++nSpacesCleaned;
            }
            
            if (r + rowOffset >= nr || r + rowOffset < 0 ||
                c + colOffset >= nc || c + colOffset < 0 ||
                room[r + rowOffset][c + colOffset] == 1) {
                // Edge of room is hit/obstacle encountered. Robot stops moving
                break;
            }
            
            // Advance robot to next space
            r += rowOffset;
            c += colOffset;
        }
        return nSpacesCleaned;
    }
    
};
