// Time complexity : O(num nodes)
// Space complexity : O(num nodes)

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node*
    cloneGraph(Node* node) {
        if (!node) {
            return nullptr;
        }
        
        return cloneGraphDFS(node);
    }
    
private:

    Node*
    cloneGraphDFS(Node* node) {

        Node* clonedNode = new Node(node->val);
        _nodeToClonedNodeTbl[node] = clonedNode;

        // Iterate over all neighbours of current node
        for (auto neighbor : node->neighbors) {

            // Check if neighbor explored and its clone exists
            unordered_map<Node*, Node*>::iterator mapIter
                = _nodeToClonedNodeTbl.find(neighbor);
            Node* clonedNeighbor;

            if (mapIter == _nodeToClonedNodeTbl.end()) {
                // Neighbor node not explored, do a DFS to create and explore
                clonedNeighbor = cloneGraphDFS(neighbor);
            } else {
                // Neighbor explored
                clonedNeighbor = mapIter->second; 
            }
            // Add edge between cloned node and its cloned neighbor
            clonedNode->neighbors.push_back(clonedNeighbor);
        }

        return clonedNode;
    }
    
    // Data members
    // Hash table maintaining mapping between old nodes and cloned nodes
    // It is populated the first time a node is visited by DFS and its clone is created
    // So behaves as a visited nodes marker too
    unordered_map<Node*, Node*> _nodeToClonedNodeTbl;
};
