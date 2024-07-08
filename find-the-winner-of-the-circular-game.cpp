// Simulation Approach
// Time complexity : O(nk)
// Space complexity : O(n)
class Solution {
public:
    int
    findTheWinner(int n, int k) {
        return findTheWinnerViaSimulation(n, k);
    }
    
private:
    
    int
    findTheWinnerViaSimulation(int n, int k) {
        // The game can be simulated using a queue for the circle
        // 1. All the 'n' friends are initially placed in the Q
        // 2. In each round, 'k - 1' dequeue operations are done from Q front
        // and re-added to Q back. The person in front of Q is then dropped
        // as he would be the 'k' the person for the round.
        // 3. Repeat step (2) till only 1 person is left in the Q
        queue<int> simQ;
        // Add all the friends [1, n] to simulation Q
        for (auto pId = 1; pId <= n; ++pId) {
            simQ.push(pId);
        }
        
        // Play the game till only a single person is left in the Q/circle
        while (simQ.size() > 1) {
            // Counting 'k' friends clockwise is done by dequeueing 'k - 1' friends
            // from Q front and re-adding them to Q back in the same order
            // 'k' the friend then is at Q front
            for (int i = 1; i <= k - 1; ++i) {
                auto pId = simQ.front();
                simQ.pop();
                simQ.push(pId);
            }
            // 'k'th person is current round loser
            simQ.pop();
        }
        // Sole person is the winner
        return simQ.front();
    }
};
