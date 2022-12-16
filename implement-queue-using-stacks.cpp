class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {
        
    }
    
    /** Push element x to the back of queue. */
    void
    push(int x) {
        if (!stack2.empty()) {
            // Move elements from stack2 to stack1
            while (!stack2.empty()) {
                stack1.push(stack2.top());
                stack2.pop();
            }
        }
        
        // Add new element
        stack1.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int
    pop() {
        if (stack2.empty()) {
            // Move elements from stack1 to stack2
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        
        int x = stack2.top();
        stack2.pop();
        
        return x;
    }
    
    /** Get the front element. */
    int
    peek() {
        if (!stack2.empty()) {
            return stack2.top();
        }
        
        // Move elements from stack1 to stack2
        while (!stack1.empty()) {
            stack2.push(stack1.top());
            stack1.pop();
        }
        
        return stack2.top();
    }
    
    /** Returns whether the queue is empty. */
    bool
    empty() {
        return (stack1.empty() && stack2.empty());
    }
    
private:
    
    // Data members
    // Stack 1 would be push stack (for all push)
    stack<int> stack1;
    // Stack 2 would be pop stack (for pop/peek)
    stack<int> stack2;    
    
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
