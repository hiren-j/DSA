// Code to find if there exists a path from the top-left cell to the bottom right cell of the maze provided only downward and rightward movements are allowed. Note that some cells have a door while some do not and a key that can be used only once to open a door ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find if there exists a path from top left to bottom right cell, using recursion with memoization - O(N^2) & O(N^2) 
    bool mazeWithNDoorsAnd1Key(vector<vector<int>>& maze, int N) {
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(N, vector<int>(2, -1)));
        return solveWithMemo(dp, maze, N, 0, 0, 1);
    }

private:
    // O(2*N*N*2) & O(N*N*2 + 2*N)
    bool solveWithMemo(vector<vector<vector<int>>>& dp, vector<vector<int>>& maze, int N, int R, int C, int keys) {
        // Edge case: If you walk outside of the maze or try to use 2 keys along the path then return false
        if(R == N || C == N || keys < 0)
            return false;

        // Edge case: If reached the bottom right cell and you've used 0 or 1 key along the path then return 1
        if(R == N-1 && C == N-1) 
            return (keys - maze[R][C] >= 0); 

        if(dp[R][C][keys] != -1)
            return dp[R][C][keys];

        // There are always two possibilities to perform at each cell
        bool moveRight = solveWithMemo(dp, maze, N, R, C+1, keys - maze[R][C]); // Is to move right
        bool moveDown  = solveWithMemo(dp, maze, N, R+1, C, keys - maze[R][C]); // Is to move down

        return dp[R][C][keys] = (moveRight || moveDown);
    }

    // O(2^(N*N)) & O(2*N)
    bool solveWithoutMemo(vector<vector<int>>& maze, int N, int R, int C, int keys) {
        // Edge case: If you walk outside of the maze or try to use 2 keys along the path then return false
        if(R == N || C == N || keys < 0)
            return false;

        // Edge case: If reached the bottom right cell and you've used 0 or 1 key along the path then return 1
        if(R == N-1 && C == N-1) 
            return (keys - maze[R][C] >= 0); 

        // There are always two possibilities to perform at each cell
        bool moveRight = solveWithoutMemo(maze, N, R, C+1, keys - maze[R][C]); // Is to move right
        bool moveDown  = solveWithoutMemo(maze, N, R+1, C, keys - maze[R][C]); // Is to move down

        return (moveRight || moveDown);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find if there exists a path from top left to bottom right cell, using 3D tabulation - O(N^2) & O(N^2)
    bool mazeWithNDoorsAnd1Key_V1(vector<vector<int>>& maze, int N) {
        vector<vector<vector<bool>>> dp(N+1, vector<vector<bool>>(N+1, vector<bool>(2, false)));

        // Initialize the second edge case
        dp[N-1][N-1][1] = true;
        dp[N-1][N-1][0] = (maze[N-1][N-1] == 0);

        for(int R = N-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == N-1 && C == N-1)
                    continue;
                for(int keys = 0; keys <= 1; ++keys) {
                    bool moveRight = (keys - maze[R][C] >= 0) ? dp[R][C+1][keys - maze[R][C]] : false;
                    bool moveDown  = (keys - maze[R][C] >= 0) ? dp[R+1][C][keys - maze[R][C]] : false;
                    dp[R][C][keys] = (moveRight || moveDown);	
                }
            }
        }

        return dp[0][0][1];
    }

    // #2 Method to find if there exists a path from top left to bottom right cell, using 2D tabulation - O(N^2) & O(N)
    bool mazeWithNDoorsAnd1Key_V2(vector<vector<int>>& maze, int N) {
        vector<vector<bool>> nextRow(N+1, vector<bool>(2, false)), idealRow(N+1, vector<bool>(2, false));

        // Initialize the second edge case
        idealRow[N-1][1] = true;
        idealRow[N-1][0] = (maze[N-1][N-1] == 0);

        for(int R = N-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == N-1 && C == N-1)
                    continue;
                for(int keys = 0; keys <= 1; ++keys) {
                    bool moveRight = (keys - maze[R][C] >= 0) ? idealRow[C+1][keys - maze[R][C]] : false;
                    bool moveDown  = (keys - maze[R][C] >= 0) ? nextRow[C][keys - maze[R][C]] : false;
                    idealRow[C][keys] = (moveRight || moveDown);	
                }
            }
            nextRow = idealRow;
        }

        return nextRow[0][1];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Matrix | Dynamic Programming 
Link  : https://www.naukri.com/code360/problems/maze-with-n-doors-and-1-key_839809?topList=top-dynamic-programming-questions&problemListRedirection=true&page=2&leftPanelTabValue=PROBLEM
