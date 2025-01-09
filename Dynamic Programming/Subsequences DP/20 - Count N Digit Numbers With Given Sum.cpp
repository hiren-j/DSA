// Code to find the count of all `n` digit numbers whose sum of digits is `sum`. Leading 0’s are not counted as digits ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;

    // O(9^N) & O(N)
    long solveWithoutMemo(int n, int len, int sum) {
        // Edge case: If you've created a number of length n and its sum of digits is equal to given sum then return 1
        if(len == n)
            return (sum == 0); 
                    
        long count = 0;
        
        // If length is 0 then avoid start from leading 0's
        for(int digit = (len == 0 ? 1 : 0); (digit <= 9 && sum - digit >= 0); ++digit)
            count = (count + solveWithoutMemo(n, len + 1, sum - digit)) % MOD;
         
        return count;
    }
    
    // O(9*N*S) & O(N*S + N)
    long solveWithMemo(vector<vector<long>>& dp, int n, int len, int sum) {
        // Edge case: If you've created a number of length n and its sum of digits is equal to given sum then return 1
        if(len == n)
            return (sum == 0); 
            
        if(dp[len][sum] != -1)
            return dp[len][sum];
            
        long count = 0;
        
        // If length is 0 then avoid start from leading 0's
        for(int digit = (len == 0 ? 1 : 0); (digit <= 9 && sum - digit >= 0); ++digit)
            count = (count + solveWithMemo(dp, n, len + 1, sum - digit)) % MOD;
         
        return dp[len][sum] = count;
    }
    
public:
    // Method to count all n length numbers whose sum of digits equals to sum, using recursion with memoization - O(N*S) & O(N*S) : Where S = sum
    long countWays(int n, int sum) {
        vector<vector<long>> dp(n, vector<long>(sum + 1, -1));
        long count = solveWithMemo(dp, n, 0, sum); 
        return (count == 0) ? -1 : count;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;
    
public:
    // #1 Method to count all n length numbers whose sum of digits equals to sum, using 2D tabulation - O(N*S) & O(N*S)
    long countWays_V1(int n, int sum) {
        vector<vector<long>> dp(n + 1, vector<long>(sum + 1, 0));
        dp[n][0] = 1; // Initialize the edge case
        
        for(int len = n-1; len >= 0; --len) {
            for(int currSum = 0; currSum <= sum; ++currSum) {
                long count = 0;
                for(int digit = (len == 0 ? 1 : 0); (digit <= 9 && currSum - digit >= 0); ++digit) {
                    count = (count + dp[len + 1][currSum - digit]) % MOD;
                }
                dp[len][currSum] = count;
            }
        }

        long count = dp[0][sum]; 
        return (count == 0) ? -1 : count;
    }

    // #2 Method to count all n length numbers whose sum of digits equals to sum, using 1D tabulation - O(N*S) & O(S)
    long countWays_V2(int n, int sum) {
        vector<long> nextRow(sum + 1, 0), idealRow(sum + 1, 0);
        nextRow[0] = 1; // Initialize the edge case
        
        for(int len = n-1; len >= 0; --len) {
            for(int currSum = 0; currSum <= sum; ++currSum) {
                long count = 0;
                for(int digit = (len == 0 ? 1 : 0); (digit <= 9 && currSum - digit >= 0); ++digit) {
                    count = (count + nextRow[currSum - digit]) % MOD;
                }
                idealRow[currSum] = count;
            }
            nextRow = idealRow;
        }
        
        long count = nextRow[sum]; 
        return (count == 0) ? -1 : count;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/count-of-n-digit-numbers-whose-sum-of-digits-equals-to-given-sum0733/1
