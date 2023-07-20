// Time complexity : O(asteroids.size()) / O(n)
// Space complexity : O(asteroids.size()) / O(n)

class Solution {
public:
    vector<int>
    asteroidCollision(vector<int>& asteroids) {
    
        // Stack contains asteriods which have not been destroyed
        // by collision from amongst those seen so far
        stack<int> stk;
        // Iterate over the asteroids sequentially from L->R
        for (auto & asteroid : asteroids) {
            if (asteroid > 0) {
                // Right moving asteroid. Add it to stack
                stk.push(asteroid);
            } else {
                // Left moving asteroid
                // This will keep on colliding with unexploded asteroids of smaller
                // size moving to the right till it encounters either a similar/bigger
                // right moving asteroid OR a left moving asteroid from among those
                // which have been seen so far
                bool currentAsteroidExplodes = false;
                int leftMovingAsteroidMagnitude = abs(asteroid);
                
                while (!stk.empty()) {
                
                    int lastSeenAsteroid = stk.top();
                    if (lastSeenAsteroid < 0) {
                        // Last seen asteroid is a left moving one, so
                        // no more collisions
                        break;
                    }
                    
                    // Last seen asteroid is a right moving one
                    if (lastSeenAsteroid < leftMovingAsteroidMagnitude) {
                        // Last seen asteriod is smaller => it explodes
                        stk.pop();
                    } else if (lastSeenAsteroid == leftMovingAsteroidMagnitude) {
                        // Last seen asterion is of same size => both asteroids explode
                        stk.pop();
                        currentAsteroidExplodes = true;
                        break;
                    } else {
                        // Last seen asteroid bigger => current asteroid explodes
                        currentAsteroidExplodes = true;
                        break;
                    }
                }
                
                if (!currentAsteroidExplodes) {
                    // Current asteroid safe => Add current asteroid to stack
                    stk.push(asteroid);
                }
            }
        }
        
        // Asteroids remaining in stack are the unexploded ones at end
        asteroids.resize(stk.size());
        int i = stk.size() - 1;
        while (!stk.empty()) {
            asteroids[i--] = stk.top();
            stk.pop();
        }
        return asteroids;
    }
};
