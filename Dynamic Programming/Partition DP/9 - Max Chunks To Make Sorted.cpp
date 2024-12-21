// Code to find the largest number of chunks that we can make to sort the array. You are given an integer array arr of length n that represents a permutation of the integers in the range [0, n - 1]. We split arr into some number of chunks (i.e., partitions), and individually sort each chunk. After concatenating them, the result should equal the sorted array ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(N^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int startIndex, int prevChunkMax) {
        if(startIndex == n)
            return 0; // Handle the edge case when there's no element 

        int minElement = INT_MAX;
        int maxElement = INT_MIN;
        int maxChunks  = INT_MIN;

        for(int index = startIndex; index < n; ++index) {
            minElement = min(minElement, nums[index]);
            maxElement = max(maxElement, nums[index]);
            if(prevChunkMax == -1 || prevChunkMax < minElement) {
                int nextChunks = solveWithoutMemo(nums, index + 1, maxElement);
                maxChunks = max(maxChunks, nextChunks + 1);
            }
            else {
                return INT_MIN;
            }
        }

        return maxChunks;
    }

    // O(N*N) & O(N+N)
    int solveWithMemo(vector<vector<int>>& dp, vector<int>& nums, int startIndex, int prevChunkMax) {
        if(startIndex == n)
            return 0; // Handle the edge case when there's no element 

        if(dp[startIndex][prevChunkMax + 1] != -1)
            return dp[startIndex][prevChunkMax + 1];

        int minElement = INT_MAX;
        int maxElement = INT_MIN;
        int maxChunks  = INT_MIN;

        for(int index = startIndex; index < n; ++index) {
            minElement = min(minElement, nums[index]);
            maxElement = max(maxElement, nums[index]);
            if(prevChunkMax == -1 || prevChunkMax < minElement) {
                int nextChunks = solveWithMemo(dp, nums, index + 1, maxElement);
                maxChunks = max(maxChunks, nextChunks + 1);
            }
            else {
                return INT_MIN;
            }
        }

        return dp[startIndex][prevChunkMax + 1] = maxChunks;
    }

public:
    // Method to find the largest number of chunks, using recursion with memoization - O(N^2) & O(N)
    int maxChunksToSorted(vector<int>& nums) {
        n = nums.size();
        vector<vector<int>> dp(n, vector<int>(12, -1));
        return solveWithMemo(dp, nums, 0, -1);        
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the largest number of chunks, using 2D tabulation - O(N^2) & O(N)
    int maxChunksToSorted(vector<int>& nums) {
        int n = nums.size();

        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(12, INT_MIN));

        // Initialize the edge case
        for(int prevChunkMax = 0; prevChunkMax < 12; ++prevChunkMax)
            dp[n][prevChunkMax] = 0;

        // Fill the rest of the table
        for(int startIndex = n-1; startIndex >= 0; --startIndex) {
            for(int prevChunkMax = 11; prevChunkMax >= -1; --prevChunkMax) {
                int minElement = INT_MAX;
                int maxElement = INT_MIN;
                int maxChunks  = INT_MIN;
                for(int index = startIndex; index < n; ++index) {
                    minElement = min(minElement, nums[index]);
                    maxElement = max(maxElement, nums[index]);
                    if(prevChunkMax == -1 || prevChunkMax < minElement) {
                        int nextChunks = dp[index + 1][maxElement];
                        maxChunks = max(maxChunks, nextChunks + 1);
                    }
                    else {
                        break;
                    }
                }   
                if(prevChunkMax + 1 < 12) 
                    dp[startIndex][prevChunkMax + 1] = maxChunks;
            }
        }

        // Return the result value
        return dp[0][0];        
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Stack | Greedy | Sorting | Monotonic Stack
Link  : https://leetcode.com/problems/max-chunks-to-make-sorted/description/
