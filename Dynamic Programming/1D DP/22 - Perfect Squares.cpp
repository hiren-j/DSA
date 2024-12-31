// Code to find the least number of perfect square numbers that sums to N ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the least number of perfect square numbers that sums to N, using recursion with memoization - O(N*sqrt(N)) & O(N)
    int numSquares(int N) {
        vector<int> memory(N+1, -1);
        return solveWithMemo(N, memory);
    }

private:
    // O(sqrt(N)*N) & O(N+N)
    int solveWithMemo(int N, vector<int>& memory) {
        // Edge case: If N is equal to 0 then its not possible to get any perfect square number
        if(N == 0)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[N] != -1)
            return memory[N];

        // Stores the result value
        int minCount = INT_MAX;

        // Explore all the possibilities which can sum to N and update the result by the minimum value
        for(int J = 1; J*J <= N; ++J) 
            minCount = min(minCount, 1 + solveWithMemo(N - J*J, memory));

        // Store the result value to the memoization table and then return it
        return memory[N] = minCount;
    }

    // O(sqrt(N)^N) & O(N)
    int solveWithoutMemo(int N) {
        // Edge case: If N is equal to 0 then its not possible to get any perfect square number
        if(N == 0)
            return 0;

        // Stores the result value
        int minCount = INT_MAX;

        // Explore all the possibilities which can sum to N and update the result by the minimum value
        for(int J = 1; J*J <= N; ++J) 
            minCount = min(minCount, 1 + solveWithoutMemo(N - J*J));

        // Return the result value
        return minCount;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the least number of perfect square numbers that sums to N, using 1D tabulation - O(N*sqrt(N)) & O(N)
    int numSquares(int N) {
        // 1D table: dp[num] stores the least number of perfect square numbers which can sum to num
        vector<int> dp(N+1, INT_MAX);

        // Initialize the edge case: If N is equal to 0 then its not possible to get any perfect square number
        dp[0] = 0;

        // Fill the rest of the table
        for(int num = 1; num <= N; ++num) {
            int minCount = INT_MAX;
            for(int J = 1; J*J <= num; ++J) {
                minCount = min(minCount, 1 + dp[num - J*J]);
            }
            dp[num] = minCount;
        }
        
        // Return the result value
        return dp[N];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Math | Dynamic Programming
Link  : https://leetcode.com/problems/perfect-squares/description/
