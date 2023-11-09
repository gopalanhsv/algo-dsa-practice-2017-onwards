// Space complexity : O(n)

// upload()
// Time complexity : O(1)
// longest()
// Time complexity : Amortized O(1) 

class LUPrefix {
public:
    LUPrefix(int n) {
        // Initialize
        // No videos uploaded
        _longestPrefixId = 0;
        // _videoStatusV[n + 1] = false acts like a sentinel for any 
        // loop check as it is always 'false'
        _videoStatusV.resize(n + 2, false);
    }
    
    void
    upload(int video) {
        _videoStatusV[video] = true;
    }
    
    int
    longest() {
        // All videos in range [1, _longestPrefixId] are already uploaded
        // Check [_longestPrefixId + 1, ...] range till we hit a video yet
        // to be uploaded
        while (_videoStatusV[_longestPrefixId + 1] == true) {
            ++_longestPrefixId;
        }
        return _longestPrefixId;
    }
    
private:
    
    // Data members
    // _videoStatusV[x] is 'true' if video 'x' is uploaded, 'false' otherwise
    vector<bool> _videoStatusV;
    // Tracks the id of the longest uploaded prefix from amongst the videos uploaded so far
    int _longestPrefixId;
    int _maxVideoId;
};

/**
 * Your LUPrefix object will be instantiated and called as such:
 * LUPrefix* obj = new LUPrefix(n);
 * obj->upload(video);
 * int param_2 = obj->longest();
 */
