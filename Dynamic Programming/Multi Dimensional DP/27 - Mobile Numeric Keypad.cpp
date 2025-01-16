// Code to find the number of possible unique sequences of length n that you can create by pressing buttons (You can start from any digit) ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {    
    #define LL long long

    vector<vector<int>> directions = {{0,0}, {-1,0}, {1,0}, {0,-1}, {0,1}};
    vector<vector<int>> numpad     = {{1, 2, 3},
                                      {4, 5, 6},
                                      {7, 8, 9},
                                      {-1, 0, -1}};

    // O(10 * 5^N) & O(N) 
    LL solveWithoutMemo(int N, int R, int C) {
        // Edge case: No number exists outside of the numpad and if you try to look for it or you've pressed '*' or '#' then you've no valid way
        if(R < 0 || C < 0 || R == 4 || C == 3 || numpad[R][C] == -1)
            return 0;
            
        // Edge case: If you've correctly dialed a phone number of length N then you've one valid way
        if(N == 0)
            return 1;
                    
        // Stores the result value
        LL count = 0;
        
        // Explore all the 5 directions one by one from the cell (R, C) and dial the phone numbers 
        for(auto& dir : directions) {
            int reachRow = R + dir[0];
            int reachCol = C + dir[1];
            count += solveWithoutMemo(N - 1, reachRow, reachCol);
        }

        // Return the result value
        return count;
    }

    // O(10 + 5*N*4*3) & O(N*4*3 + N)
    LL solveWithMemo(vector<vector<vector<LL>>>& memory, int N, int R, int C) {
        // Edge case: No number exists outside of the numpad and if you try to look for it or you've pressed '*' or '#' then you've no valid way
        if(R < 0 || C < 0 || R == 4 || C == 3 || numpad[R][C] == -1)
            return 0;
            
        // Edge case: If you've correctly dialed a phone number of length N then you've one valid way
        if(N == 0)
            return 1;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[N][R][C] != -1)
            return memory[N][R][C];
            
        // Stores the result value
        LL count = 0;
        
        // Explore all the 5 directions one by one from the cell (R, C) and dial the phone numbers 
        for(auto& dir : directions) {
            int reachRow = R + dir[0];
            int reachCol = C + dir[1];
            count += solveWithMemo(memory, N - 1, reachRow, reachCol);
        }
        
        // Store the result value to the memoization table and then return it
        return memory[N][R][C] = count;
    }
    
public:
    // Method to find how many distinct phone numbers of length N you can dial, using recursion with memoization - O(N) & O(N)
    LL getCount(int N) {
        LL result = 0;
        
        // 3D memoization table
        vector<vector<vector<LL>>> memory(N, vector<vector<LL>>(4, vector<LL>(3, -1)));
        
        // Start dialing from the cells which doesn't starts from '*' or '#'
        for(int R = 0; R < 4; ++R) 
            for(int C = 0; C < 3; ++C) 
                if(numpad[R][C] != -1)
                    result += solveWithMemo(memory, N - 1, R, C);

        // Return the result value 
        return result;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    #define LL long long

    vector<vector<int>> directions = {{0,0}, {-1,0}, {1,0}, {0,-1}, {0,1}};
    vector<vector<int>> numpad     = {{1, 2, 3},
                                      {4, 5, 6},
                                      {7, 8, 9},
                                      {-1, 0, -1}};
public:
    // Method to find how many distinct phone numbers of length N you can dial, using 3D tabulation - O(N*4*3*5) & O(N*4*3)
    LL getCount(int N) {
        LL result = 0;
        
        // 3D DP table
        vector<vector<vector<LL>>> dp(N, vector<vector<LL>>(4, vector<LL>(3, 0)));

        // Initialize the second edge case: If you've correctly dialed a phone number of length N then you've one valid way
        for(int R = 0; R < 4; ++R)
            for(int C = 0; C < 3; ++C)
                dp[0][R][C] = 1;

        // Fill the rest of the table
        for(int length = 1; length < N; ++length) {
            for(int R = 3; R >= 0; --R) {
                for(int C = 2; C >= 0; --C) {
                    if(numpad[R][C] != -1) {
                        LL count = 0;
                        for(auto& dir : directions) {
                            int reachRow = R + dir[0];
                            int reachCol = C + dir[1];
                            if(reachRow >= 0 && reachCol >= 0 && reachRow < 4 && reachCol < 3 && numpad[reachRow][reachCol] != -1) {
                                count += dp[length - 1][reachRow][reachCol];
                            }
                        }
                        dp[length][R][C] = count; 
                    }
                }
            }
        }

        // Start dialing from the cells which doesn't starts from '*' or '#'
        for(int R = 0; R < 4; ++R) 
            for(int C = 0; C < 3; ++C) 
                if(numpad[R][C] != -1)
                    result += dp[N - 1][R][C];

        // Return the result value 
        return result;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/mobile-numeric-keypad5456/1
