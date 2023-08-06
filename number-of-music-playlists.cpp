// Bottom up DP Approach
// Time complexity : O(n * goal)
// Space complexity : O(n * goal)

class Solution {
public:
    int
    numMusicPlaylists(int n, int goal, int k) {
        
        if (0 == n || 0 == goal || goal < n) {
            // Base case of nil songs, nil playlist length OR playlist length l.t
            // number of unique songs results in zero number of playlists
            return 0;
        }
        
        return numMusicPlaylistsBottomUpDP(n, goal, k);
    }
    
private:
    
    int
    numMusicPlaylistsBottomUpDP(int n, int goal, int k) {
        
        const int moduloFactor = 1000000000 + 7;
        // nPlaylistsTbl[l][s] is the number of possible playlists of length 'l'
        // from a set of 's' unique songs where each song is played at least once
        // and a songs gets replayed only after 'k' other songs have been played
        vector<vector<long> > nPlaylistsTbl(goal + 1, vector<long>(n + 1, 0));
        // An empty playlist can be created from nil songs in a single way
        nPlaylistsTbl[0][0] = 1;
        
        // Gradually construct the playlist by incrementing its length from 1 to 'goal'
        for (int pLen = 1; pLen <= goal; ++pLen) {
            // Increment the number of unique songs to considered for building
            // the current playlist of length 'pLen' from 1 to min(pLen, n)
            // (as number of unique songs cannot be more than playlist length)
            for (int nUniqSongs = 1; nUniqSongs <= min(pLen, n); ++nUniqSongs) {
        
                // Compute the number of 'pLen' length possible playlists as per
                // constraints with a set of 'nUniqSongs' unique songs 
                long nPossiblePlaylists = 0;
        
                // Two options for building new playlists:-
                // (1) By adding a new song to all earlier playlists of length 'pLen - 1'
                // Since single new unique song is being added, the earlier playlists should
                // have been constructed from 'nUniqSongs - 1' unique songs. The new unique
                // song can be selected from any of the unselected 'n - (nUniqSongs - 1)' 
                // songs
                nPossiblePlaylists += 
                    nPlaylistsTbl[pLen - 1][nUniqSongs - 1] * (n - (nUniqSongs - 1));
                // (2) By replaying an old song from all earlier playlists of length 'pLen - 1'
                // Since old song is being added, the earlier playlists should
                // have been constructed from 'nUniqSongs' unique songs. The old song may be
                // selected from any of the previously selected songs except the last 
                // played 'k' songs i.e. from any of the previously played 'nUniqSongs - k'
                if (nUniqSongs > k) {
                    nPossiblePlaylists += 
                        nPlaylistsTbl[pLen - 1][nUniqSongs] * (nUniqSongs - k);
                }
                
                nPossiblePlaylists %= moduloFactor;
                nPlaylistsTbl[pLen][nUniqSongs] = nPossiblePlaylists;
            }
        }

        return nPlaylistsTbl[goal][n];
    }
};
