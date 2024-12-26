// Code to find the number of different expressions that you can build using specified way such that they evaluates to target ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
public:
    // Method to find the total number of different expressions that evaluates to target, using recursion with memoization - O(N*T) & O(N*T) : Where T let be the target
    int findTargetSumWays(vector<int>& nums, int target) {
        unordered_map<string, int> memory;
        return solveWithMemo(memory, nums, nums.size(), target, 0, 0);
    }

private:
    // O(2*N*T) & O(N*T + N)
    int solveWithMemo(unordered_map<string, int>& memory, vector<int>& nums, int n, int target, int index, int currSum) {
        // Edge case: If all the elements are exhausted and if the sum value is equal to target then you've 1 valid expression
        if(index == n)
            return currSum == target;

        string key = to_string(index) + "_" + to_string(currSum);

        // Memoization table: If the current state is already computed then return the computed value
        if(memory.count(key))
            return memory[key];

        // There are always two possibilities to perform at each index
        int addNum = solveWithMemo(memory, nums, n, target, index + 1, currSum + nums[index]); // Is to add the index value to the sum 
        int subNum = solveWithMemo(memory, nums, n, target, index + 1, currSum - nums[index]); // Is to subtract the index value from the sum 

        // Store the result value to the memoization table and then return it
        return memory[key] = addNum + subNum;
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int n, int target, int index, int currSum) {
        // Edge case: If all the elements are exhausted and if the sum value is equal to target then you've 1 valid expression
        if(index == n)
            return currSum == target;

        // There are always two possibilities to perform at each index
        int addNum = solveWithoutMemo(nums, n, target, index + 1, currSum + nums[index]); // Is to add the index value to the sum 
        int subNum = solveWithoutMemo(nums, n, target, index + 1, currSum - nums[index]); // Is to subtract the index value from the sum 

        // Return the result value
        return addNum + subNum;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
class TopDown_V2 {
public:
    // Method to find the total number of different expressions that evaluates to target, using recursion with memoization - O(N*T) & O(N*T)
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size(), totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the difference becomes negative or odd then you can't have valid partitions
        if(totalSum - target < 0 || (totalSum - target) % 2 != 0)
            return false;

        // If the difference is an even value then you can have valid partitions 
        target = (totalSum - target) / 2;

        // 2D memoization table
        vector<vector<int>> memory(n, vector<int>(target + 1, -1));

        // Count and return the total number of subsets whose sum is equal to the target
        return solveWithMemo(memory, nums, n, n - 1, target);
    }
    
private:
    // O(2*N*T) & O(N*T + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int n, int index, int target) {
        // Edge case: If you reached the 0th index then compute the count of all the subsets according to their existence
        if(index == 0) {
            if(target == 0) 
                return (nums[index] == 0) ? 2 : 1;
            else
                return (nums[index] == target) ? 1 : 0;
        }
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][target] != -1)
            return memory[index][target];
            
        // There are always two possibilties to perform at each index
        int currSkip = solveWithMemo(memory, nums, n, index - 1, target); // Is to skip the index value
        int currTake = 0;                                                 // Is to take the index value
        
        // If possible then take the index value
        if(nums[index] <= target)
            currTake = solveWithMemo(memory, nums, n, index - 1, target - nums[index]);

        // Store the result value to the memoization table and then return it
        return memory[index][target] = currTake + currSkip;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the total number of different expressions that evaluates to target, using 2D tabulation - O(N*T) & O(N*T)
    int findTargetSumWays_V1(vector<int>& nums, int target) {
        int n = nums.size(), totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the difference becomes negative or odd then you can't have valid partitions
        if(totalSum - target < 0 || (totalSum - target) % 2 != 0)
            return false;

        // If the difference is an even value then you can have valid partitions 
        target = (totalSum - target) / 2;
        
        // 2D DP table
        vector<vector<int>> dp(n, vector<int>(target + 1, 0));   

        // Initialize the edge case: If you reached the 0th index then compute the count of all the subsets according to their existence
        dp[0][0] = 1;
        if(nums[0] == 0) dp[0][0] = 2;
        else if(nums[0] <= target) dp[0][nums[0]] = 1;

        // Fill the rest of the table
        for(int index = 1; index < n; ++index) {
            for(int currTarget = 0; currTarget <= target; ++currTarget) {
                int currSkip = dp[index - 1][currTarget]; 
                int currTake = 0;                                                       
                if(nums[index] <= currTarget) {
                    currTake = dp[index - 1][currTarget - nums[index]];
                }
                dp[index][currTarget] = currTake + currSkip;
            }
        }

        // Return the result value
        return dp[n - 1][target];
    }

    // #2 Method to find the total number of different expressions that evaluates to target, using 1D tabulation - O(N*T) & O(T)
    int findTargetSumWays_V2(vector<int>& nums, int target) {
        int n = nums.size(), totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the difference becomes negative or odd then you can't have valid partitions
        if(totalSum - target < 0 || (totalSum - target) % 2 != 0)
            return false;

        // If the difference is an even value then you can have valid partitions 
        target = (totalSum - target) / 2;

        // 1D DP tables
        vector<int> prevRow(target + 1, 0), idealRow(target + 1, 0);

        // Initialize the edge case: If you reached the 0th index then compute the count of all the subsets according to their existence
        prevRow[0] = 1;
        if(nums[0] == 0) prevRow[0] = 2;
        else if(nums[0] <= target) prevRow[nums[0]] = 1;

        // Fill the rest of the table
        for(int index = 1; index < n; ++index) {
            for(int currTarget = 0; currTarget <= target; ++currTarget) {
                int currSkip = prevRow[currTarget]; 
                int currTake = 0;                                                       
                if(nums[index] <= currTarget) {
                    currTake = prevRow[currTarget - nums[index]];
                }
                idealRow[currTarget] = currTake + currSkip;
            }
            prevRow = idealRow;
        }

        // Return the result value
        return prevRow[target];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Backtracking 
Link  : https://leetcode.com/problems/target-sum/description/?envType=list&envId=50vif4uc
