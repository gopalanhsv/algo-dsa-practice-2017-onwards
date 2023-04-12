// Time complexity : O(path.size())
// Space complexity : O(path.size())

class Solution {
public:
    string
    simplifyPath(string path) {
        // Anything to do with edit/replace or accessing data stored previously
        // (editor/directory) required use of a tree or stack or combo of both
        stack<string> pathStk;
        typedef string::size_type strSzT;
        strSzT i = 0;
        while (i < path.size()) {
            
            // Skip continuous leading '/' till a non-'/' is reached
            while (i < path.size() && path[i] == '/') {
                ++i;
            }
            if (i >= path.size()) {
                // End of string reached
                break;
            }
            
            // Reached a non-'/' char 
            
            // Find the first '/' after the non '/' dir string
            strSzT j = path.find('/', i);
            
            if (j == string::npos) {
                j = path.size();
            }
            
            // Get the directory component string from the previous seen '/'
            // to current '/' or end of string
            string dirStr = path.substr(i, j - i);
            
            if (dirStr == ".") {
                // Stay at the same directory level
                // i.e. nothing to be done
            } else if (dirStr == "..") {
                // Go one level up (i.e. pop the last directory stored in stack)
                if (!pathStk.empty()) {
                    pathStk.pop();
                }
            } else {
                // Valid dir string in path. Store on the stack
                pathStk.push(dirStr);
            }
            
            // Move to the next dir string after the '/'
            i = j + 1;
        }
    
        // The stack will now have the canonical path in reverse order
        // Compute the canonical path in correct order and add the leading '/'  
        string canonicalPathStr;
        while (!pathStk.empty()) {
            canonicalPathStr = "/" + pathStk.top() + canonicalPathStr;
            pathStk.pop();
        }
        
        return canonicalPathStr.empty() ? "/" : canonicalPathStr;
    }
};
