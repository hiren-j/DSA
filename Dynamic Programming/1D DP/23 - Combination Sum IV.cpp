// Code to find the number of possible combinations that add up to target. Note that the array values are distinct ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown_V1 {
public:
    // Method to find the number of possible combinations that add up to target, using recursion with memoization - O(N*T) & O(T) : Where T let be the target
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> memory(target + 1, -1);
        return solveWithMemo(memory, nums, nums.size(), target);
    }

private:
    // O(N*T) & O(T+T)
    int solveWithMemo(vector<int>& memory, vector<int>& nums, int n, int target) {
        // Edge case: If the target becomes zero then you've got one valid way
        if(target == 0)
            return 1;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[target] != -1)
            return memory[target];

        // Stores the result value
        int count = 0;

        // Try each number of array to find the number of possible combinations that add up to target
        for(int index = 0; index < n; ++index) 
            if(nums[index] <= target) 
                count += solveWithMemo(memory, nums, n, target - nums[index]);

        // Store the result value to the memoization table and then return it
        return memory[target] = count;
    }

    // O(N^T) & O(T)
    int solveWithoutMemo(vector<int>& nums, int n, int target) {
        // If the target becomes zero then you've got one valid way
        if(target == 0)
            return 1;

        // Stores the result value
        int count = 0;

        // Try each number of array to find the number of possible combinations that add up to target
        for(int index = 0; index < n; ++index) 
            if(nums[index] <= target) 
                count += solveWithoutMemo(nums, n, target - nums[index]);

        // Return the result value
        return count;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown_V2 {
public:
    // Method to find the number of possible combinations that add up to target, using recursion with memoization - O(N*T) & O(T) 
    int combinationSum4(vector<int>& nums, int target) {
        sort(begin(nums), end(nums));
        vector<int> memory(target + 1, -1);
        return solveWithMemo(memory, nums, nums.size(), target);
    }

private:
    // O(N*T) & O(T+T)
    int solveWithMemo(vector<int>& memory, vector<int>& nums, int n, int target) {
        // Edge case: If the target becomes zero then you've got one valid way
        if(target == 0)
            return 1;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[target] != -1)
            return memory[target];

        // Stores the result value
        int count = 0;

        // Try each number of array to find the number of possible combinations that add up to target
        for(int index = 0; (index < n && nums[index] <= target); ++index) 
            count += solveWithMemo(memory, nums, n, target - nums[index]);

        // Store the result value to the memoization table and then return it
        return memory[target] = count;
    }

    // O(N^T) & O(T)
    int solveWithoutMemo(vector<int>& nums, int n, int target) {
        // Edge case: If the target becomes zero then you've got one valid way
        if(target == 0)
            return 1;

        // Stores the result value
        int count = 0;

        // Try each number of array to find the number of possible combinations that add up to target
        for(int index = 0; (index < n && nums[index] <= target); ++index)
            count += solveWithoutMemo(nums, n, target - nums[index]);

        // Return the result value
        return count;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the number of possible combinations that add up to target, using 1D tabulation - O(N*T) & O(T)
    int combinationSum4_V1(vector<int>& nums, int target) {
        int n = nums.size();

        // 1D table: dp[target] represents the number of possible combinations that add up to the target
        vector<unsigned int> dp(target + 1, 0);

        // Initialize the edge case: If the target becomes zero then you've got one valid way
        dp[0] = 1;

        // Fill the rest of the table
        for(int currTarget = 1; currTarget <= target; ++currTarget) {
            int count = 0;
            for(int index = 0; index < n; ++index) {
                if(nums[index] <= currTarget) {
                    count += dp[currTarget - nums[index]];
                }
            }
            dp[currTarget] = count;
        }

        // Return the result value
        return dp[target];
    }

    // #2 Method to find the number of possible combinations that add up to target, using 1D tabulation - O(N*T) & O(T)
    int combinationSum4_V2(vector<int>& nums, int target) {
        int n = nums.size();
        sort(begin(nums), end(nums));

        // 1D table: dp[target] represents the number of possible combinations that add up to the target
        vector<unsigned int> dp(target + 1, 0);

        // Initialize the edge case: If the target becomes zero then you've got one valid way
        dp[0] = 1;

        // Fill the rest of the table
        for(int currTarget = 1; currTarget <= target; ++currTarget) {
            int count = 0;
            for(int index = 0; (index < n && nums[index] <= currTarget); ++index) {
                count += dp[currTarget - nums[index]];
            }
            dp[currTarget] = count;
        }

        // Return the result value
        return dp[target];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://leetcode.com/problems/combination-sum-iv/
        https://cses.fi/problemset/task/1635/
