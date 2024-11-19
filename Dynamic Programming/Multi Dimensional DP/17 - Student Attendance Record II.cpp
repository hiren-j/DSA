// Code to find the number of possible attendance records of length N that make a student eligible for an attendance award ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;

public:
    // Method to find the total number of specified attendance records of length N, using recursion with memoization - O(N) & O(N)
    int checkRecord(int N) {
        vector<vector<vector<int>>> memory(N + 1, vector<vector<int>>(2, vector<int>(3, -1)));
        return solveWithMemo(memory, N, 0, 0);
    }

private:
    // O(3*N*2*3) & O(N*2*3 + N)
    int solveWithMemo(vector<vector<vector<int>>>& memory, int N, int absences, int consecutiveLate) {
        // Edge case: If the student goes absent for 2 days or goes late for consecutively 3 days then there's no valid way
        if(absences == 2 || consecutiveLate == 3)
            return 0;

        // Edge case: If it's possible to create a valid attendence record of length N then there's 1 valid way
        if(N == 0)
            return 1;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[N][absences][consecutiveLate] != -1)
            return memory[N][absences][consecutiveLate];

        // There are three possibilities which the student can perform at each day
        int A = solveWithMemo(memory, N - 1, absences + 1, 0) % MOD;               // Is to go absent 
        int L = solveWithMemo(memory, N - 1, absences, consecutiveLate + 1) % MOD; // Is to go late
        int P = solveWithMemo(memory, N - 1, absences, 0) % MOD;                   // Is to present 

        // Store the result value to the memoization table and then return it
        return memory[N][absences][consecutiveLate] = ((A + L) % MOD + P) % MOD;
    }

    // O(3^N) & O(N)
    int solveWithoutMemo(int N, int absences, int consecutiveLate) {
        // Edge case: If the student goes absent for 2 days or goes late for consecutively 3 days then there's no valid way
        if(absences == 2 || consecutiveLate == 3)
            return 0;

        // Edge case: If it's possible to create a valid attendence record of length N then there's 1 valid way
        if(N == 0)
            return 1;
        
        // There are three possibilities which the student can perform at each day
        int A = solveWithoutMemo(N - 1, absences + 1, 0) % MOD;               // Is to go absent 
        int L = solveWithoutMemo(N - 1, absences, consecutiveLate + 1) % MOD; // Is to go late
        int P = solveWithoutMemo(N - 1, absences, 0) % MOD;                   // Is to present 

        return ((A + L) % MOD + P) % MOD;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;

public:
    // #1 Method to find the total number of specified attendance records of length N, using 3D tabulation - O(N*2*3) & O(N*3*4)
    int checkRecord_V1(int N) {
        // 3D DP table
        vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(3, vector<int>(4, 0)));

        // Initialize the first edge case: If it's possible to create a valid attendence record of length N then there's 1 valid way
        for(int absences = 0; absences < 2; ++absences)
            for(int consecutiveLate = 0; consecutiveLate < 3; ++consecutiveLate)
                dp[0][absences][consecutiveLate] = 1;

        // Fill the rest of the table
        for(int length = 1; length <= N; ++length) {
            for(int absences = 1; absences >= 0; --absences) {
                for(int consecutiveLate = 2; consecutiveLate >= 0; --consecutiveLate) {
                    int A = dp[length - 1][absences + 1][0] % MOD; 
                    int L = dp[length - 1][absences][consecutiveLate + 1] % MOD; 
                    int P = dp[length - 1][absences][0] % MOD;                   
                    dp[length][absences][consecutiveLate] = ((A + L) % MOD + P) % MOD;   
                }
            }
        }

        // Return the result value
        return dp[N][0][0];
    }

    // #2 Method to find the total number of specified attendance records of length N, using 2D tabulation - O(N*2*3) & O(2*3*4)
    int checkRecord_V2(int N) {
        // 2D DP tables
        vector<vector<int>> prevRow(3, vector<int>(4, 0)), currRow(3, vector<int>(4, 0));

        // Initialize the first edge case: If it's possible to create a valid attendence record of length N then there's 1 valid way
        for(int absences = 0; absences < 2; ++absences)
            for(int consecutiveLate = 0; consecutiveLate < 3; ++consecutiveLate)
                prevRow[absences][consecutiveLate] = 1;

        // Fill the rest of the table
        for(int length = 1; length <= N; ++length) {
            for(int absences = 1; absences >= 0; --absences) {
                for(int consecutiveLate = 2; consecutiveLate >= 0; --consecutiveLate) {
                    int A = prevRow[absences + 1][0] % MOD; 
                    int L = prevRow[absences][consecutiveLate + 1] % MOD; 
                    int P = prevRow[absences][0] % MOD;                   
                    currRow[absences][consecutiveLate] = ((A + L) % MOD + P) % MOD;   
                }
            }
            prevRow = currRow;
        }

        // Return the result value
        return prevRow[0][0];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Dynamic Programming
Link  : https://leetcode.com/problems/student-attendance-record-ii/description/?envType=daily-question&envId=2024-05-26
