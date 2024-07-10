// n => logs.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    minOperations(vector<string>& logs) {

        if (logs.empty()) {
            return 0;
        }
        
        // Iterate through logs sequentially and simulate the operation
        int netChildFolderOps = 0;
        int numParentDirOps = 0; // ../
        for (auto & op : logs) {
            if (op == "../") {
                if (netChildFolderOps > 0) {
                    --netChildFolderOps;
                }
            } else if (op != "./") {
                ++netChildFolderOps;
            }
        }
        
        // Num of steps to get back to main folder would be net subfolder ops at end       
        return netChildFolderOps;
    }
};
