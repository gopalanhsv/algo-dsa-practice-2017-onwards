// n1 = num list 'l1' nodes
// n2 = num list 'l1' nodes
// Time complexity : O(max(n1, n2))
// Space complexity : O(max(n1, n2))

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode*
    addTwoNumbers(ListNode* l1, ListNode* l2) {
        // Base case of either of the lists being empty, return the other list
        if (nullptr == l1) {
            return l2;
        }
        if (nullptr == l2) {
            return l1;
        }
        // Since 2 numbers need to be added from LSB -> MSB (i.e. from R->L) and number
        // representation in list is organized from L->R from head to tail; reverse the
        // two lists so that the two number digits get represented from MSB to LSB in
        // the two lists while moving from head to tail
        ListNode *rList1 = reverseList(l1);
        ListNode *rList2 = reverseList(l2);
        
        // New list with the sum of two numbers
        ListNode *sumListNode = nullptr;
        int carry = 0;
        
        // Add the digits at identical digit positions from the two reversed number lists
        // while moving form L->R sequentially
        while (rList1 || rList2 || carry) {

            // Digit sum is initialized to carry from previous position
            int sumOfDigits = carry;
            if (rList1) {
                // Add current digit from list#1 and advance to next digit in list#1
                sumOfDigits += rList1->val;
                rList1 = rList1->next;
            }
            if (rList2) {
                // Add current digit from list#2 and advance to next digit in list#2
                sumOfDigits += rList2->val;
                rList2 = rList2->next;
            }
            
            // Compute the digit value of sum and append it to head of
            // new list representing the sum of lists 1 & 2
            int currPosDigit = sumOfDigits % 10;
            sumListNode = appendNewNodeToListHead(currPosDigit, sumListNode);
            // Compute the carry val
            carry = sumOfDigits / 10;
        }
        
        // At least one of the two lists 1/2 is fully explored
        // Append the rest of the node/digits vals in the non explored list to the sumlist
        sumListNode = appendNodesToList(rList1, sumListNode);
        sumListNode = appendNodesToList(rList2, sumListNode);
        
        return sumListNode;
    }
    
private:
    
    ListNode*
    reverseList(ListNode* head) {
        ListNode *prev = nullptr;
        ListNode *curr = head;
        while (curr) {
            // Reverse the link between the curr and previous nodes
            ListNode* next = curr->next;
            curr->next = prev;
            // Advance to next node/set up the pre-requisites
            prev = curr;
            curr = next;
        }
        
        return prev;
    }
    
    inline ListNode*
    appendNewNodeToListHead(int val, ListNode* prevHead) {
        ListNode* newHead = new ListNode(val, prevHead);
        return newHead;
    }
    
    inline ListNode*
    appendNodesToList(ListNode* srcList, ListNode* dstList) {
        while (srcList) {
            dstList = appendNewNodeToListHead(srcList->val, dstList);
            srcList = srcList->next;
        }
        return dstList;
    }
};
