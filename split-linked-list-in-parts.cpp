// n => num list nodes
// Time complexity : O(n)
// Space complexity : O(1)

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
    vector<ListNode*>
    splitListToParts(ListNode* head, int k) {
        
        // Num npodes in the original list
        int nNodes = numListNodes(head);
        // For splitting the list equally, determine the minimum number of nodes
        // which will be in each part post split and the number of leftover nodes
        int minNodesPerPart = nNodes / k;
        int nRemainingNodes = nNodes % k;
        
        vector<ListNode*> listPartsV(k, nullptr);
        // Iterate over the list nodes sequentially from beginning to end, building
        // each of the 'k' parts from 1 to k
        // Tracks the start/head node from the next new list part
        auto nextPartHead = head;
        // Build the 1st to kth part sequentially
        for (int i = 0; i != k; ++i) {
            auto currPartHead = nextPartHead;
            // Number of nodes in each part will the sum of the minimum nodes per part
            // plus one node if there are any remainder nodes left (i.e. nodes are distributed
            // equally from 1st to kth list with extra nodes assigned to earlier parts)
            int nNodesInCurrPart = minNodesPerPart;
            if (nRemainingNodes > 0) {
                ++nNodesInCurrPart;
                --nRemainingNodes;
            }
            // Build current list part consisting of 'nNodesInCurrPart' commencing from
            // node 'currPartHead' in the original list. 'nextPartHead' is the start node
            // for next part in original list commencing immediately after the nodes
            // for current part
            nextPartHead = buildSubList(currPartHead, nNodesInCurrPart);
            
            listPartsV[i] = currPartHead;
        }
        
        return listPartsV;
    }
    
private:
    
    inline int
    numListNodes(ListNode* head) {
        int n = 0;
        while (head) {
            ++n;
            head = head->next;
        }
        return n;
    }
    
    ListNode*
    buildSubList(ListNode* head, int nNodes) {
        // Build a sublist list of 'nNodes' commencing from 'head' node in
        // original list and return the immediate node after 'nNodes'
        
        // Advance 'nNodes - 1' node to prospective tail of list
        while (nNodes > 1) {
            head = head->next;
            --nNodes;
        }
        // Set tail node of sublist
        ListNode *nextNode = nullptr;
        if (nNodes > 0) {
            nextNode = head->next;
            head->next = nullptr;
        }
        return nextNode;
    }
};
