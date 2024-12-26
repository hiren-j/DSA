// Code to find the number of different expressions that you can build using specified way such that they evaluates to target ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DON'T IGNORE MUST READ (REGARDING MY REASONING BEHIND THE LINE): 
    int maxSpace = 40001
    int offset   = 20000

Constraints:
1 <= nums.length <= 20
0 <= nums[i] <= 1000
-1000 <= target <= 1000

As mentioned in the worst case we could have 20 values and the maximum value could be 1000, now based on this:
    = nums.length * nums[i]
    = 20 * 1000
    = 20000
    => Let say this value 20000 is called offset.

-> Worst case of positive sum: 
    If we add 1000 for 20 times the maximum possible sum will be 20000, hence the worst case for positive sum could be 20000.
-> Worst case of negative sum: 
    If we subtract 1000 for 20 times the maximum possible negative sum will be -20000, hence the worst case for negative sum could be -20000.

-> As I said (offset = 20000), So I could say:
    -> In summary the worst case for negative sum is: -offset
    -> In summary the worst case for positive sum is:  offset 

Now we have to fit both negative and positive sum into array, array indexing starts from 0.

-> Intuition to store negative sums: 
    -> We will use index 0 to store the result for -20000.              To get index 0 do this -> (-20000 + offset) 
    -> We will use index 1 to store the result for -19999.              To get index 1 do this -> (-19999 + offset) 
    -> We will use index 2 to store the result for -19998.              To get index 2 do this -> (-19998 + offset) 
    -> We will use index i to store the result for any negative target. To get index i do this -> (target + offset) 

-> Intuition to store positive sums: 
    -> We will use index 20000 to store the result for 0.                         To get index 20000 do this -> (0 + offset) 
    -> We will use index 20001 to store the result for 1.                         To get index 20001 do this -> (1 + offset) 
    -> We will use index 20002 to store the result for 2.                         To get index 20002 do this -> (2 + offset) 
    -> We will use index (i + 20000) to store the result for any positive target. To get index (i + offset) do this -> (target + offset) 

-> As you could see the common line in both the intuitions is: (target + offset)
-> So We will be using (target + offset) for fetching array indeces.

-> Now as I said the worst positive sum is 20000,
   then for it the index will be = 20000 + offset
                                 = 20000 + 20000
                                 = 40000   

-> So the last index will be 40000, to ensure this index into an array the size must be 40001.
-> So size for array should be 40001.
-> Let say it as the maxSpace = 40001.

-> This approach ensures that the array has indeces for both negative and positive sum, including the value of `target` itself. This way, you can use an array without dealing with negative indices.
  
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;
    int maxSpace = 40001;
    int offset   = 20000;

    // O(2^n) & O(n)
    int solveWithoutMemo(vector<int>& nums, int index, int target) {
        // Edge case: If all the values are picked and sum of all values is equal to target then you have 1 valid way
        if(index == n)
            return target == 0; 
        
        // There are always two possibilities to perform at each value
        int add = solveWithoutMemo(nums, index + 1, target + nums[index]); // Is to add it
        int sub = solveWithoutMemo(nums, index + 1, target - nums[index]); // Is to subtact it

        // Return the result value
        return add + sub;    
    }

    // O(2*n*maxSpace) & O(n*maxSpace + n)
    int solveWithMemo(vector<vector<int>>& dp, vector<int>& nums, int index, int target) {
        // Edge case: If all the values are picked and sum of all values is equal to target then you have 1 valid way
        if(index == n)
            return target == 0; 

        // Memoization table: If the current state is already computed then return the computed value
        if(dp[index][target + offset] != -1)
            return dp[index][target + offset];
        
        // There are always two possibilities to perform at each value
        int add = solveWithMemo(dp, nums, index + 1, target + nums[index]); // Is to add it
        int sub = solveWithMemo(dp, nums, index + 1, target - nums[index]); // Is to subtact it

        // Store the result value to the memoization table and then return it
        return dp[index][target + offset] = add + sub;    
    }

public:
    int findTargetSumWays(vector<int>& nums, int target) {
        n = nums.size();
        vector<vector<int>> dp(n, vector<int>(maxSpace, -1));
        return solveWithMemo(dp, nums, 0, target);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(n * maxSpace) & O(n * maxSpace)
    int findTargetSumWays_V1(vector<int>& nums, int target) {
        int n = nums.size();
        int maxSpace = 40001;
        int offset   = 20000;

        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(maxSpace, 0));

        // Initialize the edge case
        dp[n][offset] = 1; 

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(int sum = -offset; sum <= offset; ++sum) {
                int newIndex1 = sum + nums[index] + offset;
                int newIndex2 = sum - nums[index] + offset;
                int add = (newIndex1 >= 0 && newIndex1 < maxSpace) ? dp[index + 1][newIndex1] : 0;
                int sub = (newIndex2 >= 0 && newIndex2 < maxSpace) ? dp[index + 1][newIndex2] : 0;
                dp[index][sum + offset] = add + sub; 
            }
        }

        // Return the result value
        return dp[0][target + offset];
    }

    // O(n * maxSpace) & O(maxSpace)
    int findTargetSumWays_V2(vector<int>& nums, int target) {
        int n = nums.size();
        int maxSpace = 40001;
        int offset   = 20000;

        // 1D DP tables
        vector<int> nextRow(maxSpace, 0), currRow(maxSpace, 0);

        // Initialize the edge case 
        nextRow[offset] = 1; 

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(int sum = -offset; sum <= offset; ++sum) {
                int newIndex1 = sum + nums[index] + offset;
                int newIndex2 = sum - nums[index] + offset;
                int add = (newIndex1 >= 0 && newIndex1 < maxSpace) ? nextRow[newIndex1] : 0;
                int sub = (newIndex2 >= 0 && newIndex2 < maxSpace) ? nextRow[newIndex2] : 0;
                currRow[sum + offset] = add + sub; 
            }
            nextRow = currRow; 
        }

        // Return the result value
        return nextRow[target + offset];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Backtracking 
Link  : https://leetcode.com/problems/target-sum/description/?envType=list&envId=50vif4uc
