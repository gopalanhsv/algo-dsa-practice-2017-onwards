// n => seats.size() / students.size()
// Time complexity : O(nlogn)
// Space complexity : O(logn)

class Solution {
public:
    int
    minMovesToSeat(vector<int>& seats, vector<int>& students) {
        // To seat all students with the minimum number of moves; adopt the greedy
        // approach of seating a student at the closest free seat from amongst
        // the pool of available free seats
        
        // Sort both the students and seats in non-decreasing order of their locations;
        // Assign 1st student to 1st free seat; 2nd student to next free seat and so on
        sort(seats.begin(), seats.end());
        sort(students.begin(), students.end());
        
        int nMoves = 0;
        for (auto i = 0; i != seats.size(); ++i) {
            // student[i] is seated at seat[i]
            // Num moves reqd is equal to the location difference
            nMoves += abs(seats[i] - students[i]);
        }
        
        return nMoves;
    }
};
