// Solution with stack
// Time complexity : O(s.size())
// Space complexity : O(s.size())

// Solution without stack
// Time complexity : O(s.size())
// Space complexity : O(1)

class Solution {
public:
    string
    removeStars(string s) {
        return removeStarsWoStack(s);        
        return removeStarsViaStack(s);
    }
    
private:
    
    string
    removeStarsViaStack(string s) {
        // Stack to retain appropriate chars
        stack<char> chrStk;
        // Iterate over the string chars sequentially from L->R
        for (auto & c : s) {
            if (c == '*') {
                // Current char is '*'. 
                if (!chrStk.empty() && 
                    chrStk.top() != '*') {
                    // Skip the closest non-'*' seen so far
                    // (will be at stack top) and current char
                    chrStk.pop();
                } else {
                    // Add current char to stack
                    chrStk.push(c);
                }
            } else {
                // Add current char to stack
                chrStk.push(c);
            }
        }
        
        // Update string to account for removed chars
        int newStrSz = chrStk.size();
        s.resize(newStrSz);
        int idx = newStrSz - 1;
        while (!chrStk.empty()) {
            s[idx--] = chrStk.top();
            chrStk.pop();
        }
        
        return s;
    }
    
    
    string
    removeStarsWoStack(string s) {
    
        // Write pointer
        int wrIdx = 0;
        // Iterate over the string chars sequentially from L->R
        for (auto & c : s) {
            if (c == '*') {
                // Current char is a '*'
                if ((wrIdx > 0) && s[wrIdx - 1] != '*') {
                    // Remove closest non-'*' char to the left
                    // (would be at the immediate left) and 
                    // also the current '*'
                    --wrIdx;
                    continue;
                }
            }
            // Retain current char
            s[wrIdx++] = c;
        }
        
        // Resize the string to account for char removals
        s.resize(wrIdx);
        
        return s;
    }
};
