class Solution {
public:
    string
    categorizeBox(int length, int width, int height, int mass) {
    
        // Determine box bulkiness
        long boxVol = (long)length * width * height;
        bool bulky = false;
        if ((length >= 10000) || (width >= 10000) ||
            (height >= 10000)|| (boxVol >= 1000000000)) {
            bulky = true;
        }
        // Determine box heaviness
        bool heavy = (mass >= 100) ? true : false;
        
        // Categorize box
        if (!bulky) {
            return (!heavy) ? "Neither" : "Heavy";
        }
        return (!heavy) ? "Bulky" : "Both";
    }
};
