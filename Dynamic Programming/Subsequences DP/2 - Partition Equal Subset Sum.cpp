// Code to determine if you can partition the array into two subsets such that the sum of the elements in both the subsets is equal ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
public: 
    // Method to determine if you can partition the array in the specified way, using recursion with memoization - O(N*S) & O(N*S) : Where S let be the sum
    bool canPartition(vector<int>& nums) {
        int n = nums.size(), totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the total sum of the array is odd, then you can't partition the array into two subsets
        if(totalSum % 2 != 0)
            return false;
        
        // Partitioning an even sum into two parts is always equal to each other. So, you can easily figure out there exists two subsets with equal sum or not, if you check for the one subset and it exists then the another subset will absolutely exist it's because there sum are always equal
        int sum = totalSum / 2;
        
        // 2D memoization table
        vector<vector<int>> memory(n, vector<int>(sum + 1, -1));
        
        // Check for the presence of one subset and if it exists then return true, else false
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
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
public: 
    // Method to determine if you can partition the array in the specified way, using recursion with memoization - O(N*N*S) & O(N*S)
    bool canPartition(vector<int>& nums) {
        int n = nums.size(), totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the total sum of the array is odd, then you can't partition the array into two subsets
        if(totalSum % 2 != 0)
            return false;
        
        // Partitioning an even sum into two parts is always equal to each other. So, you can easily figure out there exists two subsets with equal sum or not, if you check for the one subset and it exists then the another subset will absolutely exist it's because there sum are always equal
        int sum = totalSum / 2;
        
        // 2D memoization table
        vector<vector<int>> memory(n, vector<int>(sum + 1, -1));
        
        // Check for the presence of one subset and if it exists then return true, else false
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
};
// Note: This solution (TopDown_V2) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V2)

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp {
public: 
    // #1 Method to determine if you can partition the array in the specified way, using 2D tabulation - O(N*S) & O(N*S)
    bool canPartition_V1(vector<int>& nums) {
        int n = nums.size(), totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the total sum of the array is odd, then you can't partition the array into two subsets
        if(totalSum % 2 != 0)
            return false;
        
        // Partitioning an even sum into two parts is always equal to each other. So, you can easily figure out there exists two subsets with equal sum or not, if you check for the one subset and it exists then the another subset will absolutely exist it's because there sum are always equal
        int sum = totalSum / 2;

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

    // #2 Method to determine if you can partition the array in the specified way, using 1D tabulation - O(N*S) & O(S)
    bool canPartition_V2(vector<int>& nums) {
        int n = nums.size(), totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the total sum of the array is odd, then you can't partition the array into two subsets
        if(totalSum % 2 != 0)
            return false;
        
        // Partitioning an even sum into two parts is always equal to each other. So, you can easily figure out there exists two subsets with equal sum or not, if you check for the one subset and it exists then the another subset will absolutely exist it's because there sum are always equal
        int sum = totalSum / 2;

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

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://leetcode.com/problems/partition-equal-subset-sum/description/
        https://www.geeksforgeeks.org/problems/subset-sum-problem2014/1
