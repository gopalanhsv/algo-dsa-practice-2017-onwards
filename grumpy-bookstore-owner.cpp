// n => customers.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        
        // Customers who come into the bookstore when owner is non-grumpy will
        // always be satisfied. Customers who come into the bookstore when owner
        // is grumpy will be dissatisfied unless they come during the 'minutes'
        // size time window while the owner is practicing secret technique
        
        // To maximize the number of customers who can be satisfied, the owner needs
        // to adopt the greedy approach of practicing the secret technique of non
        // grumpiness for that particular time window 'minutes', where his grumpiness
        // moments intersect with the maximum number of customers arrival events
        
        // Use a sliding window of size 'minutes' to track 'minutes' length window
        // where the owner applies secret technique to overcome grumpiness. Need
        // to find the particular window where his grumpiness offends the maximum
        // number of customers; and convert them into satified customers
        
        int nAlwaysSatisfiedCustomers = 0;
        int nMaxDissatisfiedCustomersInWindow = 0;
        int nDissatisfiedCustomersInWindow = 0;
        
        // Sliding window extends over the range [winStart, winEnd] and is of
        // the fixed length 'minutes'
        int nMinuteEvents = customers.size();
        int winStart = 0;
        for (int winEnd = 0; winEnd != nMinuteEvents; ++winEnd) {
            // Add current time instant to the secret technique time window
            // Currently at time 'winEnd'
            auto & nCustomerArrivals = customers[winEnd];
            
            if (0 == grumpy[winEnd]) {
                // Owner not grumpy
                // Customers coming at current time are always satified
                nAlwaysSatisfiedCustomers += nCustomerArrivals;
            } else {
                // Owner is grumpy
                // Customers coming at current time would be dissatified
                nDissatisfiedCustomersInWindow += nCustomerArrivals;
            }
            
            if (winEnd >= minutes) {
                // Secret technique time window exceeds max allowed
                // Shift the left/start side of the window by 1 unit forward
                if (1 == grumpy[winStart]) {
                    // Update the number of customers experiencing dissatisfaction
                    // at the start side of the window
                    nDissatisfiedCustomersInWindow -= customers[winStart];
                }
                ++winStart;
            }
            
            // Update the maximum number of dissatisfied customers within window
            // experiencing the thrall of secret technique and getting turning satisfied
            nMaxDissatisfiedCustomersInWindow
                = max(nMaxDissatisfiedCustomersInWindow, nDissatisfiedCustomersInWindow);
        }
        
        // Num satifiesfied customers
        return nMaxDissatisfiedCustomersInWindow + nAlwaysSatisfiedCustomers;
    }
};
