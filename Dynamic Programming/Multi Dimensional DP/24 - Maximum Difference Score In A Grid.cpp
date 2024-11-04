// Code to find the maximum total score you can achieve. You are given an m x n matrix grid consisting of positive integers. You can move from a cell in the matrix to any other cell that is either to the bottom or to the right (not necessarily adjacent). The score of a move from a cell with the value c1 to a cell with the value c2 is c2 - c1. You can start at any cell, and you have to make at least one move ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int N, M;

    // O(M*N*M + N*N*M) & O(N*M + N+M)
    int getMaxPositiveScore(vector<vector<int>>& dp, vector<vector<int>>& grid, int startR, int startC) {
        // Memoization table: If the current state is already computed then return the comptuted value
        if(dp[startR][startC] != -1)
            return dp[startR][startC];

        // There are always two possibilities to perform at each cell
        int moveRight = 0; // Is to move to any right cell 
        int moveDown  = 0; // Is to move to any bottom cell

        // Explore each right cell and get the score you can get from all the possibility and then update the result by the maximum value
        for(int C = startC+1; C < M; ++C) 
            moveRight = max(moveRight, grid[startR][C] - grid[startR][startC] + getMaxPositiveScore(dp, grid, startR, C));
        
        // Explore each bottom cell and get the score you can get from all the possibility and then update the result by the maximum value
        for(int R = startR+1; R < N; ++R) 
            moveDown = max(moveDown, grid[R][startC] - grid[startR][startC] + getMaxPositiveScore(dp, grid, R, startC));

        // Store the result value to the memoization table and then return it
        return dp[startR][startC] = max(moveRight, moveDown);
    }
    // Note: Without memoization the time complexity of this function will be O(M^(N*M) + N^(N*M)) and the auxiliary space will be O(N+M)

    // O(3*N*M) & O(2*N*M)
    int getMaxNegativeScore(vector<vector<int>>& grid) {
        // 2D tabulation tables
        vector<vector<int>> maxElementRight(N, vector<int>(M, INT_MIN));
        vector<vector<int>> maxElementDown(N, vector<int>(M, INT_MIN));

        // Find the maximum element lying at the right side of each cell
        for(int R = 0; R < N; ++R) {
            maxElementRight[R][M-1] = grid[R][M-1];
            for(int C = M-2; C >= 0; --C) {
                maxElementRight[R][C] = max(grid[R][C], maxElementRight[R][C+1]);
            }
        }

        // Find the maximum element lying at the bottom side of each cell
        for(int C = 0; C < M; ++C) {
            maxElementDown[N-1][C] = grid[N-1][C];
            for(int R = N-2; R >= 0; --R) {
                maxElementDown[R][C] = max(grid[R][C], maxElementDown[R+1][C]);
            }
        }
        
        int maxNegScore = INT_MIN;

        // Move to each cell and update the maximum negative score
        for(int R = 0; R < N; ++R) {
            for(int C = 0; C < M; ++C) {
                int scoreRight = (C + 1 < M) ? maxElementRight[R][C + 1] : INT_MIN;
                int scoreDown  = (R + 1 < N) ? maxElementDown[R + 1][C] : INT_MIN;
                if(scoreRight != INT_MIN) maxNegScore = max(maxNegScore, scoreRight - grid[R][C]);
                if(scoreDown  != INT_MIN) maxNegScore = max(maxNegScore, scoreDown - grid[R][C]);
            }
        }
        
        return maxNegScore;
    }

public:
    // Method to find the maximum score you can achieve, using recursion with memoization and 2D tabulation - O(N*M*(M+N)) & O(N*M)
    int maxScore(vector<vector<int>>& grid) {
        N = grid.size(), M = grid[0].size();

        int maxPosScore = 0;

        // 2D memoization table
        vector<vector<int>> dp(N, vector<int>(M, -1));

        // Consider each cell as an unique start point and find the maximum positive score you can get from it and then update the result by the maximum value
        for(int R = 0; R < N; ++R)
            for(int C = 0; C < M; ++C)
                maxPosScore = max(maxPosScore, getMaxPositiveScore(dp, grid, R, C));
        
        // If the maximum positive score is 0 then there is a chance that the result could be a maximum negative value hence find the maximum negative score and then return it
        return (maxPosScore == 0) ? getMaxNegativeScore(grid) : maxPosScore;
    }
};
// Note: This solution will lead to time-limit-exceed

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int N, M;

    // O(3*N*M) & O(2*N*M)
    int getMaxNegativeScore(vector<vector<int>>& grid) {
        // 2D tabulation tables
        vector<vector<int>> maxElementRight(N, vector<int>(M, INT_MIN));
        vector<vector<int>> maxElementDown(N, vector<int>(M, INT_MIN));

        // Find the maximum element lying at the right side of each cell
        for(int R = 0; R < N; ++R) {
            maxElementRight[R][M-1] = grid[R][M-1];
            for(int C = M-2; C >= 0; --C) {
                maxElementRight[R][C] = max(grid[R][C], maxElementRight[R][C+1]);
            }
        }

        // Find the maximum element lying at the bottom side of each cell
        for(int C = 0; C < M; ++C) {
            maxElementDown[N-1][C] = grid[N-1][C];
            for(int R = N-2; R >= 0; --R) {
                maxElementDown[R][C] = max(grid[R][C], maxElementDown[R+1][C]);
            }
        }
        
        int maxNegScore = INT_MIN;

        // Move to each cell and update the maximum negative score
        for(int R = 0; R < N; ++R) {
            for(int C = 0; C < M; ++C) {
                int scoreRight = (C+1 < M) ? maxElementRight[R][C+1] : INT_MIN;
                int scoreDown  = (R+1 < N) ? maxElementDown[R+1][C] : INT_MIN;
                if(scoreRight != INT_MIN) maxNegScore = max(maxNegScore, scoreRight - grid[R][C]);
                if(scoreDown  != INT_MIN) maxNegScore = max(maxNegScore, scoreDown - grid[R][C]);
            }
        }

        return maxNegScore;
    }

public:
    // Method to find the maximum score you can achieve, using 2D multi tabulation - O(N*M*(M+N)) & O(N*M)
    int maxScore(vector<vector<int>>& grid) {
        N = grid.size(), M = grid[0].size();

        int maxPosScore = 0;

        // 2D tabulation table
        vector<vector<int>> dp(N, vector<int>(M, 0));

        // Fill the table and find the maximum positive score you can get
        for(int startR = N-1; startR >= 0; --startR) {
            for(int startC = M-1; startC >= 0; --startC) {
                int moveRight = 0;
                int moveDown  = 0;

                for(int C = startC+1; C < M; ++C) 
                    moveRight = max(moveRight, grid[startR][C] - grid[startR][startC] + dp[startR][C]);        
                for(int R = startR+1; R < N; ++R) 
                    moveDown = max(moveDown, grid[R][startC] - grid[startR][startC] + dp[R][startC]);
                
                dp[startR][startC] = max(moveRight, moveDown);
                maxPosScore = max(maxPosScore, dp[startR][startC]);
            }
        }

        // If the maximum positive score is 0 then there is a chance that the result could be a maximum negative value hence find the maximum negative score and then return it
        return (maxPosScore == 0) ? getMaxNegativeScore(grid) : maxPosScore;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/maximum-difference-score-in-a-grid/description/
