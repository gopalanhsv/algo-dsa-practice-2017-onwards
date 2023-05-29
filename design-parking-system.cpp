// Time complexity : O(1)
// Space complexity : O(1)

class ParkingSystem {
public:
    ParkingSystem(int big, int medium, int small) {
        _nSlotAvlPerCarTypeTbl.resize(4);
        _nSlotAvlPerCarTypeTbl[1] = big;
        _nSlotAvlPerCarTypeTbl[2] = medium;
        _nSlotAvlPerCarTypeTbl[3] = small;
    }
    
    bool
    addCar(int carType) {
        if (_nSlotAvlPerCarTypeTbl[carType] > 0) {
            // Slots available for this car type => park car
            --_nSlotAvlPerCarTypeTbl[carType];
            return true;
        }
        // No parking slot for given car
        return false;
    }
    
private:

    // Table maintaining the number of car park slots available per car type
    // (index 1 for small cars, index 2 for medium cars, index 3 for big cars)
    vector<int> _nSlotAvlPerCarTypeTbl;
};

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */
