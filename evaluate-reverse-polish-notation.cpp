class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        
        typedef vector<string>::size_type vecSzT;

        // Using a stack of 'longs' instead of 'ints' to store
        // intermediate operand vals
        stack<long> operandsStk;
        
        // Iterate thru all the string tokens sequentially
        for (vecSzT i = 0; i != tokens.size(); ++i) {
            // If an operator is encountered, apply the
            // operator on last two operands/items stored in the stack
            // and push the result back to stack.
            
            // If an operand is encountered, push it on to stack
            
            if (tokens[i] == "+") {
                long operand2 = operandsStk.top();
                operandsStk.pop();
                long operand1 = operandsStk.top();
                operandsStk.pop();
                operandsStk.push(operand1 + operand2);
                
            } else if (tokens[i] == "-") {
                long operand2 = operandsStk.top();
                operandsStk.pop();
                long operand1 = operandsStk.top();
                operandsStk.pop();
                operandsStk.push(operand1 - operand2);
                
            } else if (tokens[i] == "*") {
                long operand2 = operandsStk.top();
                operandsStk.pop();
                long operand1 = operandsStk.top();
                operandsStk.pop();
                operandsStk.push(operand1 * operand2);
                
            } else if (tokens[i] == "/") {
                long operand2 = operandsStk.top();
                operandsStk.pop();
                long operand1 = operandsStk.top();
                operandsStk.pop();
                operandsStk.push(operand1 / operand2);
                
            } else {
                operandsStk.push(stol(tokens[i]));
            }
        }
        
        // Stack top holds result at end
        return operandsStk.top();
    }
};
