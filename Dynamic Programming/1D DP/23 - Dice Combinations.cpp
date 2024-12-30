// Code to count the number of ways to construct sum n by throwing a dice one or more times. Each throw produces an outcome between 1 and 6 ~ coded by Hiren 

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to count the total number of ways to construct sum n, using recursion with memoization - O(N) & O(N)
    int countWays(int n) {
        vector<int> memory(n + 1, -1);
        return solveWithMemo(memory, n);
    }

private:
    // O(6*N) & O(N+N)
    int solveWithMemo(vector<int>& memory, int n) {
        // Edge case: If n is 0, then there is only one way to construct n
        if(n == 0)
            return 1;

        // Memoization table: If the current state is already copmuted then return the computed value
        if(memory[n] != -1)
            return memory[n];

        int count = 0;

        // Explore all possible outcomes and count the number of ways to construct n
        for(int outcome = 1; (outcome <= 6 && n - outcome >= 0); ++outcome)
            count = (count + solveWithMemo(memory, n - outcome)) % MOD;

        // Store the result value to the memoization table and then return it
        return memory[n] = count % MOD;
    }

    // O(6^N) & O(N)
    int solveWithoutMemo(int n) {
        // Edge case: If n is 0, then there is only one way to construct n
        if(n == 0)
            return 1;

        int count = 0;

        // Explore all possible outcomes and count the number of ways to construct n
        for(int outcome = 1; (outcome <= 6 && n - outcome >= 0); ++outcome)
            count = (count + solveWithoutMemo(n - outcome)) % MOD;

        return count % MOD;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to count the total number of ways to construct sum n, using 1D tabulation - O(N) & O(N)
    int countWays(int n) {
        // 1D DP table: dp[i] represents the number of ways to construct sum i
        vector<int> dp(n + 1, 0);

        // Initialize the edge case
        dp[0] = 1;

        // Fill the rest of the table
        for(int step = 1; step <= n; ++step) {
            int count = 0;
            for(int outcome = 1; (outcome <= 6 && step - outcome >= 0); ++outcome) {
                count = (count + dp[step - outcome]) % MOD;
            }
            dp[step] = count % MOD;
        }

        // Return the result value
        return dp[n];
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Combinatorics
Link  : https://cses.fi/problemset/task/1633
