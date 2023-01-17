class Solution {
public:
    vector<string>
    readBinaryWatch(int turnedOn) {
        // Vector with all possible LED values
        _ledValueV = {
            8, 4, 2, 1, // Indices 0 to 3 are hour LED values
            32, 16, 8, 4, 2, 1 // Indices 4 to 9 are minute LED values
        };
        
        // Generate all possible LED combinations of LEDs which can be
        // be turned on for the specified number of 'on' LEDs via
        // DFS/backtracking
        generateValidLedCombinations(turnedOn, 0);
        
        return _possibleTimeStrsV;
    }
    
private:
    
    void
    computeValidTimesFromSelectedLeds() {
        // Iterate through the selected LEDs which are currently ON
        // and determine hour and minute values represented by them
        int min = 0;
        int hour = 0;
        for (auto ledId : _selectedLedV) {
            if (ledId <= 3) {
                // Hours LED
                hour += _ledValueV[ledId];
            } else {
                // Minutes LED
                min += _ledValueV[ledId];
            }
        }
        
        if ((hour <= 11) && (min <= 59)) {
            // Hour and minute vals represented by selected 'ON'
            // LEDs are in valid time range.
            
            // Generate the "hh:mm" string for time represented by 'ON' LEDs;
            // and append it to the list of possible times for the given
            // number of 'ON' LEDs
            string hhmmStr;
            
            if (hour >= 10) {
                hhmmStr += int('0' + (hour / 10));
            }
            hhmmStr += int('0' + (hour % 10));
            
            hhmmStr += ":";
            
            hhmmStr += int('0' + (min / 10));
            hhmmStr += int('0' + (min % 10));
            
            _possibleTimeStrsV.emplace_back(hhmmStr);
        }
    }
    
    void
    generateValidLedCombinations(int numLedsOn, int ledId) {
        if (numLedsOn == 0) {    
            // The specified number of LEDs to be turned 'on' are all
            // selected & stored in the selection list. Determine
            // the valid times which can represented using the
            // selected LEDs
            computeValidTimesFromSelectedLeds();
            return;
        }
        
        // Current ledId is invalid => all valid LEDs have been
        // examined in other DFS cycles
        if (ledId >= _ledValueV.size()) {
            return;
        }

        // Select LED at 'ledId' to be turned on
        _selectedLedV.emplace_back(ledId);
        // Generate combinations with LED at 'ledId' ON
        generateValidLedCombinations(numLedsOn - 1, ledId + 1); 
        // Backtrack/switch LED at 'ledId'
        _selectedLedV.pop_back();
        
        // Skip LED at 'ledId' while generating combinations
        // of LEDs to be turned ON
        generateValidLedCombinations(numLedsOn, ledId + 1);  
    }
    
    // Data members
    // Array of all possible LED values for hour and minute rows
    vector<int> _ledValueV;
    // Array of LEDs ids which are selected to be turned on 
    vector<int> _selectedLedV;
    // Array of all possible valid time combinations for the
    // specified set of 'on' LEDs
    vector<string> _possibleTimeStrsV;
};
