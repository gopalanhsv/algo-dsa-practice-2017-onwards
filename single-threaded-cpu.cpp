class Solution {
public:

    // Structure describing task (task descriptor)
    typedef struct _TaskT {
        int enqueueTime;
        int processingTime;
        int index;
    } TaskT;
        
    // Comparator object to order tasks in priority Q
    struct TaskCmpObj {
        // If CPU is idle prefer task which is available/enqueued first
        // If several tasks enqueued up when CPU is idle, prefer
        // one with least processing time. If several task enqueued up with
        // same processing time prefer one with lowest index
        bool
        operator()(const TaskT& t1, const TaskT& t2) {
            if (t1.processingTime == t2.processingTime) {
                return t1.index > t2.index;
            }
            return t1.processingTime > t2.processingTime;
        }
    };
    
    vector<int>
    getOrder(vector<vector<int>>& tasks) {
        
        // Populate array of task descriptors
        int nTasks = tasks.size();
        vector<TaskT> tasksV(nTasks);
        for (int i = 0; i != nTasks; ++i) {
            TaskT t;
            t.enqueueTime = tasks[i][0];
            t.processingTime = tasks[i][1];
            t.index = i;
            tasksV[i] = t;
        }
        // Sort the tasks s.t. they get ordered in the ascending order of the enqueue time
        // s.t tasks which are enqueued earlier are processed earlier
        sort(tasksV.begin(), tasksV.end(),
             [&](const TaskT& t1, const TaskT& t2) { 
                 return t1.enqueueTime < t2.enqueueTime;});
        // CPU priority queue for processing tasks (which are
        // currently enqueued)
        priority_queue<TaskT, vector<TaskT>, TaskCmpObj> cpuQ;
        
        // Output vector of task ordering
        vector<int> cpuTaskOrderV(nTasks);
        int assignIdx = 0;
        int tId = 0; // Task id
        long int currTime = 0;
        while (assignIdx < nTasks) {
        
            // Update current time to the enqueue time of first
            // task in queue not yet processed (if the task 
            // enqueue/arrival time is much higher than current time)
            currTime = max(currTime, (long)tasksV[tId].enqueueTime);
            
            // Iterate over the tasks in the ascending order of enqueue times
            // Add the tasks to the cpu scheduler Q if they are already enqueued
            // up by the current time
            tId = enqueueAllArrivedTasks(currTime, tId, nTasks, tasksV, cpuQ);
            
            // Process all the tasks in the CPU Q as per specified order
            // and assign them to CPU
            while (!cpuQ.empty()) {
                // Process task at highest priority as per CPu scheduler
                auto & t = cpuQ.top();
                cpuTaskOrderV[assignIdx++] = t.index;
                // Update current time to account for task processing
                currTime += t.processingTime;
                cpuQ.pop();
                
                // Add any new tasks which have arrived by task end to scheduler
                tId = enqueueAllArrivedTasks(currTime, tId, nTasks, tasksV, cpuQ);
            }
        }
        
        return cpuTaskOrderV;
    }
    
private:
    int
    enqueueAllArrivedTasks(int currTime, int tId, int nTasks, vector<TaskT>& tasksV,
        priority_queue<TaskT, vector<TaskT>, TaskCmpObj>& cpuQ) {
        
        while ((tId < nTasks) && (tasksV[tId].enqueueTime <= currTime)) {
            cpuQ.push(tasksV[tId]);
            ++tId;
        }
        return tId;
    }
};
