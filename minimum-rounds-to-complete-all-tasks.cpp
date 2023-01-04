class Solution {
public:
    int
    minimumRounds(vector<int>& tasks) {
        // Hash table maintaining mapping from task difficulty level
        // to number of tasks at that difficulty level
        unordered_map<int, int> numTasksPerLevelTbl;  
        for (auto & level : tasks) {
            numTasksPerLevelTbl[level]++;
        }
        
        // Since each processing round can process groups of either 2 or 3 tasks at a
        // time (of the same difficulty level); to complete all the tasks in the min
        // number of possible rounds, adopt the greedy approach of execing 3 tasks in
        // a group (at a level) as much as possible, and any remaining ones in same
        // level in groups of 2
        int minRounds = 0;
        // Iterate over table of tasks grouped on a difficulty level basis
        for (auto & entry : numTasksPerLevelTbl) {
            // entry => hash table entry
            // Number of tasks at the current difficulty level
            // (of entry.first)
            auto & nTasksAtCurrLvl = entry.second;
            if (1 == nTasksAtCurrLvl) {
                // Not possible to complete tasks at this level
                return -1;
            }
            
            // Compute the maximum number of 3-task groups into which
            // tasks at the current difficulty level can be grouped into
            int nGroupOf3Tasks = nTasksAtCurrLvl / 3;
            // Remaining/leftover tasks after dividing tasks
            // into groups of 3 tasks each
            int nRemainingTasks = nTasksAtCurrLvl % 3;
            // All tasks at current level can be evenly divided in groups of 3
            // Exec 3 tasks in each round
            // 0 == nRemainingTasks
            // minRounds += nGroupOf3Tasks;
            // All tasks at current level can be evenly divided in groups of 3
            // except 1 remaining task. Exec 4 tasks in groups of 2 over 2 rounds;
            // and remaining tasks with 3 tasks per round
            // 1 == nRemainingTasks
            // minRounds += (nGroupOf3Tasks - 1);
            // minRounds += 2;
            // All tasks at current level can be evenly divided in groups of 3
            // except 2 remaining tasks. Exec 2 tasks in group of 2 over 1 round;
            // and remaining tasks with 3 tasks per round
            // 2 == nRemainingTasks
            // minRounds += nGroupOf3Tasks;
            // minRounds += 1;
 
            // Above set of calcs are summarized via following 3 statements
            minRounds += nGroupOf3Tasks;
            if (0 != nRemainingTasks) {
                ++minRounds;
            }
        }
        
        return minRounds;
    }
};
