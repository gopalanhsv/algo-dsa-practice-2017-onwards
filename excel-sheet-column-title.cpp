// Time complexity : O(log columnNumber) / O(log n)
// Space complexity : O(1)

class Solution {
public:
    string
    convertToTitle(int columnNumber) {
        // The problem is akin to converting a base-10 number to base-26; with the 26 base
        // digits ranging from 'A' to 'Z' for digits '1' to '26'. '0' digit is excluded. 
        // Since '0' is excluded and modulo-26 ops in c++ works only with 0-25; one needs
        // to decrement the remainder by 1 prior to each modulo-26 conversion ops
        string title;
        while (columnNumber) {
            // Decrement as mod-26 works in range [0, 26] while we need to work with range [1, 26]
            --columnNumber;
            title = char('A' + columnNumber % 26) + title;
            columnNumber = (columnNumber / 26);
        }
        return title;
    }
};
