// n => folder.size(), W => average length of a string in 'folder'
// Time Complexity : O(nlogn + nW)
// Space Complexity : O(n)

class Solution {
public:
    vector<string>
    removeSubfolders(vector<string>& folder) {
        // Base case of single/empty string
        if (folder.size() < 2) {
            return folder;
        }
        
        vector<string> outV;
        // Sort the folder/subfolders list lexicographically s.t. folders
        // always come before their subfolders in the list
        sort(folder.begin(), folder.end());
        
        // Iterate thru list of folders/subfolders
        for (int i = 0; i < folder.size();) {
            
            // After sorting first item would always be folder
            outV.emplace_back(folder[i]);
            
            // Skip subsequent string which are subfolders
            int j = i + 1;
            while ((j != folder.size()) && isSubFolder(folder[i], folder[j])) {
                ++j;
            }
            
            i = j;
        }
        
        return outV;
    }
    
private:
    bool
    isSubFolder(string& folderStr, string& subFolderStr) {
        // Folder string len has to be lesser than its subfolder string len
        if (folderStr.size() >= subFolderStr.size()) {
            return false;
        }

        auto i = 0;
        // Stop at first mismatch char between the folder & subfolder string
        // or end of folder string; whichever occurs earlier
        while ((i != folderStr.size()) && (folderStr[i] == subFolderStr[i])) {
            ++i;
        }
  
        // Folder should be a prefix of subfolder. The character after prefix
        // should be '/' for 'subf' to be a subfolder of 'folder'
        if ((i == folderStr.size()) && (subFolderStr[i] == '/')) {
            return true;
        }
        
        return false;
    }
};
