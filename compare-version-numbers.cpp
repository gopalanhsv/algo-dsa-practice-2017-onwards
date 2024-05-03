// p => version1.size(), q => version2.size()
// Time complexity : O(max(p, q))
// Space complexity : O(1)

class Solution {
public:
    int
    compareVersion(string version1, string version2) {
        
        auto i = 0, j = 0;
        auto v1Sz = version1.size(), v2Sz = version2.size();
        
        // Keep comparing current revision substring values of both versions1/2 in
        // lockstep till both the strings are fully exhausted or
        // the strings differ in their current revisions
        while ((i < v1Sz) || (j < v2Sz)) {
            
            // Compute current revision of version1
            int revision1 = 0;
            i = computeCurrentRevision(i, version1, v1Sz, revision1);

            // Compute current revision of version2
            int revision2 = 0;
            j = computeCurrentRevision(j, version2, v2Sz, revision2);

            // Compare current revisions of both version1/2
            if (revision1 < revision2) {
                return -1;
            } else if (revision1 > revision2) {
                return 1;
            }
            
            // Both the current revisions of version1/2 are equal,
            // Continue on to compare the next revision
        }
        
        // Both the versions1/2 were equal in all revisions
        return 0;
    }
    
private:
    int
    computeCurrentRevision(int i, string & version, int sz, int & revision) {
        
        // Skip leading zeroes in current revision of version
        while ((i < sz) && (version[i] == '0')) {
            ++i;
        }
        
        // Compute current revision of version
        revision = 0;
        if (i < sz) {
            for (; i < sz; ++i) {
                auto c = version[i];
                if (c == '.') {
                    // Ed of current revision i.e '.' reached => exit
                    break;
                }
                revision = revision * 10 + (c - '0');
            }
        }
        
        // Return index of first character from next revision (if any)
        return ++i;
    }
};
