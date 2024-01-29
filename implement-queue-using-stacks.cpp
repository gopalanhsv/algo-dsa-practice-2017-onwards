// X1 => number of push calls so far
// X2 => number of pop calls so far

// Time complexity : per call
// push() / pop() : O(max(X1 - X2, 0))
// empty() : O(1)

// Space complexity : O(max(X1 - X2, 0)

class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {
        
    }
    
    /** Push element x to the back of queue. */
    void
    push(int x) {
        // Move elements from pop stack to push stack
        // as previous operation was a pop operation
        while (!popStk.empty()) {
            pushStk.push(popStk.top());
            popStk.pop();
        }
        
        // Add new element to push stack
        pushStk.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int
    pop() {
       
        // Move elements from push stack to pop stack
        // as previous operation was a push operation
        // and elements are organized in LIFO fashion now
        while (!pushStk.empty()) {
            popStk.push(pushStk.top());
            pushStk.pop();
        }
        
        // Remove earliest added element
        int x = popStk.top();
        popStk.pop();
        
        return x;
    }
    
    /** Get the front element. */
    int
    peek() {
        if (!popStk.empty()) {
            // Elements are organized in FIFO fashion from top of
            // pop stack towards kottom of pop stack
            return popStk.top();
        }
        
        // Move elements from push stack to pop stack
        // as previous operation was a push operation
        // and elements are organized in LIFO fashion now
        while (!pushStk.empty()) {
            popStk.push(pushStk.top());
            pushStk.pop();
        }
        
        return popStk.top();
    }
    
    /** Returns whether the queue is empty. */
    bool
    empty() {
        return (pushStk.empty() && popStk.empty());
    }
    
private:
    
    // Data members
    // Push stack (for all push operations to the Q)
    stack<int> pushStk;
    // Pop stack (for pop/peek operations from the Q)
    stack<int> popStk;    
    
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
