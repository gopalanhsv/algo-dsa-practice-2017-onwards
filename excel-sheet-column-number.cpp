// Time complexity : O(columTitle.size()) / O(n)
// Space complexity : O(1)
class Solution {
public:
    int
    titleToNumber(string columnTitle) {
        // Akin to base-26 to base-10 conversion with funny business of adding a
        // 1 to every char as number system ranges from A-1 to Z-26 instead of
        // from A-0 (i.e. no 0)
        int number = 0;
        for (auto & c : columnTitle) {
            number = number * 26 + (c - 'A' + 1);
        }
        return number;
    }
};
