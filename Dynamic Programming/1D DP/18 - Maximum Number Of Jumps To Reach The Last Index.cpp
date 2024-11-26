// Code to find the maximum number of jumps required to reach the last index of the array with following the mentioned rules ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the maximum number of jumps, using recursion with memoization - O(N*N) & O(N)
    int maxJumpsToReachLastIndex(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> memory(n, -1);
        int maxJumps = solveWithMemo(memory, nums, n, target, 0);
        return (maxJumps == INT_MIN) ? -1 : maxJumps;
    }

private:
    // O(N*N) & O(N+N)
    int solveWithMemo(vector<int>& memory, vector<int>& nums, int n, int target, int startIndex) {
        // Edge case: If you reached the last index then return 0 as a valid indication of it
        if(startIndex == n-1)
            return 0;

        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[startIndex] != -1)
            return memory[startIndex];
        
        // Stores the result value
        int maxJumps = INT_MIN;

        // Explore all the possibilities of jumping from the current index and update the result by the maximum value
        for(int jump = startIndex+1; jump < n; ++jump) {
            if((-target <= nums[jump] - nums[startIndex]) && (nums[jump] - nums[startIndex] <= target)) {
                int nextJumps = solveWithMemo(memory, nums, n, target, jump);
                if(nextJumps != INT_MIN) {
                    maxJumps = max(maxJumps, 1 + nextJumps);
                } 
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[startIndex] = maxJumps;
    }

    // O(N^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int n, int target, int startIndex) {
        // Edge case: If you reached the last index then return 0 as a valid indication of it
        if(startIndex == n-1)
            return 0;

        // Stores the result value
        int maxJumps = INT_MIN;

        // Explore all the possibilities of jumping from the current index and update the result by the maximum value
        for(int jump = startIndex+1; jump < n; ++jump) {
            if((-target <= nums[jump] - nums[startIndex]) && (nums[jump] - nums[startIndex] <= target)) {
                int nextJumps = solveWithoutMemo(nums, n, target, jump);
                if(nextJumps != INT_MIN) {
                    maxJumps = max(maxJumps, 1 + nextJumps);
                } 
            }
        }

        // Return the result value
        return maxJumps;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp {
public:
    // Method to find the maximum number of jumps, using 1D tabulation - O(N*N) & O(N)
    int maxJumpsToReachLastIndex(vector<int>& nums, int target) {
        int n = nums.size();

        // 1D table: dp[index] represents the maximum number of jumps required to reach the individual index
        vector<int> dp(n, INT_MIN);

        // Initialize the edge case: If you reached the last index then return 0 as a valid indication of it
        dp[n-1] = 0;

        // Fill the rest of the table
        for(int startIndex = n-2; startIndex >= 0; --startIndex) {
            int maxJumps = INT_MIN;
            
            for(int jump = startIndex+1; jump < n; ++jump) {
                if((-target <= nums[jump] - nums[startIndex]) && (nums[jump] - nums[startIndex] <= target)) {
                    int nextJumps = dp[jump];
                    if(nextJumps != INT_MIN) {
                        maxJumps = max(maxJumps, 1 + nextJumps);
                    } 
                }
            }
            
            dp[startIndex] = maxJumps;
        }

        int maxJumps = dp[0];

        // Return the result value
        return (maxJumps == INT_MIN) ? -1 : maxJumps;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/maximum-number-of-jumps-to-reach-the-last-index/description/
