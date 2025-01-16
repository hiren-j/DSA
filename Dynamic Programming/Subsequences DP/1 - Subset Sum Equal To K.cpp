// Code to determine if there is a subset of the given set with sum equal to the given sum or not ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ: As I mentioned earlier, I'll be providing multiple ways of writing the top-down solutions. So, from now on, in this Subsequence DP pattern and the LIS DP pattern, you’ll find different approaches to crafting these solutions. 
                            This will help you figure out multiple ways of writing a top-down solution. Again, I'll be doing it for both the Subsequence and LIS patterns to help you grasp various techniques and perspectives.
                            In this Subsequence pattern, there are a total of 22 questions, and 12 of them contain multiple ways of writing the top-down solution. 
                            If multiple ways are not provided, consider that I tried but couldn’t get them to work through all test cases. 
                            Hope you’re enjoying the series!
*/
  
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// #1 Class to implement the Top-down approach:
class TopDown_V1 {   
public:
    // Method to determine if there exists the mentioned subset, using recursion with memoization - O(N*S) & O(N*S) : Where S let be the sum
    bool isSubsetSum(vector<int>& nums, int sum) {
        int n = nums.size();
        vector<vector<int>> memory(n, vector<int>(sum + 1, -1));
        return solveWithMemo(memory, nums, n, 0, sum);
    }
    
private:
    // O(2*N*S) & O(N*S + N)
    bool solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int n, int index, int sum) {
        // Edge case: If the sum becomes zero then there exists a subset with given sum 
        if(sum == 0)
            return true;

        // Edge case: If all the elements are exhausted then return false
        if(index == n)
            return false;
            
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][sum] != -1)
            return memory[index][sum];
        
        // There are always two possibilties to perform at each index
        bool currSkip = solveWithMemo(memory, nums, n, index + 1, sum); // Is to skip the index value
        bool currTake = false;                                          // Is to take the index value

        // If possible then take the index value
        if(nums[index] <= sum)
            currTake = solveWithMemo(memory, nums, n, index + 1, sum - nums[index]);
        
        // Store the result value to the memoization table and then return it
        return memory[index][sum] = currTake || currSkip;
    }

    // O(2^N) & O(N)
    bool solveWithoutMemo(vector<int>& nums, int n, int index, int sum) {
        // Edge case: If the sum becomes zero then there exists a subset with given sum 
        if(sum == 0)
            return true;

        // Edge case: If all the elements are exhausted then return false
        if(index == n)
            return false;
            
        // There are always two possibilties to perform at each index
        bool currSkip = solveWithoutMemo(nums, n, index + 1, sum); // Is to skip the index value
        bool currTake = false;                                     // Is to take the index value

        // If possible then take the index value
        if(nums[index] <= sum)
            currTake = solveWithoutMemo(nums, n, index + 1, sum - nums[index]);

        // Return the presence information of the subset 
        return currTake || currSkip;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// #2 Class to implement the Top-down approach:
class TopDown_V2 {
public:
    // Method to determine if there exists the mentioned subset, using recursion with memoization - O(N*N*S) & O(N*S)
    bool isSubsetSum(vector<int>& nums, int sum) {
        int n = nums.size();
        vector<vector<int>> memory(n + 1, vector<int>(sum + 1, -1));
        return solveWithMemo(memory, nums, n, 0, sum);
    }

private:
    // O(N*N*S) & O(N*S + N)
    bool solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int n, int startIndex, int sum) {
        // Edge case: If the sum becomes zero then there exists a subset with given sum 
        if(sum == 0)
            return true;
        
        // Edge case: If all the elements are exhausted then return false
        if(startIndex == n)
            return false;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex][sum] != -1)
            return memory[startIndex][sum];
            
        // If the subset equal to given sum doesn't exist, then if possible, then take the index value
        for(int index = startIndex; index < n; ++index)
            if(nums[index] <= sum && solveWithMemo(memory, nums, n, index + 1, sum - nums[index])) 
                return memory[startIndex][sum] = true;
        
        // Store the result value to the memoization table and then return it
        return memory[startIndex][sum] = false;
    }

    // O(N^N) & O(N)
    bool solveWithoutMemo(vector<int>& nums, int n, int startIndex, int sum) {
        // Edge case: If the sum becomes zero, then there exists a subset with given sum 
        if(sum == 0)
            return true;
                        
        // If the subset equal to given sum doesn't exist, then if possible, then take the index value
        for(int index = startIndex; index < n; ++index) 
            if(nums[index] <= sum && solveWithoutMemo(nums, n, index + 1, sum - nums[index])) 
                return true;

        // If reached here then return false 
        return false;
    }
};
// Note: This solution (TopDown_V2) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V2)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Bottom-up approach:
class BottomUp {   
public:
    // #1 Method to determine if there exists the mentioned subset, using 2D tabulation - O(N*S) & O(N*S)
    bool isSubsetSum_V1(vector<int>& nums, int sum) {
        int n = nums.size();

        // 2D DP table
        vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));

        // Initialize the first edge case: If the sum becomes zero then there exists a subset with given sum 
        for(int index = 0; index <= n; ++index)
            dp[index][0] = true;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(int currSum = 1; currSum <= sum; ++currSum) {
                bool currSkip = dp[index + 1][currSum]; 
                bool currTake = false;                                          
                if(nums[index] <= currSum) {
                    currTake = dp[index + 1][currSum - nums[index]];
                }
                dp[index][currSum] = currTake || currSkip;
            }
        }

        // Return the result value
        return dp[0][sum];
    }

    // #2 Method to determine if there exists the mentioned subset, using 1D tabulation - O(N*S) & O(S)
    bool isSubsetSum_V2(vector<int>& nums, int sum) {
        int n = nums.size();

        // 1D DP tables
        vector<bool> nextRow(sum + 1, false), idealRow(sum + 1, false);
        nextRow[0] = true;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            idealRow[0] = true;
            for(int currSum = 1; currSum <= sum; ++currSum) {
                bool currSkip = nextRow[currSum]; 
                bool currTake = false;                                          
                if(nums[index] <= currSum) {
                    currTake = nextRow[currSum - nums[index]];
                }
                idealRow[currSum] = currTake || currSkip;
            }
            nextRow = idealRow;
        }

        // Return the result value
        return nextRow[sum];
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://www.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1
        https://www.codingninjas.com/studio/problems/subset-sum-equal-to-k_1550954?leftPanelTabValue=PROBLEM
