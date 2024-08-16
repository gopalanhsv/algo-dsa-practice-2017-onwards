// n => bills.size()
// Time Complexity : O(n)
// Space Complexity : O(1)

class Solution {
public:
    bool
    lemonadeChange(vector<int>& bills) {
        //return lemonadeChangeExtensible(bills);
        return lemonadeChangeHardcoded(bills);
    }
        
private:
    
    bool
    lemonadeChangeHardcoded(vector<int>& bills) {
        
        // Adopt the greedy approach of retaining as many of the 5$ bills possible
        // (need to have max of these in hand as these give the most flexibility in
        // returning change of 5/10/15)
        // Algo :-
        // 1. Customer comes with 5$ bill, store it
        // 2. Customer comes with 10$ bill, store it and return 5$
        // 3. Customer comes with 20$ bill, return 15$. Try returning
        //    in 10 + 5 first if available else 3 x 5$
        int nFives = 0;
        int nTens = 0;
        // Process each customer as per their arrival
        for (auto bill : bills) {
    
            switch (bill) {
                case 5:
                    ++nFives;
                    break;
                    
                case 10:
                    ++nTens;
                    if (nFives > 0) {
                        // Give 5 as change
                        --nFives;
                    } else {
                        // No change
                        return false;
                    }
                    break;
                    
                case 20:
                    if (nTens > 0 & nFives > 0) {
                        // Given 10 + 5 as change
                        --nTens;
                        --nFives;
                    } else if (nFives > 2) {
                        // Given 3 x 5 as change
                        nFives -= 3;
                    } else {
                        // No change
                        return false;
                    }
                    break;
                    
                default:
                    // Unsupported bill denomination
                    return false;
            }
        }
        
        // Managed to give change to all customers
        return true;
        
    }
    
    bool
    lemonadeChangeExtensible(vector<int>& bills) {
        
        // Init table maintaining running denomination count of notes
        _denominationCntTbl[5] = 0;
        _denominationCntTbl[10] = 0;
        _denominationCntTbl[20] = 0;
        
        // When a customer gives a note for lemonade, adopt the greedy approach of trying to return
        // change with max denomination possible i.e. try to break down the change with max number
        // of 20$ bills available, remainder amount with 10$ bills and the rest with 5$ bills
        
        // This approach allows us to retain the max number of 5$, 10$ bills which gives the most
        // flexibility to construct reqd change in each iteration (it can build to 5 X 2 = 10$ and
        // 10 X 2 = 5 x 4 = 20$) easily, while 20 and 10$ dont give that much flexibility
        
        // Iterate over customers sequentially
        for (auto bill : bills) {
            // Add customer bill to denomination count table
            ++_denominationCntTbl[bill];
            if (bill > 5) {
                // Attempt to construct change from the denominations available
                // int change = bill - 5;
                // Attempt to construct change from 10$ first
                int change = constructChangeForDenomination(10, bill - 5);
                if (0 != change) {
                    // Attempt to onstruct change from 5$ now
                    change = constructChangeForDenomination(5, change);
                    if (0 != change) {
                        // Not able to return change completely this time
                        return false;
                    }
                }
            }
        }
        
        // Managed to serve all customers with proper change 
        return true;
    }
    
    int
    constructChangeForDenomination(int denom, int change) {
        
        int denomBillFreqCnt = _denominationCntTbl[denom];
        if (change >= denom && denomBillFreqCnt > 0) {
            int nDenomBillsNeeded = change / denom;
            if (nDenomBillsNeeded >= denomBillFreqCnt) {
                change -= (denom * denomBillFreqCnt);
                _denominationCntTbl[denom] = 0;
            } else {
                change -= (denom * nDenomBillsNeeded);
                _denominationCntTbl[denom] -= nDenomBillsNeeded;
            }
        }
        return change;
    }
    
    // Data members
    // Table maintaining running denomination count of notes
    // available with the business owner
    unordered_map<int, int> _denominationCntTbl;
};
