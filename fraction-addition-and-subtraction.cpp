// n => expression.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    string
    fractionAddition(string expression) {
        
        // Split the expression into individual fractions
        splitExpressionIntoIndividualComponents(expression);
    
        // Combine and evaluate all the individual expression fractions to single fraction
        // Reducible expression will be 'evaluatedNumerator / evaluatedDenominator'
        long long evaluatedNumerator, evaluatedDenominator;
        evaluateExpression(evaluatedNumerator, evaluatedDenominator);
        
        eliminateCommonFactors(evaluatedNumerator, evaluatedDenominator);
        
        // Convert reduced expression fraction to string
        string outStr;
        outStr += to_string(evaluatedNumerator) + "/" + to_string(evaluatedDenominator);
        return outStr;
    }

private:
    
    void
    splitExpressionIntoIndividualComponents(const string& expression) {
        
        // Iterate over the expression, parse and split into individual fractions
        int i = 0;
        int exprSz = expression.size();
        while (i < exprSz) {
            // Fraction sign
            int sign = 1;
            if ('-' == expression[i]) {
                sign = -1;
                ++i;
            } else if ('+' == expression[i]) {
                ++i;
            }
            
            // Numerator
            int numerator = int(expression[i] - '0');
            ++i;
            if (isdigit(expression[i])) {
                int digit = int(expression[i] - '0');
                numerator = ((numerator * 10) + digit);
                ++i;
            }
            numerator *= sign;
            
            // Skip '/'
            ++i;
            // Demominator
            int denom = int(expression[i] - '0');
            ++i;
            if ((i < exprSz) && isdigit(expression[i])) {
                int digit = int(expression[i] - '0');
                denom = ((denom * 10) + digit);
                ++i;
            }
            
            _uniqueDenom.insert(denom);
            _allFractionsV.push_back({numerator, denom});
        }
    }
    
    void
    evaluateExpression(long long& evaluatedNumerator, long long& evaluatedDenominator) {
        
        // Product of all unique denominators
        evaluatedDenominator = 1;
        for (auto & x : _uniqueDenom) {
            evaluatedDenominator *= x;
        }
        // Normalize all numerators to a single value and add them up
        evaluatedNumerator = 0;
        for (auto & fraction : _allFractionsV) {
            auto & num = fraction.first;
            auto & denom = fraction.second;
            
            long long normalizedNumerator = num;
            normalizedNumerator *= (evaluatedDenominator / denom);
            
            evaluatedNumerator += normalizedNumerator;
        }

    }
    
    void
    eliminateCommonFactors(long long& numerator, long long& denominator) {
        int sign = 1;
        if (numerator < 0) {
            sign = -1;
            numerator = -numerator;
        }
        // Reduce the numerator and denominator of the reducible expression into a irreducible fraction
        for (int factor = 9; factor >= 2; -- factor) {
            while ((0 == (numerator % factor)) && (0 == (denominator % factor))) {
                numerator /= factor;
                denominator /= factor;
            }
        }
        
        numerator *= sign;
    }
    
    // Data members
    unordered_set<int> _uniqueDenom;    
    vector<pair<int, int> > _allFractionsV;

};
