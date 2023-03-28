// Time complexity
// O(num videos)
// Space complexity
// O(num creators) tending to O(num videos)

class Solution {
public:
    vector<vector<string>>
    mostPopularCreator(vector<string>& creators, vector<string>& ids, vector<int>& views) {
        // Information/data about a creator video views
        typedef struct _CreatorViewInfoT {
            // Creator popularity
            long popularity;
            // Tracks the view count of the creators' most viewed video
            int mostViewedVideoViewCnt;
            // Tracks creators' most viewed video id (lexicographically smallest if
            // multiple videos of creator are most viewed)
            string mostViewedVideoId;
        } CreatorViewInfoT;
        
        // Hash table maintaining the creator video view data on a
        // per creator basis
        unordered_map<string, CreatorViewInfoT> creatorToViewInfoTbl;
        
        // Iterate over each video sequentially
        int nVideos = creators.size();
        for (int idx = 0; idx != nVideos; ++idx) {
            auto & creatorId = creators[idx];
            auto & videoId = ids[idx];
            auto & videoViewCnt = views[idx];

            // Update the creator video view data for the current videos'
            // creator in the hash table
            auto & creatorVideoViewInfo = creatorToViewInfoTbl[creatorId];
            // Update creator popularity
            creatorVideoViewInfo.popularity += videoViewCnt;
            // Update the most viewed video for current creator
            if (videoViewCnt > creatorVideoViewInfo.mostViewedVideoViewCnt) {
                // Current video has most views
                creatorVideoViewInfo.mostViewedVideoId = videoId;
                creatorVideoViewInfo.mostViewedVideoViewCnt = videoViewCnt;
            } else if (videoViewCnt == creatorVideoViewInfo.mostViewedVideoViewCnt) {
                // Current video has most views along with some earlier videos
                if (creatorVideoViewInfo.mostViewedVideoId.empty()) {
                    creatorVideoViewInfo.mostViewedVideoId = videoId;
                } else {
                    // Choose lexicographically smallest video id
                    creatorVideoViewInfo.mostViewedVideoId = 
                        min(videoId, creatorVideoViewInfo.mostViewedVideoId);
                }
            }
        }
        
        int maxPopularity = 0;
        vector<string> mostPopularCreatorsV;
        // Iterate over each entry in the creator video view data table
        // and find the creator(s) with the most popularity/most viewed videos 
        for (auto & hte : creatorToViewInfoTbl) {
            // hte => hash table entry
            auto & creatorId = hte.first;
            auto & creatorVideoViewInfo = hte.second;
            if (creatorVideoViewInfo.popularity > maxPopularity) {
                // Current creator has the max popularity amongst all seen so far
                mostPopularCreatorsV.clear();
                mostPopularCreatorsV.emplace_back(creatorId);
                maxPopularity = creatorVideoViewInfo.popularity;
            } else if (creatorVideoViewInfo.popularity == maxPopularity) {
                // Current creator has the max popularity along with several seen so far
                mostPopularCreatorsV.emplace_back(creatorId);
            }
        }
        
        // Build output vector of most popular creators with
        // respective most popular video ids
        vector<vector<string> > mostPopularCreatorsInfoV;
        for (auto & creatorId : mostPopularCreatorsV) {
            auto & videoViewInfo = creatorToViewInfoTbl[creatorId];
            auto & mostPopularVideo = videoViewInfo.mostViewedVideoId;
            mostPopularCreatorsInfoV.push_back({creatorId, mostPopularVideo});
        }
        
        return mostPopularCreatorsInfoV;
    }
};
