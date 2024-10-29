// Code to check whether there exists a valid parentheses string path in the grid or not ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DON'T IGNORE MUST READ: As you work on this problem, you'll notice that there isn't a bottom-up solution provided. 
                        This is one of the two problems in the multi-dimensional folder where I couldn't get the bottom-up approach to pass all the test cases. 
                        The issue wasn't with time limits but with incorrect results. So, I've only included the top-down (memoized) solution for this problem. 
                        There are only two problems in the entire DP series without bottom-up solutions. These three lies in this folder.
    
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int N, M;

    // O(2^(N*M)) & O(N+M)
    bool solveWithoutMemo(vector<vector<char>>& grid, int R, int C, int stackLength) {
        // Edge case: If all the rows or columns are exhausted then you can't find any path
        if(R == N || C == M)
            return false;

        // Edge case: If it's a closing parentheses then we've found a valid pair of parentheses hence reduce the stack length by 1
        if(grid[R][C] == ')')
            stackLength--;

        // Edge case: If the stack length becomes negative then there doesn't exist a valid path
        if(stackLength < 0)
            return false;
            
        // Edge case: If you reached the bottom right corner and the stack becomes empty then we've found a valid path
        if(R == N-1 && C == M-1)
            return stackLength == 0;
        
        // Edge case: If it's a opening parentheses then assume we're pushing it to the stack hence increase the stack length by 1 
        if(grid[R][C] == '(')
            stackLength++;

        // There are always two possibilities to perform at each cell
        bool moveRight = solveWithoutMemo(grid, R, C+1, stackLength); // Is to move right
        bool moveDown  = solveWithoutMemo(grid, R+1, C, stackLength); // Is to move down

        // Return true if you've found the valid path from any possibility
        return (moveRight || moveDown);
    }

    // O(2*N*M*N+M) & O(N*M*N+M + N+M)
    bool solveWithMemo(vector<vector<vector<int>>>& memory, vector<vector<char>>& grid, int R, int C, int stackLength) {
        // Edge case: If all the rows or columns are exhausted then you can't find any path
        if(R == N || C == M)
            return false;

        // Edge case: If it's a closing parentheses then we've found a valid pair of parentheses hence reduce the stack length by 1
        if(grid[R][C] == ')')
            stackLength--;

        // Edge case: If the stack length becomes negative then there doesn't exist a valid path
        if(stackLength < 0)
            return false;
            
        // Edge case: If you reached the bottom right corner and the stack becomes empty then we've found a valid path
        if(R == N-1 && C == M-1)
            return stackLength == 0;
        
        // Edge case: If it's a opening parentheses then assume we're pushing it to the stack hence increase the stack length by 1 
        if(grid[R][C] == '(')
            stackLength++;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[R][C][stackLength] != -1)
            return memory[R][C][stackLength];

        // There are always two possibilities to perform at each cell
        bool moveRight = solveWithMemo(memory, grid, R, C+1, stackLength); // Is to move right
        bool moveDown  = solveWithMemo(memory, grid, R+1, C, stackLength); // Is to move down

        // Store the result value to the memoization table and then return it
        return memory[R][C][stackLength] = (moveRight || moveDown);
    }

public:
    // Method to check whether there exists a valid parentheses string path or not, using recursion with memoization :-
    bool hasValidPath(vector<vector<char>>& grid) {
        N = grid.size(), M = grid[0].size();
        if(N == 1 && M == 1) return false;
        vector<vector<vector<int>>> memory(N, vector<vector<int>>(M, vector<int>(N+M, -1)));
        return solveWithMemo(memory, grid, 0, 0, 0);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/description/
