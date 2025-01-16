// Code to find the number of possible ways (out of the K^N total ways) to roll the dice, so the sum of the face-up numbers equals the target value ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;

public:
    // Method to find the number of possible ways, using recursion with memoization - O(N*T*K) & O(N*T) : Where T let be the target
    int numRollsToTarget(int n, int k, int target) {
        vector<vector<int>> memory(n + 1, vector<int>(target + 1, -1));
        return solveWithMemo(memory, n, k, target);
    }

private:
    // O(K*N*T) & O(N*T + N)
    int solveWithMemo(vector<vector<int>>& memory, int n, int k, int target) {
        // Edge case: If all the dice are rolled and the target becomes zero then you've one valid way
        if(n == 0) 
            return (target == 0);

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[n][target] != -1)
            return memory[n][target];

        // Stores the result value
        int count = 0;

        // Iterate and if possible then take the face number in the target
        for(int face = 1; (face <= k && face <= target); ++face)
            count = (count + solveWithMemo(memory, n - 1, k, target - face)) % MOD;

        // Store the result value to the memoization table and then return it
        return memory[n][target] = count;
    }

    // O(K^N) & O(N)
    int solveWithoutMemo(int n, int k, int target) {
        // Edge case: If all the dice are rolled and the target becomes zero then you've one valid way
        if(n == 0) 
            return (target == 0);

        // Stores the result value
        int count = 0;

        // Iterate and if possible then take the face number in the target
        for(int face = 1; (face <= k && face <= target); ++face) 
            count = (count + solveWithoutMemo(n - 1, k, target - face)) % MOD;

        // Return the result value
        return count;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;

public:
    // #1 Method to find the number of possible ways, using 2D tabulation - O(N*T*K) & O(N*T) 
    int numRollsToTarget_V1(int n, int k, int target) {
        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));

        // Initialize the edge case: If all the dice are rolled and the target becomes zero then you've one valid way
        dp[0][0] = 1;

        // Fill the rest of the table
        for(int dice = 1; dice <= n; ++dice) {
            for(int currTarget = 0; currTarget <= target; ++currTarget) {
                int count = 0;
                for(int face = 1; (face <= k && face <= currTarget); ++face) {
                    count = (count + dp[dice - 1][currTarget - face]) % MOD;
                }
                dp[dice][currTarget] = count;
            }
        }

        // Return the result value
        return dp[n][target];
    }

    // #2 Method to find the number of possible ways, using 1D tabulation - O(N*T*K) & O(T)
    int numRollsToTarget_V2(int n, int k, int target) {
        // 1D DP tables
        vector<int> prevRow(target + 1, 0), idealRow(target + 1, 0);

        // Initialize the edge case: If all the dice are rolled and the target becomes zero then you've one valid way
        prevRow[0] = 1;

        // Fill the rest of the table
        for(int dice = 1; dice <= n; ++dice) {
            for(int currTarget = 0; currTarget <= target; ++currTarget) {
                int count = 0;
                for(int face = 1; (face <= k && face <= currTarget); ++face) {
                    count = (count + prevRow[currTarget - face]) % MOD;
                }
                idealRow[currTarget] = count;
            }
            prevRow = idealRow;
        }

        // Return the result value
        return prevRow[target];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming
Link  : https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/description/?envType=daily-question&envId=2023-12-26
