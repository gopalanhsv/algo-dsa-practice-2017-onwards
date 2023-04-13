// n = pushed.size() = popped.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    bool
    validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        
        // Base case error check
        if (pushed.size() != popped.size()) {
            return false;
        }
        
        // Have a pointer to track the current element in 'popped'
        // Keep adding elements from 'pushed' to stack till a element
        // with same value as indicated by 'popped' pointer is hit
        // at the top of stack.
        // Now keep removing elements from stack top matching the current
        // popped pointer (while advancing the popped pointer for each popped
        // element) till either the stack is empty OR mismatch occurs between
        // stack top and popped pointer element
        stack<int> stk;
        int popIdx = 0;
        int nElems = pushed.size();
        // Iterate over the elements in 'pushed' sequentially and
        // add them to stack one by one
        for (auto & pushVal : pushed) {
            stk.push(pushVal);
            // Remove elements from stack top matching the set of 
            // elements indicated by current popped array block
            while (!stk.empty() && stk.top() == popped[popIdx]) {
                stk.pop();
                ++popIdx;
            }
        }
        
        // Stack should be empty if pushed and popped indicate a
        // valid stack traversal
        return stk.empty();
    }
};
