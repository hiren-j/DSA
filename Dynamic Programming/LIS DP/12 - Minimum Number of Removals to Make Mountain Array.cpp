// Code to find the minimum number of elements to remove to make an array a mountain array ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the minimum number of elements to remove to make the given array a mountain array, using 1D tabulation - O(N*N) & O(N)
    int minimumMountainRemovals(vector<int>& nums) {
        int n = nums.size();

        vector<int> LIS(n, 1), LDS(n, 1);

        // Find the length of the LIS of each index
        for(int index = 0; index < n; ++index) 
            for(int prevIndex = 0; prevIndex < index; ++prevIndex) 
                if(nums[prevIndex] < nums[index])
                    LIS[index] = max(LIS[index], LIS[prevIndex] + 1);

        // Find the length of the LDS of each index
        for(int index = n-1; index >= 0; --index) 
            for(int nextIndex = n-1; nextIndex > index; --nextIndex) 
                if(nums[nextIndex] < nums[index])
                    LDS[index] = max(LDS[index], LDS[nextIndex] + 1);

        int maxLenBitonic = 0;

        // If the strictly increasing and strictly decreasing subsequence of each index exists then update the bitonic length by the maximum value
        for(int index = 0; index < n; ++index) 
            if(LIS[index] > 1 && LDS[index] > 1)
                maxLenBitonic = max(maxLenBitonic, LIS[index] + LDS[index] - 1);
        
        return n - maxLenBitonic;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Binary Search | Dynamic Programming | Greedy
Link  : https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/description/
