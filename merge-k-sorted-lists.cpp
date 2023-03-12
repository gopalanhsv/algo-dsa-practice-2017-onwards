// Heap approach
// Time complexity : O(nlogk)
// n -> total number of nodes, k -> # of lists
// Space complexity : O(k) k -> # of lists

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
    mergeKLists(vector<ListNode*>& lists) {
        return mergeKListsViaHeap(lists);
    }
    
private:

    ListNode*
    mergeKListsViaHeap(vector<ListNode*>& lists) {
        
        typedef struct _ListNodeCmpObj {
            bool
            operator()(const ListNode* lp1, const ListNode* lp2) {
                return lp1->val > lp2->val;
            }
        } ListNodeCmpObj;
        
        // Use a min-heap of size 'k' to always select the node with min
        // value from amongst nodes of the 'k' different linked lists.
        priority_queue<ListNode*, vector<ListNode*>, ListNodeCmpObj> minHeap;

        // Since the 'k' lists are in sorted order, the head node of each list
        // will have the min element for the respective list.
        // The next element to be added to end of the merged list would the
        // element with min value from amongst the 'k' sorted lists; i.e. the
        // element with min value amongst the head nodes of the 'k' sorted
        // lists. This is easily accomplished by employing a k-sized min heap
        // to store the head node elems of the respective lists

        // Iterate over the head nodes of each of the 'k' lists
        for (auto & listHead : lists) {
            if (listHead) {
                // Add the head node to min heap
                minHeap.push(listHead);
                // Advance head to the next node as node is processed
                listHead = listHead->next;
            }
        }
        
        // Build the sorted and merged list from heap
        ListNode* mergedListHead = nullptr;
        ListNode* mergedListTail = nullptr;
        while (!minHeap.empty()) {
            // Pop off the node at top of heap 
            auto minValListNode = minHeap.top();
            minHeap.pop();
            // Add the node which comes next to the popped off node
            // in the appropriate list to the heap. This ensures that
            // 'k' unprocessed min value nodes are always in the heap
            if (minValListNode->next) {
                minHeap.push(minValListNode->next);
            }
            //minValListNode->next = nullptr;
            
            // Append popped off node to the merged list - min value
            // element amongst the unprocessed nodes
            if (!mergedListHead) {
                mergedListHead = minValListNode;
            } else {
                mergedListTail->next = minValListNode;
            }
            // Update the list tail node
            mergedListTail = minValListNode;
        }
        
        if (mergedListTail) {
            mergedListTail->next = nullptr;
        }
        
        return mergedListHead;
    }
    
    
};
