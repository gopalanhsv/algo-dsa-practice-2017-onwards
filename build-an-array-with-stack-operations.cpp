// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    vector<string>
    buildArray(vector<int>& target, int n) {
        vector<string> opsV;
        
        // Tracks the smallest element yet unsed from the input stream
        // for building the array via stack operations
        auto smallestUnusedStreamElem = 1;
        
        // Iterate over the target array elements sequentially from L->R
        for (auto & currLastElem : target) {
            
            // Use the stack (with appropriate ops) to to build the target array
            // (i.e. to have the stack top as 'currLastElem')
            
            while (smallestUnusedStreamElem < currLastElem) {
                // Smallest usused/unread element from stream is l.t 'currLastElem'
                // Advance to next smallest unused/element using stack to
                // read element from stream to stack followed by popping it
                opsV.emplace_back("Push");
                opsV.emplace_back("Pop");
                // Advance to next element in list
                ++smallestUnusedStreamElem;
            }
            // Now smallest unread/unused stream element is identical to that
            // required at target array end. Add it to top of stack/array end using stack 
            opsV.emplace_back("Push");
            // Advance to next unused element in stream
            ++smallestUnusedStreamElem;
        }
        
        return opsV;
    }
};
