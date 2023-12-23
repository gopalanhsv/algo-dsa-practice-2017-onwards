// l => logs.size()
// Time complexity : O(l)
// Space complexity : O(l)

class Solution {
public:
    vector<int>
    exclusiveTime(int n, vector<string>& logs) {
        // timesV[i] is the total of the exclusive times of function 'i' from
        // amongst the logs parsed so far
        vector<int> timesV(n, 0);
        
        auto prevEventTStamp = 0;
        auto prevEventTypeIsStart = false;

        // Stack holding the current functions in progress (which have started
        // but not yet ended)
        stack<int> fnCallStk;
        
        // Iterate over each log string sequentially
        for (auto & log : logs) {
            int fnId;
            bool currEventTypeIsStart;
            long timeStamp;
            // Parse current log string to determine current function event parameters
            parseLog(log, fnId, currEventTypeIsStart, timeStamp);
            
            long durationSincePrevEvent = 0;
            if (!currEventTypeIsStart) {
                // Current event is function call end
                if (prevEventTypeIsStart) {
                    // Previous event was function call start
                    // Current function execs over the time interval
                    // [prevEventTStamp, timeStamp]
                    durationSincePrevEvent = timeStamp - prevEventTStamp + 1;
                } else {
                    // Previous event was function call end
                    // Current function execs over the time interval
                    // [prevEventTStamp + 1, timeStamp + 1]
                    durationSincePrevEvent = timeStamp - prevEventTStamp;
                }
                // Update the time duration for which the function at top of
                // gets executed to include the current event
                auto & runningFnId = fnCallStk.top();
                timesV[runningFnId] += durationSincePrevEvent;
                // Function at stack top is done/ended => pop if off the stack
                fnCallStk.pop();
            } else {

                // Current event is for function call start
                if (!fnCallStk.empty()) {
                    
                    // Update the time duration for the function event occuring
                    // immediately prior to the current event
                    if (prevEventTypeIsStart) {
                        // Previous event was function call start
                        // Function at the top of the stack (previous event function)
                        // execs over the time interval
                        // [prevEventTStamp, timeStamp - 1]
                        durationSincePrevEvent = timeStamp - prevEventTStamp;
                    } else {
                        // Previous event was function call end
                        // Function at the top of the stack (if non-empty)
                        // execs over the time interval
                        // [prevEventTStamp + 1, timeStamp - 1]
                        durationSincePrevEvent = timeStamp - 1 - prevEventTStamp;
                    }
                    auto & runningFnId = fnCallStk.top();
                    timesV[runningFnId] += durationSincePrevEvent;
                }
                
                // Add current function to stack as its the most recent in progress
                fnCallStk.push(fnId);
            }

            prevEventTStamp = timeStamp;
            prevEventTypeIsStart = currEventTypeIsStart;
        }
        
        return timesV;
    }

private:

    inline void
    parseLog(string& log, int& fnId, bool& start, long& timeStamp) {
        auto i = 0;
        // Determine called function id from the current log event
        fnId = 0;
        while (log[i] != ':') {
            fnId = (10 * fnId) + int(log[i] - '0');
            ++i;
        }
        // Determine if current log event represents called function start or end 
        ++i;
        start = (log[i] == 's');
        
        i = log.find(':', i);
        ++i;

        // Determine the time at which current log event occurs
        auto sLen = log.size();
        timeStamp = 0;
        while (i < sLen) {
            timeStamp = (10 * timeStamp) + int(log[i] - '0');
            ++i;
        }
    }
};
