// Code to find how many distinct phone numbers of length N you can dial ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;

    vector<vector<int>> directions = {{-2, -1}, {-1, -2}, {-2, 1}, {-1, 2}, {2, -1}, {1, -2}, {2, 1}, {1, 2}};
    vector<vector<int>> dialpad    = {{1, 2, 3},
                                      {4, 5, 6},
                                      {7, 8, 9},
                                      {-1, 0, -1}};
    // O(10 * 8^N) & O(N)
    int solveWithoutMemo(int N, int R, int C) {
        // Edge case: No number exists outside of the dialpad and if you try to look for it or you've pressed '*' or '#' then you've no valid way
        if(R < 0 || C < 0 || R >= 4 || C >= 3 || dialpad[R][C] == -1)
            return 0;

        // Edge case: If you've correctly dialed a phone number of length N then you've one valid way
        if(N == 0)
            return 1;

        // Stores the result value
        int count = 0;

        // Explore all the 8 directions one by one from the cell (R, C) and dial the phone numbers 
        for(auto& dir : directions) {
            int reachRow = R + dir[0];
            int reachCol = C + dir[1];
            count = (count + solveWithoutMemo(N - 1, reachRow, reachCol)) % MOD;
        }

        // Return the result value
        return count % MOD;
    }
    
    // O(10 + 8*N*4*3) & O(N*4*3 + N)
    int solveWithMemo(vector<vector<vector<int>>>& memory, int N, int R, int C) {
        // Edge case: No number exists outside of the dialpad and if you try to look for it or you've pressed '*' or '#' then you've no valid way
        if(R < 0 || C < 0 || R >= 4 || C >= 3 || dialpad[R][C] == -1)
            return 0;

        // Edge case: If you've correctly dialed a phone number of length N then you've one valid way
        if(N == 0)
            return 1;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[N][R][C] != -1)
            return memory[N][R][C];

        // Stores the result value
        int count = 0;

        // Explore all the 8 directions one by one from the cell (R, C) and dial the phone numbers 
        for(auto& dir : directions) {
            int reachRow = R + dir[0];
            int reachCol = C + dir[1];
            count = (count + solveWithMemo(memory, N - 1, reachRow, reachCol)) % MOD;
        }

        // Store the result value to the memoization table and then return it
        return memory[N][R][C] = count % MOD;
    }

public:
    // Method to find how many distinct phone numbers of length N you can dial, using recursion with memoization - O(N) & O(N)
    int knightDialer(int N) {
        int result = 0;
        
        // 3D memoization table
        vector<vector<vector<int>>> memory(N, vector<vector<int>>(4, vector<int>(3, -1)));

        // Start dialing from the cells which doesn't starts from '*' or '#'
        for(int R = 0; R < 4; ++R) 
            for(int C = 0; C < 3; ++C) 
                if(dialpad[R][C] != -1) 
                    result = (result + solveWithMemo(memory, N - 1, R, C)) % MOD;

        // Return the result value
        return result % MOD;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;

    vector<vector<int>> directions = {{-2, -1}, {-1, -2}, {-2, 1}, {-1, 2}, {2, -1}, {1, -2}, {2, 1}, {1, 2}};
    vector<vector<int>> dialpad    = {{1, 2, 3},
                                      {4, 5, 6},
                                      {7, 8, 9},
                                      {-1, 0, -1}};
public:
    // Method to find how many distinct phone numbers of length N you can dial, using 3D tabulation - O(N*4*3*8) & O(N*4*3)
    int knightDialer(int N) {
        // 3D DP table
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(4, vector<int>(3, 0)));

        // Initialize the second edge case: If you've correctly dialed a phone number of length N then you've one valid way
        for(int R = 0; R < 4; ++R)
            for(int C = 0; C < 3; ++C)
                dp[0][R][C] = 1;

        // Fill the rest of the table
        for(int length = 1; length < N; ++length) {
            for(int R = 3; R >= 0; --R) {
                for(int C = 2; C >= 0; --C) {
                    if(dialpad[R][C] != -1) {
                        int count = 0;
                        for(auto& dir : directions) {
                            int reachRow = R + dir[0];
                            int reachCol = C + dir[1];
                            if(reachRow >= 0 && reachCol >= 0 && reachRow < 4 && reachCol < 3 && dialpad[reachRow][reachCol] != -1) {
                                count = (count + dp[length - 1][reachRow][reachCol]) % MOD;
                            }
                        }
                        dp[length][R][C] = count % MOD;
                    }
                }
            }
        }

        int result = 0;

        // Start dialing from the cells which doesn't starts from '*' or '#'
        for(int R = 0; R < 4; ++R) 
            for(int C = 0; C < 3; ++C) 
                if(dialpad[R][C] != -1) 
                    result = (result + dp[N - 1][R][C]) % MOD;

        // Return the result value
        return result % MOD;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming
Link  : https://leetcode.com/problems/knight-dialer/description/
