// Binary Search Approach
// Time complexity : O(1)
// Space complexity : O(1)

// Iterative Approach
// Time complexity : O(neededApples)
// Space complexity : O(1)


class Solution {
public:
    long long
    minimumPerimeter(long long neededApples) {
        //return minPerimeterIterativeApproach(neededApples);
        return minPerimeterBinarySearchApproach(neededApples);
    }

    long long
    minPerimeterIterativeApproach(long long neededApples) {
        // For a square plot of side '2L' :
        // Top side will pass through (0, L) & num apples on top side
        // = L + 2((1 + L) + (2 + L) + (3 + L) + (4 + L) + (5 + L) + .. + (L + L))
        // = L + 2(L.L + L(1 + L)/2)
        // Next to top side will pass through (0, L - 1) & num apples on top side
        // = L - 1 + 2((1 + L - 1) + (2 + L - 1) + (3 + L - 1) + (4 + L - 1) + (5 + L - 1) + .. + (L + L - 1))
        // = L - 1 + 2(L(L - 1) + L(1 + L)/2)
        // Line at distance 'i' from X-axis  will pass through (0, i)/(0, -i) & num apples on that line
        // = i + 2((1 + i) + (2 + i) + (3 + i) + (4 + i) + (5 + i) + .. + (L + i))
        // = i + 2(Li + L(1 + L)/2) = i + 2Li + L(1 + L) = i(1 + 2L) + L(1 + L)
        
        // So, for a square plot of side '2L' : 
        // There is one line passing through (0, 0) with {0 + L(1 + L))} apples
        // Total of '2L' Lines passing through (0, 1/-1), (0, 2/-2), (0, 3/-3), ....,(0, i/-i), .., (0, L/-L)
        // with apple count as
        // = 2 { (1 + 2L)(1 + 2 + 3 + ... + L) + L.L(1 + L) }
        // = 2 { (1 + 2L)(1 + L)L/2 + L.L(1 + L) }
        // = (1 + 2L)(1 + L)L + (1 + L)2L.L = L(1 + L)(1 + 2L + 2L)
        // = L(1 + L)(1 + 4L)
        
        // So, total count of apples for a square of side '2L' is
        // = L(1 + L)(1 + 4L) + L(1 + L) = (1 + L)(L(1 + 4L) + L)
        // = (1 + L)(L(1 + 4L) + L) = (1 + L)(2L + 4LL) = 2L(1 + L)(1 + 2L)
        
        // Iterate over the possible square side lengths
        // incrementally till one is found which has the necessary amount of apples
        long long sqrSideLen = 0;
        // Number of apples enclosed/on square
        long long nSqrApples = 0;
        while (nSqrApples < neededApples) {
            // Increment square side length
            sqrSideLen += 2;
            
            // Update the count of apples on/enclosed by square
            nSqrApples = sqrSideLen * (1 + (sqrSideLen / 2)) * (1 + sqrSideLen);
        }
        
        long long sqrPerimeter = 4 * sqrSideLen;
        return sqrPerimeter;
    }
    
    long long
    minPerimeterBinarySearchApproach(long long neededApples) {
        // For a square plot of side '2L' :
        // Top side will pass through (0, L) & num apples on top side
        // = L + 2((1 + L) + (2 + L) + (3 + L) + (4 + L) + (5 + L) + .. + (L + L))
        // = L + 2(L.L + L(1 + L)/2)
        // Next to top side will pass through (0, L - 1) & num apples on top side
        // = L - 1 + 2((1 + L - 1) + (2 + L - 1) + (3 + L - 1) + (4 + L - 1) + (5 + L - 1) + .. + (L + L - 1))
        // = L - 1 + 2(L(L - 1) + L(1 + L)/2)
        // Line at distance 'i' from X-axis  will pass through (0, i)/(0, -i) & num apples on that line
        // = i + 2((1 + i) + (2 + i) + (3 + i) + (4 + i) + (5 + i) + .. + (L + i))
        // = i + 2(Li + L(1 + L)/2) = i + 2Li + L(1 + L) = i(1 + 2L) + L(1 + L)
        
        // So, for a square plot of side '2L' : 
        // There is one line passing through (0, 0) with {0 + L(1 + L))} apples
        // Total of '2L' Lines passing through (0, 1/-1), (0, 2/-2), (0, 3/-3), ....,(0, i/-i), .., (0, L/-L)
        // with apple count as
        // = 2 { (1 + 2L)(1 + 2 + 3 + ... + L) + L.L(1 + L) }
        // = 2 { (1 + 2L)(1 + L)L/2 + L.L(1 + L) }
        // = (1 + 2L)(1 + L)L + (1 + L)2L.L = L(1 + L)(1 + 2L + 2L)
        // = L(1 + L)(1 + 4L)
        
        // So, total count of apples for a square of side '2L' is
        // = L(1 + L)(1 + 4L) + L(1 + L) = (1 + L)(L(1 + 4L) + L)
        // = (1 + L)(L(1 + 4L) + L) = (1 + L)(2L + 4LL) = 2L(1 + L)(1 + 2L)
        
        // Max and min possible square side lengths
        long long minPossibleSqrSideLen = 0;
        // Max square side choosen empirically to prevent overflow
        long long maxPossibleSqrSideLen = 1000000; //neededApples;
        
        // Exec a binary search in the range [minPossibleSqrSideLen, maxPossibleSqrSideLen]
        // to determine the min possible square side s.t. that square holds the required
        // number of apples
        auto l = minPossibleSqrSideLen;
        auto r = maxPossibleSqrSideLen;
        while (l < r) {
            // Candidate square side
            auto mid = l + (r - l)/ 2;
            
            // Number of apples held by square of side 'mid'
            //auto nSqrApples =  sideLen * (1 + halfSideLen) * (1 + sideLen) / 2;
            auto nSqrApples =  mid * (1 + (mid / 2)) * (1 + mid);
            if (nSqrApples >= neededApples) {
                // This would be a upper bound on the square side len which
                // is sufficient to hold required number of apples
                r = mid;
                // Look for smaller square side length
            } else {
                // Look for higher square side lengths which can hold the
                // required number of apples
                l = mid + 1;
            }
        }
        
        // l & r converge in a pincer movement with 'l' being the min possible side
        // length of a sqaure which holds the given number of apples
        
        if (0 != (l & 0x1)) {
            // 'l' cannot be odd, as square is centered at (0, 0)
            // => needs to be upscaled to nearest even length
            ++l;
        }
        
        long long sqrPerimeter = 4 * l;
        return sqrPerimeter;
    }
};
