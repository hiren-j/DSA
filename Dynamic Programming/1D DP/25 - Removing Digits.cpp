// Code to count the total steps required to make the given number equal to 0. On each step, you may subtract one of the digits from the number ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to count the total steps required to reduce n to 0, using recursion with memoization - O(NLogN) & O(N)
    int minStepsToMakeZero(int n) {
        vector<int> dp(n + 1, -1);
        return solveWithMemo(dp, n);
    }

private:
    // O(LogN*N) & O(N+N)
    int solveWithMemo(vector<int>& dp, int n) {
        // Edge case: If n is 0, then no steps are required to make n equal to 0
        if(n == 0)
            return 0;

        // Edge case: If n is negative, then it is not possible to make n equal to 0
        if(n < 0)
            return INT_MAX;

        // Memoization table: If the current state is already computed then return the computed value
        if(dp[n] != -1)
            return dp[n];

        int curr = n, minSteps = INT_MAX;

        // Subtract the digits one by one and find the minimum steps to make number equal to 0 and then update the result by the minimum value
        while(curr) {
            int digit = curr % 10;
            curr /= 10;
            if(digit == 0) continue;
            int nextSteps = solveWithMemo(dp, n - digit);
            if(nextSteps != INT_MAX) minSteps = min(minSteps, 1 + nextSteps);
        }

        // Store the result value to the memoization table and then return it
        return dp[n] = minSteps; 
    }

    // O(LogN^N) & O(N)
    int solveWithoutMemo(int n) {
        // Edge case: If n is 0, then no steps are required to make n equal to 0
        if(n == 0)
            return 0;

        // Edge case: If n is negative, then it is not possible to make n equal to 0
        if(n < 0)
            return INT_MAX;

        int curr = n, minSteps = INT_MAX;

        // Subtract the digits one by one and find the minimum steps to make number equal to 0 and then update the result by the minimum value
        while(curr) {
            int digit = curr % 10;
            curr /= 10;
            if(digit == 0) continue;
            int nextSteps = solveWithoutMemo(n - digit);
            if(nextSteps != INT_MAX) minSteps = min(minSteps, 1 + nextSteps);
        }

        return minSteps; 
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to count the total steps required to reduce n to 0, using 1D tabulation - O(NLogN) & O(N)
    int minStepsToMakeZero(int n) {
        // 1D DP table: dp[i] represents the total steps required to reduce i to 0
        vector<int> dp(n + 1, INT_MAX);

        // Initialize the edge case
        dp[0] = 0;

        // Fill the rest of the table
        for(int number = 1; number <= n; ++number) {
            int curr = number, minSteps = INT_MAX;

            while(curr) {
                int digit = curr % 10;
                curr /= 10;
                if(digit == 0) continue;
                int nextSteps = (number - digit >= 0) ? dp[number - digit] : INT_MAX;
                if(nextSteps != INT_MAX) minSteps = min(minSteps, 1 + nextSteps);
            }

            dp[number] = minSteps; 
        }

        // Return the result value
        return dp[n];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Math | Dynamic Programming
Link  : https://cses.fi/problemset/task/1637
