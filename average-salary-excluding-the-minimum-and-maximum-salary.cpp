// Time complexity : O(salary.size())
// Space complexity : O(1)

class Solution {
public:
    double
    average(vector<int>& salary) {
        if (salary.size() <= 2) {
            // Base case of zilch remaining after exclusions
            return 0;
        }
        
        double totalSalary = 0.0;
        int maxSalary = numeric_limits<int>::min();
        int minSalary = numeric_limits<int>::max();
        for (auto & s : salary) {
            totalSalary += s;
            maxSalary = max(maxSalary, s);
            minSalary = min(minSalary, s);
        }
        
        return (totalSalary - maxSalary - minSalary) / (salary.size() - 2);
    }
};
