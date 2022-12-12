class Solution {
public:
    int
    maxArea(vector<int>& height) {
        // Base case of single/no vertical pillar. Water cannot be stored
        if (height.size() < 2) {
            return 0;
        }
        
        // Water volume between any two pillars is determined solely by the height
        // of the smaller of the two pillars and the distance between them
        
        // Have two pointer representing the two pillars/lines enclosing the
        // water and move them towards each other. At any time after computing
        // water area between two pillars, fix the pillar/line with higher
        // height (as it will lead to more water vol) and advance from 
        // smaller line/pillar towards bigger pillar hoping that next pillar
        // might be taller leading to more water volume
        int l = 0, r = height.size() - 1;
        int maxWaterArea = 0;
        while (l < r) {
            // Heights of left and right water enclosing vertical pillars
            auto & lh = height[l];
            auto & rh = height[r];
            // Area of water enclosed between the two vertical pillars
            // Update the max water enclosed
            maxWaterArea = max((r - l) * min(lh, rh), maxWaterArea);
            if (lh < rh) {
                // Left pillar lower than right pillar
                // Greedy strategy, Fix right pillar and advance left pillar
                ++l;
            } else {
                // Right pillar lower than left pillar
                // Greedy strategy, Fix left pillar and advance right pillar
                --r;
            }
        }
        return maxWaterArea;
    }
};
