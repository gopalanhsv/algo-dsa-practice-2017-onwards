// n => people.size()
// Time complexity : O(nlogn)
// Space complexity : O(log n)

class Solution {
public:
    int
    numRescueBoats(vector<int>& people, int limit) {
        // A boat can carry 2 people at the most provided the sum of their weights does't exceed
        // the specified limit. To minimize the number of boats, adopt the greedy approach of
        // maximizing the number of people alloted per boat should be maximized (i.e 2)
        
        // From amongst the people yet to assigned to boats; the heaviest person is either solely
        // assigned a boat; or combined with the lightest unassigned person - provided that their
        // combined weights is within limits.
        // If the heaviest person cannot be combined with the lightest, combination with
        // any of the remaining people automatically exceeds limit
        
        // Sort the people in the non-decreasing order of weights
        sort(people.begin(), people.end());
        int l = 0;
        int r = people.size() - 1;
        int nBoats = 0;
        while (l <= r) {
            // Attempt to put the heaviest and the lightest of the unassigned
            // people in a single boat
            if (people[l] + people[r] <= limit) {
                // Heaviest and lightest assigned to a single boast
                ++nBoats;
                // Prune the heaviest and lightest people from
                // list of yet to be assigned
                ++l;
                --r;
            } else { // people[l] + people[r] > limit
                // Heaviest and lightest exceed weight limit
                // Assign heaviest to a boat and prune heaviest
                ++nBoats;
                --r;
            }
        }
        
        return nBoats;
    }
};
