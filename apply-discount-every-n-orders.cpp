// Time complexity :
// getBill() : O(num products being billed)
// Space complexity : O(number of unique products)

class Cashier {
public:
    Cashier(int n, int discount, vector<int>& products, vector<int>& prices) {
        _nCustomersSeen = 0;
        _discountCustomerNumber = n;
        _discountFactor = (double(100 - discount)) / 100;
        // Populate the product ids to their respective price mappings 
        int nProducts = products.size();
        for (auto i = 0; i != nProducts; ++i) {
            _productToPriceTbl[products[i]] = prices[i];
        }
    }
    
    double
    getBill(vector<int> product, vector<int> amount) {
        // Compute bill value prior to discounting
        auto nProducts = product.size();
        double totalBillVal = 0.0;
        for (auto i = 0; i != nProducts; ++i) {
            auto prodPrice = _productToPriceTbl[product[i]];
            auto qty = amount[i];
            totalBillVal += (prodPrice * qty);
        }
        
        // Update number of customers seen
        if (++_nCustomersSeen == _discountCustomerNumber) {
            // Apply discount and reset customer count
            _nCustomersSeen = 0;
            totalBillVal *= _discountFactor;
        }
        
        return totalBillVal;
    }
    
private:
    // Num customers seen so far (rolling number from 1 to n)
    int _nCustomersSeen;
    // Customer multiple at which discount is applied
    int _discountCustomerNumber;
    // Hash table mapping product id to their respective prices
    unordered_map<int, int> _productToPriceTbl;
    // Multiple factor to be applied to total price to get discounted price
    double _discountFactor;
};

/**
 * Your Cashier object will be instantiated and called as such:
 * Cashier* obj = new Cashier(n, discount, products, prices);
 * double param_1 = obj->getBill(product,amount);
 */
