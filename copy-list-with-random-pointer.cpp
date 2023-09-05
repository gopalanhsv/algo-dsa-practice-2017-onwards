// Time complexity : O(num list nodes)
// Space complexity : O(1) / O(num list nodes) if output list is included
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node*
    copyRandomList(Node* head) {
    
        if (!head) {
            return head;
        }
        
        // Create a copy of the list with each of the original nodes and corresponding
        // new nodes fields set as follows:-
        // 1. 'val' field in cloned node is same as that of the original node
        // 2. 'next' field in the original node updated to its cloned node
        // (proxy hash table maintaining mapping original list node to its clone)
        // 3. 'random' field in cloned node is set to 'random' field of original node
        // 4. 'next' field in the cloned node is set to 'random' field of original node
        //    
        Node* currNode = head;
        Node* listCopyHead = nullptr;
        while (currNode) {
            // Step 1
            Node* newListCurrNode = new Node(currNode->val);
            if (!listCopyHead) {
                listCopyHead = newListCurrNode;
            }
            // Step 3 & 4
            newListCurrNode->random = currNode->random;
            newListCurrNode->next = currNode->random;
            // Step 3
            currNode->random = newListCurrNode;
            
            // Advance to next node in original list
            currNode = currNode->next;
        }
        
        // Iterate through the original list nodes in sequence. Link the 'random'
        // field for each of the nodes in the cloned list to the appropriate node
        // in the cloned list as using the info in 'random' field of both the cloned
        // and original node
        currNode = head;
        while (currNode) {
            // Pointer to original node clone in cloned list
            auto currNodeCloneP = currNode->random;
            // Original node 'random' field is stored in its clone
            auto currNodeRandomP = currNodeCloneP->random;
            // Update the 'random' field of nodes' clone to point to the appropriate node in the cloned
            // list; as per the mapping indicated initially in the 'random' field of original node
            if (currNodeRandomP) {
                currNodeCloneP->random = currNodeRandomP->random;
            } else {
                currNodeCloneP->random = nullptr;
            }
            // Advance to next node in original list
            currNode = currNode->next;
        }
        // Iterate through the original list nodes in sequence. Link the nodes in cloned nodes
        // in sequence and revert the 'random' field values for nodes in original list
        currNode = head;
        while (currNode) {
            // Pointer to the original nodes' clone
            auto currNodeCloneP = currNode->random;
            auto currNodeNextP = currNode->next;
            // Revert the original node 'random' field (hidden in its cloned
            // node 'next' field)
            auto currNodeRandomP = currNodeCloneP->next;
            currNode->random = currNodeRandomP;
            // Link the current node in cloned list to the appropriate next node in cloned list
            if (currNodeNextP) {
                currNodeCloneP->next = currNodeNextP->random;
            } else {
                currNodeCloneP->next = nullptr;
            }
            // Advance to next node in original list
            currNode = currNode->next;
        }
        
        return listCopyHead;
    }
};
