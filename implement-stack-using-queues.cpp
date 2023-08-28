// n => num elements streamed so far
// Time complexity 
// push() / top() / empty() : O(1)
// pop() : O(n)
// Space complexity : O(n)

class MyStack {
public:
    MyStack() {
        _topElement = -1;
    }
    
    void
    push(int x) {
        // Update the stack top element
        _topElement = x;
        
        // Add the new element to the rear to non-empty Q
        // (or Q1 if both are empty)
        if (!_q2.empty()) {
            _q2.push(x);
        } else {
            _q1.push(x);
        }
    } 
    
    int
    pop() {    
        // Get the value of current top element
        int oldTopElement = _topElement;
        
        // Element at stack top will be the one at rear of
        // currently non-empty Q. Move all elements from the
        // non-empty Q to empty Q, except the single element
        // at non-empty Q rear (stack top element). Drop that
        // element (stack pop operation). Also update the 
        // top element of stack to the rear element of Q
        // after the move
        if (!_q2.empty()) {
            _topElement = moveAllElementsAndRemoveLast(_q2, _q1);
                   
        } else {
            
            _topElement = moveAllElementsAndRemoveLast(_q1, _q2);
        }
        
        return oldTopElement;
    }
    
    int
    top() {
        return _topElement;
    }
    
    bool
    empty() {
        return _q1.empty() && _q2.empty();
    }
    
private:
    
    int
    moveAllElementsAndRemoveLast(queue<int> & srcQ, queue<int> & dstQ) {
        if (srcQ.size() == 1) {
            // Stack and hence Q becomes empty. Reset top element
            _topElement = -1;
            srcQ.pop();
            return _topElement;
        }
        
        // Move all element except the last 2 from source Q to destination Q
        while (srcQ.size() > 2) {
            dstQ.push(srcQ.front());
            srcQ.pop();
        }
        
        // 2nd last element of source Q becomes the new stack top element
        // Move it to rear of destination Q
        _topElement = srcQ.front();
        dstQ.push(srcQ.front());
        srcQ.pop();
        
        // Dump element at rear of source Q (previous stack top element popped)
        srcQ.pop();
        
        return _topElement;
    }
    
    // Data members
    // Two Qs to simulate stack
    queue<int> _q1;
    queue<int> _q2;
    // Always tracks the top element value, resets to -1 when stack is empty
    int _topElement;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
