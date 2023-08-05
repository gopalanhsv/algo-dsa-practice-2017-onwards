// Time complexity : O(hours.size())
// Space complexity : O(1)
class Solution {
public:
    int
    numberOfEmployeesWhoMetTarget(vector<int>& hours, int target) {

        int nEmployees = 0;
        for (auto & workedHrs : hours) {
            if (workedHrs >= target) {
                ++nEmployees;
            }
        }
        return nEmployees;
    }
};
