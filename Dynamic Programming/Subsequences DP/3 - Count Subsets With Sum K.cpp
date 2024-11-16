// Code to find the count of all the subsets of the given array with a sum equal to the given sum ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;

public:
    // Method to count all the subsets whose sum equals to the given sum, using recursion with memoization - O(N*S) & O(N*S) : Where S let be the sum 
    int countSubsetEqualsSum(vector<int>& nums, int sum) {
        int n = nums.size();
        vector<vector<int>> memory(n, vector<int>(sum + 1, -1));
        return solveWithMemo(memory, nums, n, n - 1, sum);
    }

private:
    // O(2*N*S) & O(N*S + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int n, int index, int sum) {
        // Edge case: If you reached the 0th index then compute the count of all the subsets according to their existence
        if(index == 0) {
            if(sum == 0) 
                return (nums[index] == 0) ? 2 : 1;
            else
                return (nums[index] == sum) ? 1 : 0;
        }
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][sum] != -1)
            return memory[index][sum];
            
        // There are always two possibilties to perform at each index
        int currSkip = solveWithMemo(memory, nums, n, index - 1, sum) % MOD; // Is to skip the index value
        int currTake = 0;                                                    // Is to take the index value
        
        // If possible then take the index value
        if(nums[index] <= sum)
            currTake = solveWithMemo(memory, nums, n, index - 1, sum - nums[index]) % MOD;

        // Store the result value to the memoization table and then return it
        return memory[index][sum] = (currTake + currSkip) % MOD;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;

public:
    // #1 Method to count all the subsets whose sum equals to the given sum, using 2D tabulation - O(N*S) & O(N*S)
    int countSubsetEqualsSum_V1(vector<int>& nums, int sum) {
        int n = nums.size();
        
        // 2D DP table
        vector<vector<int>> dp(n, vector<int>(sum + 1, 0));   

        // Initialize the edge case: If you reached the 0th index then compute the count of all the subsets according to their existence
        dp[0][0] = 1;

        if(nums[0] == 0) 
            dp[0][0] = 2;

        else if(nums[0] <= sum) 
            dp[0][nums[0]] = 1;

        // Fill the rest of the table
        for(int index = 1; index < n; ++index) {
            for(int currSum = 0; currSum <= sum; ++currSum) {
                int currSkip = dp[index - 1][currSum] % MOD; 
                int currTake = 0;                                                       
                if(nums[index] <= currSum) {
                    currTake = dp[index - 1][currSum - nums[index]] % MOD;
                }
                dp[index][currSum] = (currTake + currSkip) % MOD;
            }
        }

        // Return the result value
        return dp[n - 1][sum];
    }

    // #2 Method to count all the subsets whose sum equals to the given sum, using 1D tabulation - O(N*S) & O(S)
    int countSubsetEqualsSum_V2(vector<int>& nums, int sum) {
        int n = nums.size();

        // 1D DP tables
        vector<int> prevRow(sum + 1, 0), idealRow(sum + 1, 0);

        // Initialize the edge case: If you reached the 0th index then compute the count of all the subsets according to their existence
        prevRow[0] = 1;

        if(nums[0] == 0) 
            prevRow[0] = 2;

        else if(nums[0] <= sum) 
            prevRow[nums[0]] = 1;

        // Fill the rest of the table
        for(int index = 1; index < n; ++index) {
            for(int currSum = 0; currSum <= sum; ++currSum) {
                int currSkip = prevRow[currSum] % MOD; 
                int currTake = 0;                                                       
                if(nums[index] <= currSum) {
                    currTake = prevRow[currSum - nums[index]] % MOD;
                }
                idealRow[currSum] = (currTake + currSkip) % MOD;
            }
            prevRow = idealRow;
        }

        // Return the result value
        return prevRow[sum];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/perfect-sum-problem5633/1
