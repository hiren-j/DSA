// Code to find the maximum number of moves that you can perform in the grid. You can start at any cell in the first column of the matrix, and traverse the grid in the following way: From a cell (row, col), you can move to any of the cells: (row - 1, col + 1), (row, col + 1) and (row + 1, col + 1) such that the value of the cell you move to, should be strictly bigger than the value of the current cell ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    vector<vector<int>> directions = {{-1,1}, {0,1}, {1,1}};
    int N, M;

    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < N && C < M; 
    }

    // O(N * 3^(N*M)) & O(N+M)
    int solveWithoutMemo(vector<vector<int>>& grid, int R, int C) {
        int maxMoves = 0;

        // Explore all the directions one by one and then update the result by the maximum value
        for(auto& dir : directions) {
            int reachR = R + dir[0];
            int reachC = C + dir[1];
            if(isValid(reachR, reachC) && grid[reachR][reachC] > grid[R][C]) {
                maxMoves = max(maxMoves, 1 + solveWithoutMemo(grid, reachR, reachC));
            }
        }   

        return maxMoves;
    }

    // O(N + 3*N*M) & O(N*M + N+M)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& grid, int R, int C) {
        // Memoization table: If the current state is already computed then return the computed value 
        if(memory[R][C] != -1)
            return memory[R][C];

        int maxMoves = 0;

        // Explore all the directions one by one and then update the result by the maximum value
        for(auto& dir : directions) {
            int reachR = R + dir[0];
            int reachC = C + dir[1];
            if(isValid(reachR, reachC) && grid[reachR][reachC] > grid[R][C]) {
                maxMoves = max(maxMoves, 1 + solveWithMemo(memory, grid, reachR, reachC));
            }
        }   

        // Store the result value to the memoization table and then return it
        return memory[R][C] = maxMoves;
    }

public:
    // Method to find the maximum number of moves you can perform in the grid, using recursion with memoization - O(N*M) & O(N*M)
    int maxMoves(vector<vector<int>>& grid) {
        N = grid.size(), M = grid[0].size();
        int result = 0;

        // 2D memoization table
        vector<vector<int>> memory(N, vector<int>(M, -1));

        // Start from the first column of each row and find the maximum moves you can perform from it and then update the result by the maximum value 
        for(int R = 0; R < N; ++R)
            result = max(result, solveWithMemo(memory, grid, R, 0));

        return result;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    vector<vector<int>> directions = {{-1,1}, {0,1}, {1,1}};
    int N, M;

    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < N && C < M; 
    }

public:
    // Method to find the maximum number of moves you can perform in the grid, using 2D tabulation - O(N*M) & O(N*M)
    int maxMoves(vector<vector<int>>& grid) {
        N = grid.size(), M = grid[0].size();

        vector<vector<int>> dp(N, vector<int>(M, 0));

        for(int C = M-1; C >= 0; --C) {
            for(int R = N-1; R >= 0; --R) {
                int maxMoves = 0;
                for(auto& dir : directions) {
                    int reachR = R + dir[0];
                    int reachC = C + dir[1];
                    if(isValid(reachR, reachC) && grid[reachR][reachC] > grid[R][C]) {
                        maxMoves = max(maxMoves, 1 + dp[reachR][reachC]);
                    }
                }
                dp[R][C] = maxMoves;
            }
        }

        int result = 0;

        for(int R = 0; R < N; ++R)
            result = max(result, dp[R][0]);

        return result;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/maximum-number-of-moves-in-a-grid/description/?envType=daily-question&envId=2024-10-29
