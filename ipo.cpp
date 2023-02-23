class Solution {
public:
    int
    findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        // To maximize the capital, adopt the greedy approach of choosing
        // a project from the list of possible projects (which are yet undone and
        // feasible with capital in hand) s.t. max capital gets added from
        // project profit post selected project completion. This devolves to
        // always selecting the project yielding the maximum profit (consequently
        // leading to maximum possible capital delta increase) from amongst
        // the yet uncompleted feasible projects with the min capital threshold
        // l.e. to capital in hand currently
        
        int nProjects = profits.size();
        typedef struct _ProjectInfoT {
            int profit;
            int capital;
        } ProjectInfoT;
        
        vector<ProjectInfoT> pInfoV;
        for (int i = 0; i != nProjects; ++i) {
            ProjectInfoT pi;
            pi.profit = profits[i];
            pi.capital = capital[i];
            pInfoV.emplace_back(pi);
        }

        typedef struct _ProjectInfoCapitalCmpObj {
            bool
            operator()(const ProjectInfoT& pi1, const ProjectInfoT& pi2) {
                return pi1.capital < pi2.capital;
            }
        } ProjectInfoCapitalCmpObj;
        
        /*priority_queue<ProjectInfoT, vector<ProjectInfoT>, ProjectInfoCapitalCmpObj> minHeap;
        for (auto & pi : pInfoV) {
            minHeap.push(pi);
        }*/
        sort(pInfoV.begin(), pInfoV.end(), ProjectInfoCapitalCmpObj());
        
        typedef struct _ProjectInfoProjectCmpObj {
            bool
            operator()(const ProjectInfoT& pi1, const ProjectInfoT& pi2) {
                return pi1.profit < pi2.profit;
            }
        } ProjectInfoProjectCmpObj;
        priority_queue<ProjectInfoT, vector<ProjectInfoT>, ProjectInfoProjectCmpObj> maxHeap;
        
        long capitalInHand = w;
        int pIdx = 0;
        while (k-- > 0) {
            
            while (pIdx < nProjects) {
                auto & pi = pInfoV[pIdx];
                if (pi.capital > capitalInHand) {
                    break;
                }
        
                maxHeap.push(pi);
                ++pIdx;
            }
            
            
            if (!maxHeap.empty()) {
                auto & pi = maxHeap.top();
                capitalInHand += pi.profit;
                maxHeap.pop();
            } else {
                break;
            }
            
            //--k;
        }
        
        return capitalInHand;
    }
};
