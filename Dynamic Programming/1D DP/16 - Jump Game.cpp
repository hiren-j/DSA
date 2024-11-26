// Code to check whether you can reach the last index of the array or not. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to check whether you can reach the last index or not, using recursion with memoization - O(N*N) & O(N)
    bool canJumpToLastIndex(vector<int>& nums) {
        int n = nums.size();
        vector<int> memory(n-1, -1);
        return solveWithMemo(memory, nums, n, 0);
    }

private:
    // O(N*N) & O(N+N)
    int solveWithMemo(vector<int>& memory, vector<int>& nums, int n, int index) {
        // Edge case: If you reached the last index then return true
        if(index == n-1)
            return true;

        // Memoization table: If the current state is already computed then return the computed value 
        if(memory[index] != -1)
            return memory[index];

        // Explore all the possibilities of jumping from the current index 
        for(int jump = 1; (jump <= nums[index] && jump + index < n); ++jump) 
            if(solveWithMemo(memory, nums, n, jump + index)) 
                return true;

        // Stores the value to the memoization table and then return it
        return memory[index] = false;
    }

    // O(N^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int n, int index) {
        // Edge case: If you reached the last index then return true
        if(index == n-1)
            return true;

        // Explore all the possibilities of jumping from the current index 
        for(int jump = 1; (jump <= nums[index] && jump + index < n); ++jump)
            if(solveWithoutMemo(nums, n, jump + index))
                return true;

        // If you're not able to reach the last index then return false
        return false;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to check whether you can reach the last index or not, using 1D tabulation - O(N*N) & O(N)
    bool canJumpToLastIndex(vector<int>& nums) {
        int n = nums.size();

        // 1D table: dp[index] represents whether you can reach the individual index or not
        vector<bool> dp(n, false);

        // Initialize the edge case: If you reached the last index then return true
        dp[n-1] = true;

        // Fill the rest of the table
        for(int index = n-2; (index >= 0 && !dp[0]); --index) {
            for(int jump = 1; (jump <= nums[index] && jump + index < n); ++jump) {
                if(dp[jump + index]) {
                    dp[index] = true;
                    break;
                }
            }
        }

        // Return the result value
        return dp[0];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Greedy
Link  : https://leetcode.com/problems/jump-game/
