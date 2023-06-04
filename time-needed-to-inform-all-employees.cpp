// Bottom up DFS approach
// Time complexity : O(num employees)
// Space complexity : O(num employees)
//
//
// Top down DFS approach
// Time complexity : O(num employees)
// Space complexity : O(num employees)

class Solution {
public:
    int
    numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        //return numMinutesViaTopDownDfs(n, headID, manager, informTime);
        return numMinutesViaBottomUpDfs(n, headID, manager, informTime);
    }
    
private:
    
    int
    bottomUpDfs(
        int empId, vector<int>& manager, vector<int>& informTime, vector<int>& timeForInfoToReachEmpV) {
        // Manager for current employee
        int mgrId = manager[empId];
        
        // Current employee is the head
        if (mgrId == -1) {
            return 0;
        }
        
        // Time for info to reach current employee is unknown, so compute it
        // by traversing up the management hierarchy
        if (timeForInfoToReachEmpV[empId] == 0) {
            // This would be time taken by employee manager to disseminate info + time taken for info
            // to reach the manager
            timeForInfoToReachEmpV[empId] =
                informTime[mgrId] + bottomUpDfs(mgrId, manager, informTime, timeForInfoToReachEmpV);
        }
                                                       
        return timeForInfoToReachEmpV[empId];
    }
    
    int
    numMinutesViaBottomUpDfs(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        
        _timeToInformAllEmployees = 0;
        vector<int> timeForInfoToReachEmpV(n, 0);
        // Iterate over all employees
        for (int e = 0; e != n; ++e) {
            // For each employee, determine the time for info from head to percolate
            // via bottom up DFS. Reuse the time if already calculated earlier. Max of
            // the time calculated as such would be the reqd answer
            _timeToInformAllEmployees =
                max(_timeToInformAllEmployees,
                    bottomUpDfs(e, manager, informTime, timeForInfoToReachEmpV));
        }
        
        return _timeToInformAllEmployees;
    }
    
    int
    numMinutesViaTopDownDfs(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        // Create management tree hierarchy by forming an adjacency list of
        // the graph with each vertex being an employee and the list of
        // subordinates of an employee being the neighbour vertices
        createCompanyHierarchyTree(n, manager, headID);
        
        // Do a DFS/BFS traversal commencing from the company head and visit all
        // the employees. Track the amount of time it takes to inform each and
        // every employee.
        _timeToInformAllEmployees = 0;
        informAllEmployeesViaDfs(headID, informTime, 0);
        return _timeToInformAllEmployees;
    }
    
    void
    informAllEmployeesViaDfs(int empId, vector<int>& informTimeV, int totalTimeElapsed) {
        
        unordered_map<int, vector<int> >::iterator it = _employeeToSubordinatesTbl.find(empId);
        if (_employeeToSubordinatesTbl.end() == it) {
            // No more subordinates. Update the max time to inform all employees
            _timeToInformAllEmployees = max(_timeToInformAllEmployees, totalTimeElapsed);
            return;
        }
        
        // Iterate over all the subordinates of the current employee and inform them
        auto & subordinatesV = it->second;
        // Add time taken to speak to all subordinates
        totalTimeElapsed += informTimeV[empId];
        // Subordinates need to inform down the chain 
        for (auto & subOrdId : subordinatesV) {
            informAllEmployeesViaDfs(subOrdId, informTimeV, totalTimeElapsed);
        }
    }
    
    void
    createCompanyHierarchyTree(int n, vector<int>& manager, int headId) {
        // Iterate over all employees
        for (int i = 0; i != n; ++i) {
            // Skip the org head
            if (i != headId) {
                // Create a mapping from manager of current employee to employee.
                auto & mgr = manager[i];
                _employeeToSubordinatesTbl[mgr].emplace_back(i);
            }
        }
    }
    
    // Data members
    
    // Adjacency list of graph mapping an employee to respective subordinates
    unordered_map<int, vector<int> > _employeeToSubordinatesTbl;
    int _timeToInformAllEmployees;
};
