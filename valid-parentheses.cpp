class Solution {
public:
    bool
    isValid(string s) {
        
        typedef string::size_type strSzT;
        
        stack<char> paranthesisStk;
        
        // Iterate over each char of string sequentially
        for (strSzT i = 0; i != s.size(); ++i) {
            
            char p = s[i];
            
            if (p == '(' || p == '[' || p == '{') {
                // Opening paranthesis, push on to stack
                paranthesisStk.push(p);
            } else {
                // Closing paranthesis. Stack top entry should
                // match the closing paranthesis
                if (paranthesisStk.empty()) {
                    return false;
                }
                
                char top = paranthesisStk.top();
                paranthesisStk.pop();                
                if ( (top == '(' && p == ')') ||
                     (top == '{' && p == '}') ||
                     (top == '[' && p == ']') ) {
                    // Matching paranthesis at stack top
                    continue;
                } else {
                    // Stack top doesn't have matching paranthesis. Signal error
                    return false;
                }
            }
        }
        
        // Stack should be empty at end
        return paranthesisStk.empty();
    }
};
