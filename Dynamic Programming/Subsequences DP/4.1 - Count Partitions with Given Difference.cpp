// Code to count the total number of partitions in which S1 is greater than or equal to S2 and the difference between S1 and S2 is equal to D ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
class TopDown {
    #define MOD 1000000007

public:
    // Method to count the total number of such partitions, using recursion with memoization - O(N*T) & O(N*T) : Where T let be the target
    int countPartitions(int N, int D, vector<int>& nums) {
        int totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the difference becomes negative or odd then you can't have valid partitions
        if(totalSum - D < 0 || (totalSum - D) % 2 != 0)
            return false;

        // If the difference is an even value then you can have valid partitions 
        int target = (totalSum - D) / 2;

        // 2D memoization table
        vector<vector<int>> memory(N, vector<int>(target + 1, -1));

        // Count and return the total number of subsets whose sum is equal to the target
        return solveWithMemo(memory, nums, N, N - 1, target);
    }
    
private:
    // O(2*N*T) & O(N*T + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int N, int index, int target) {
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
        int currSkip = solveWithMemo(memory, nums, N, index - 1, target) % MOD; // Is to skip the index value
        int currTake = 0;                                                       // Is to take the index value
        
        // If possible then take the index value
        if(nums[index] <= target)
            currTake = solveWithMemo(memory, nums, N, index - 1, target - nums[index]) % MOD;

        // Store the result value to the memoization table and then return it
        return memory[index][target] = (currTake + currSkip) % MOD;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    #define MOD 1000000007

public:
    // #1 Method to count the total number of such partitions, using 2D tabulation - O(N*T) & O(N*T)
    int countPartitions_V1(int N, int D, vector<int>& nums) {
        int totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the difference becomes negative or odd then you can't have valid partitions
        if(totalSum - D < 0 || (totalSum - D) % 2 != 0)
            return false;
            
        // If the difference is an even value then you can have valid partitions 
        int target = (totalSum - D) / 2;

        // 2D DP table
        vector<vector<int>> dp(N, vector<int>(target + 1, 0));   

        // Initialize the edge case: If you reached the 0th index then compute the count of all the subsets according to their existence
        dp[0][0] = 1;
        if(nums[0] == 0) dp[0][0] = 2;
        else if(nums[0] <= target) dp[0][nums[0]] = 1;

        // Fill the rest of the table
        for(int index = 1; index < N; ++index) {
            for(int currTarget = 0; currTarget <= target; ++currTarget) {
                int currSkip = dp[index - 1][currTarget] % MOD; 
                int currTake = 0;                                                       
                if(nums[index] <= currTarget) {
                    currTake = dp[index - 1][currTarget - nums[index]] % MOD;
                }
                dp[index][currTarget] = (currTake + currSkip) % MOD;
            }
        }

        // Return the result value
        return dp[N - 1][target];
    }

    // #2 Method to count the total number of such partitions, using 1D tabulation - O(N*T) & O(T)
    int countPartitions_V2(int N, int D, vector<int>& nums) {
        int totalSum = accumulate(begin(nums), end(nums), 0);
        
        // Edge case: If the difference becomes negative or odd then you can't have valid partitions
        if(totalSum - D < 0 || (totalSum - D) % 2 != 0)
            return false;
            
        // If the difference is an even value then you can have valid partitions 
        int target = (totalSum - D) / 2;

        // 1D DP tables
        vector<int> prevRow(target + 1, 0), idealRow(target + 1, 0);

        // Initialize the edge case: If you reached the 0th index then compute the count of all the subsets according to their existence
        prevRow[0] = 1;
        if(nums[0] == 0) prevRow[0] = 2;
        else if(nums[0] <= target) prevRow[nums[0]] = 1;

        // Fill the rest of the table
        for(int index = 1; index < N; ++index) {
            for(int currTarget = 0; currTarget <= target; ++currTarget) {
                int currSkip = prevRow[currTarget] % MOD; 
                int currTake = 0;                                                       
                if(nums[index] <= currTarget) {
                    currTake = prevRow[currTarget - nums[index]] % MOD;
                }
                idealRow[currTarget] = (currTake + currSkip) % MOD;
            }
            prevRow = idealRow;
        }

        // Return the result value
        return prevRow[target];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/partitions-with-given-difference/1
