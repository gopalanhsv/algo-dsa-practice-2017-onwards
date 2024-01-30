// n => tokens.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    int
    evalRPN(vector<string>& tokens) {

        // Using a stack of 'longs' instead of 'ints' to prevent overflow
        // during computation of intermediate operand vals
        stack<long> operandsStk;
        // Iterate thru all the string tokens sequentially from L->R
        for (auto & token : tokens) {
            // An operator is encountered => pop the last two operands off the
            // stack, apply the operator on the same and push the result back to stack
            
            // An operand is encountered => push it on to stack
            
            if (token == "+") {
                long operand1, operand2;
                last2OperandsFromStk(operand1, operand2, operandsStk);
                operandsStk.push(operand1 + operand2);
                
            } else if (token == "-") {
                long operand1, operand2;
                last2OperandsFromStk(operand1, operand2, operandsStk);
                operandsStk.push(operand1 - operand2);
                
            } else if (token == "*") {
                long operand1, operand2;
                last2OperandsFromStk(operand1, operand2, operandsStk);
                operandsStk.push(operand1 * operand2);
                
            } else if (token == "/") {
                long operand1, operand2;
                last2OperandsFromStk(operand1, operand2, operandsStk);
                operandsStk.push(operand1 / operand2);
                
            } else {
                operandsStk.push(stol(token));
            }
        }
        
        // Stack top holds result at end
        return operandsStk.top();
    }
    
private:
    
    inline void
    last2OperandsFromStk(long& op1, long& op2, stack<long>& stk) {
        op2 = stk.top();
        stk.pop();
        op1 = stk.top();
        stk.pop();
    }
};
