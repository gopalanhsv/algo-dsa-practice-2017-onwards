// Time complexity : O(senate.size())
// Space complexity : O(senate.size())

class Solution {
public:
    string
    predictPartyVictory(string senate) {
        // Since each senator is smart and will play the best strategy for a self
        // party win; the senator should apply the greedy approach of maximizing
        // the senators from self party full voting rights vote and do his best to
        // curtail the rights of maximum senators from the opposite party at any
        // given point in time.
        // Since a senator can curtail the voting rights at most one senator from
        // the other party who come after him to vote, he should curtail the
        // voting right of the closest other party senator having full rights who
        // come after him to vote. This will give a better chance to more self party
        // senators who come after him to vote retain their rights; and in turn
        // ban more of other party senators increasing their party win probabilities
        
        // Queue of 'R' & 'D' senator ids yet to excercise their voting rights
        // by participating in the procedure
        queue<int> rPartySenatorsQ;
        queue<int> dPartySenatorsQ;
        int nSenators = senate.size();
        for (int id = 0; id != nSenators; ++id) {
            if (senate[id] == 'R') {
                rPartySenatorsQ.push(id);
            } else {
                dPartySenatorsQ.push(id);
            }
        }
        
        while (!rPartySenatorsQ.empty() && !dPartySenatorsQ.empty()) {
            auto rSenatorId = rPartySenatorsQ.front();
            rPartySenatorsQ.pop();
            auto dSenatorId = dPartySenatorsQ.front();
            dPartySenatorsQ.pop();
            if (rSenatorId < dSenatorId) {
                rPartySenatorsQ.push(rSenatorId + nSenators);
            } else {
                dPartySenatorsQ.push(dSenatorId + nSenators);
            }
        }
        
        return (dPartySenatorsQ.empty()) ? "Radiant" : "Dire";
    }
};
