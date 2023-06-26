// c => candidates
// Time complexity : O(k log c + c log c)
// Space complexity : O(c)
class Solution {
public:
    long long
    totalCost(vector<int>& costs, int k, int candidates) {
    
        int nWorkers = costs.size();

        // For selecting a worker during a session, candidate workers from both
        // front and back of the array are stored in a min heap with entries
        // having lower costs towards the heap top compared to those having lower
        // costs; tie-breaker on entries with same costs being the smaller index
        // entry (which is pushed towards heap top)
        typedef struct _WorkerInfoT {
            int cost;
            int idx;
        } WorkerInfoT;
        typedef struct _WorkerInfoCmpObj {
            bool
            operator()(const WorkerInfoT& wi1, const WorkerInfoT& wi2) {
                if (wi1.cost == wi2.cost) {
                    return wi1.idx > wi2.idx;
                }
                return wi1.cost > wi2.cost;
            }
        } WorkerInfoCmpObj;
        // Min heap for storing candidates
        priority_queue<WorkerInfoT, vector<WorkerInfoT>, WorkerInfoCmpObj> 
            frontCandidates, backCandidates;
        
        // Tracks the total hiring cost at each point in time
        long long hiringCost = 0;
        // Simulate each of the 'k' hiring sessions sequentially
        // Use two pointers to select candidate workers fron front and back
        int lo = 0;
        int hi = nWorkers - 1;
        for (int sId = 0; sId < k; ++sId) {
            
            // Select the appropriate worker for current session as per input rules
            
            // First select 'candidate' workers for consideration from both
            // the front and back of array excluding the workers who has been
            // selected for working in earlier sessions.
            // Done by having appropriately 'candidate' sized min heaps for both
            // the workers from array front and back separately
            // Candidates for consideration from front of array are added to front heap 
            while ((frontCandidates.size() < candidates) && (lo <= hi)) {
                WorkerInfoT wi;
                wi.cost = costs[lo];
                wi.idx = lo++;
                frontCandidates.push(wi);
            }
            
            // Candidates for consideration from back of array are added to back heap
            while ((backCandidates.size() < candidates) && (lo <= hi)) {
                WorkerInfoT wi;
                wi.cost = costs[hi];
                wi.idx = hi--;
                backCandidates.push(wi);
            }
            
            /*if (frontCandidatesMinHeap.empty() && backCandidatesMinHeap.empty()) {
                break;
            }*/

            // Select the worker for current session from the set of candidates
            // under consideration (worker with least cost/worker with smallest index
            // if there are multiple workers with same least cost)
            // Select least cost candidate and update hiring cost
            // Ensure to account for the scenario that one of array ends may not
            // have required number of candidates
            if (!frontCandidates.empty() && !backCandidates.empty()) {
                if (frontCandidates.top().cost <= backCandidates.top().cost) {
                    hiringCost += frontCandidates.top().cost;
                    frontCandidates.pop();
                } else {
                    hiringCost += backCandidates.top().cost;
                    backCandidates.pop();
                }
            } else if (!frontCandidates.empty()) {
                hiringCost += frontCandidates.top().cost;
                frontCandidates.pop();
            } else {
                hiringCost += backCandidates.top().cost;
                backCandidates.pop();
            }
        }
        
        return hiringCost;
    }
};
