class Solution {
public:
    int
    removeElement(vector<int>& v, int val) {

        typedef vector<int>::size_type vecSzT;
        
        vecSzT wrPtr = 0;
        // Iterate over all elements of vector sequentially
        for (vecSzT rdPtr = 0; rdPtr != v.size(); ++rdPtr) {
            // Skip vector elems with given value
            if (v[rdPtr] == val) {
                continue;
            }
            
            // Append the current element to appropriate location
            // in the vector and update the write location
            v[wrPtr++] = v[rdPtr];
        }
        
        return wrPtr;
    }
};
