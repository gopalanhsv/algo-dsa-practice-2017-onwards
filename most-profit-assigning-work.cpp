// j => num jobs (profit.size()), w => worker.size()
// Time complexity : O(jlogj + wlogw)
// Space complexity : O(j) + O(logj + logw)
class Solution {
public:
    int
    maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        // One job can be assigned multiple times to different workers and each worker
        // can do at most one job as per his/her difficulty level.
        // To maximize the profit, adopt the greedy approach of always assigning an unassigned
        // worker to the max profit yielding job (as per worker difficulty profile). This is
        // easily done by organising the jobs and workers in the respective ascending order of
        // difficulty/ability
        typedef struct _JobInfoT {
            int difficulty;
            int profit;
        } JobInfoT;
        vector<JobInfoT> jobInfoV;
        auto nJobs = profit.size();
        for (auto i = 0; i != nJobs; ++i) {
            JobInfoT ji;
            ji.difficulty = difficulty[i];
            ji.profit = profit[i];
            jobInfoV.emplace_back(ji);
        }
        // Sort the jobs as per the ascending order of difficulty. For jobs having the same difficulty,
        // order them in the descending order of their profits s.t. jobs yielding higher profit are
        // prioritised for the same difficulty level
        struct JobInfoCmpObj {
            bool
            operator()(const JobInfoT& ji1, const JobInfoT& ji2) {
                if (ji1.difficulty == ji2.difficulty) {
                    return ji1.profit > ji2.profit;
                }
                return ji1.difficulty < ji2.difficulty;
            }
        };
        sort(jobInfoV.begin(), jobInfoV.end(), JobInfoCmpObj());
        
        // Sort the workers in the ascending order of their ability levels
        sort(worker.begin(), worker.end());
        auto maxTotalProfit = 0;
        auto jobId = 0;
        // Tracks the max possible profit accruing to a worker on choosing job as per ability
        auto maxPossibleProfit = 0;
        // Iterate over the worker abilities sequentially in ascending order of abilities
        for (auto & workerAbility : worker) {
            // Select the job yielding maximum profit possible with current worker ability 
            while ((jobId < nJobs) && (jobInfoV[jobId].difficulty <= workerAbility)) {
                maxPossibleProfit = max(maxPossibleProfit, jobInfoV[jobId].profit);
                ++jobId;
            }
            maxTotalProfit += maxPossibleProfit;
        }
        
        return maxTotalProfit;
    }
};
