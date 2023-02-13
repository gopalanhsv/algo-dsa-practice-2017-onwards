class Solution {
public:
    vector<vector<string>>
    displayTable(vector<vector<string>>& orders) {

        // Organize orders as per tables where they are served dropping
        // unnecessary information
        organizeOrders(orders);
        
        // Construct the output display
        vector<vector<string> > displayV;
        constructOutputDisplay(displayV);
        
        return displayV;
    }
    
private:
    
    void
    organizeOrders(vector<vector<string>>& orders) {
        // Build Hash table maintaining a mapping between table id and the respective
        // item/item count information ordered/served from/at the particular table
        // Iterate over each order
        for (auto & order : orders) {
            // Table at which current order is served
            int tableId = stoi(order[1]);
            // Name of current dish ordered
            auto & dishName = order[2];
            
            // Update the count of the current dish served at the current table
            _tblIdToItemCntInfoTbl[tableId][dishName]++;
            
            // Add both the table id and dish name to sorted set
            _tableIds.insert(tableId);
            _items.insert(dishName);
        }
    }

    void
    constructOutputDisplay(vector<vector<string> >& displayV) {
        
        // 1st row of output display (has only the labels)
        vector<string> firstRowV;
        firstRowV.emplace_back("Table");
        for (auto & itemName : _items) {
            firstRowV.emplace_back(itemName);
        }
        displayV.emplace_back(firstRowV);
        
        // Remaining rows of output display in ascending order of table ids 
        // with the count of dishes served at the particular table id
        // Iterate over table ids in ascending order
        for (auto & tblId : _tableIds) {
            vector<string> currRowV;
            // Add current table id to output display
            currRowV.emplace_back(to_string(tblId));
            // Data of dishes served at current table
            auto & currTblDishInfo = _tblIdToItemCntInfoTbl[tblId];
            // Iterate over all dishes/items served in the restaurant in the
            // ascending order of the dish names
            for (auto & name : _items) {
                // Determine the count of current item/dish served at current table
                auto iter = currTblDishInfo.find(name);
                int nCurrItems = 0;
                if (iter != currTblDishInfo.end()) {                    
                    nCurrItems = iter->second;
                }
                // Add the count of current dish served at current table to output
                currRowV.emplace_back(to_string(nCurrItems));
            }
            
            // Add current row display to output
            displayV.emplace_back(currRowV);
        }
    }
    
    // Data members
    // Table ids of tables at which at least one order gets served
    // (organized in ascending order)
    set<int> _tableIds;
    // All dishes/items served (organized in ascending order)
    set<string> _items;
    // Hash table maintaining a mapping between table id and the respective
    // item/item count information ordered/served from/at the particular table
    unordered_map<int, unordered_map<string, int> > _tblIdToItemCntInfoTbl;
};
