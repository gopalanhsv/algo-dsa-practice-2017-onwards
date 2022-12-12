class Solution {
public:
    string
    intToRoman(int num) {
    
        // Hash table mapping decimal values to the corresponding
        // roman symbols (including all special cases). The hash
        // table is organized in the descending order of the
        // key values (decimal) using a RB tree/balanced tree
        map<int, string, greater<int> > decValToRomanSymbolsTbl;
        decValToRomanSymbolsTbl[1] = "I";
        decValToRomanSymbolsTbl[4] = "IV";
        decValToRomanSymbolsTbl[5] = "V";
        decValToRomanSymbolsTbl[9] = "IX";
        decValToRomanSymbolsTbl[10] = "X";
        decValToRomanSymbolsTbl[40] = "XL";
        decValToRomanSymbolsTbl[50] = "L";
        decValToRomanSymbolsTbl[90] = "XC";
        decValToRomanSymbolsTbl[100] = "C";
        decValToRomanSymbolsTbl[400] = "CD";
        decValToRomanSymbolsTbl[500] = "D";
        decValToRomanSymbolsTbl[900] = "CM";
        decValToRomanSymbolsTbl[1000] = "M";
        
        /*
        vector<string> romanSymbolsV = {
            "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"
        };
        vector<int> decValsV = {
            1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1
        };*/
        
        // Adopt the greedy strategy of determining the largest decimal
        // value (which can be mapped to a roman symbol) which can divide
        // the current remaining portion of the number at each step.
        // All that needs to be done in this case is to go through the
        // possible roman symbols in the descending order of their values
        string romanStr;
        // Iterate through roman symbols in the descending order of magnitude
        for (auto & entry : decValToRomanSymbolsTbl) {
            auto & divisor = entry.first;
            if (divisor > num) {
                // Current roman symbol exceeds number
                continue;
            }
            
            // Current roman symbol is the max value which can divide the number
            auto & romanSymbol = entry.second;
            // Divide number by the roman symbol and get the number of current
            // roman symbols which can go into the number
            int quotient = num / divisor;
            while (quotient-- > 0) {
                // Append the obtained roman symbols to the roman representation
                romanStr += romanSymbol;
            }
            // Adjust the number to account for the value represented by
            // roman symbols
            num = num % divisor;
        }
        
        return romanStr;
    }
};
