// Code to find the minimum number of jumps to reach the last index of the array ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
public:
    // Method to find the minimum number of jumps, using recursion with memoization - O(N*N) & O(N)
    int minJumpsToReachLastIndex(vector<int>& nums) {
        int n = nums.size();
        vector<int> memory(n-1, -1);
        return solveWithMemo(memory, nums, n, 0);
    }

private:
    // O(N*N) & O(N+N)
    int solveWithMemo(vector<int>& memory, vector<int>& nums, int n, int index) {
        // Edge case: If you reached the last index then return 0 as a valid indication of it
        if(index == n-1)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index] != -1)
            return memory[index];

        // Stores the result value
        int minJumps = INT_MAX;

        // Explore all the possibilities of jumping from the current index and update the result by the minimum value
        for(int jump = 1; (jump <= nums[index] && index + jump < n); ++jump) {
            int nextJumps = solveWithMemo(memory, nums, n, index + jump);
            if(nextJumps != INT_MAX) {
                minJumps = min(minJumps, 1 + nextJumps);
            }
        }
        
        // Store the result value to the memoization table and then return it
        return memory[index] = minJumps;
    }

    // O(N^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int n, int index) {
        // Edge case: If you reached the last index then return 0 as a valid indication of it
        if(index == n-1)
            return 0;

        // Stores the result value
        int minJumps = INT_MAX;

        // Explore all the possibilities of jumping from the current index and update the result by the minimum value
        for(int jump = 1; (jump <= nums[index] && index + jump < n); ++jump) {
            int nextJumps = solveWithoutMemo(nums, n, index + jump);
            if(nextJumps != INT_MAX) {
                minJumps = min(minJumps, 1 + nextJumps);
            }
        }

        // Return the result value 
        return minJumps;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp {
public:
    // Method to find the minimum number of jumps, using 1D tabulation - O(N*N) & O(N)
    int minJumpsToReachLastIndex(vector<int>& nums) {
        int n = nums.size();

        // 1D table: dp[index] represents the minimum number of jumps required to reach the individual index
        vector<int> dp(n, INT_MAX);

        // Initialize the edge case: If you reached the last index then return 0 as a valid indication of it
        dp[n-1] = 0;

        // Fill the rest of the table
        for(int index = n-2; index >= 0; --index) {     
            int minJumps = INT_MAX;

            for(int jump = 1; (jump <= nums[index] && index + jump < n); ++jump) {
                int nextJumps = dp[index + jump];
                if(nextJumps != INT_MAX) {
                    minJumps = min(minJumps, 1 + nextJumps);
                }
            }

            dp[index] = minJumps;
        }

        // Return the result value
        return dp[0];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Greedy
Link  : https://leetcode.com/problems/jump-game-ii/description/
