// Code to check is if you can reach the final cell with a health value of 1 or more. You start on the upper-left corner (0, 0) and would like to get to the lower-right corner (m - 1, n - 1). You can move up, down, left, or right from one cell to another adjacent cell as long as your health remains positive. Cells (i, j) with grid[i][j] = 1 are considered unsafe and reduce your health by 1 ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DON'T IGNORE MUST READ: Creating a correct bottom-up solution for this problem is not possible because of how cells are visited and marked during recursion. Even if you convert the memoized (top-down) solution to bottom-up, it won’t work properly. 
                        The issue comes from the fact that, in the recursive solution, cells are marked as "visited" and "unvisited" at different stages, which can't be handled in a bottom-up approach. In many cases, even memoization fails when handling these visited/unvisited states. 
                        However, for this specific problem, memoization works fine, but the bottom-up approach still cannot manage the visited/unvisited states correctly.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    vector<vector<int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    int M, N;
    
    // O(4^(N*M)) & O(N*M + 4*2)
    bool solveWithoutMemo(vector<vector<int>>& grid, int health, int R, int C) {
        // Edge case: If you walk outside of the grid or if the cell is already visited then return false
        if(R < 0 || C < 0 || R >= M || C >= N || grid[R][C] == -1)
            return false;

        // If the cell is unsafe then reduce the health by 1 
        if(grid[R][C] == 1)
            health--;

        // Edge case: If health is less than or equal to 0, then return false
        if(health <= 0)
            return false;

        // Edge case: If you can reach the lower-right corner with a health value of 1 or more, then return true
        if(R == M-1 && C == N-1)
            return health > 0;
        
        // Mark the cell (R, C) as visited
        int currCellValue = grid[R][C];
        grid[R][C] = -1; 

        // Recursively check all the possible directions and return true if any of the direction return true
        for(auto& dir : directions) 
            if(solveWithoutMemo(grid, health, R + dir[0], C + dir[1])) 
                return true;

        // Mark the cell (R, C) as unvisited
        grid[R][C] = currCellValue;

        // If no direction returns true, then return false
        return false;
    }
    
    // O(4*N*M*H) & O(N*M*H + N*M + 4*2)
    bool solveWithMemo(vector<vector<vector<int>>>& memory, vector<vector<int>>& grid, int health, int R, int C) {
        // Edge case: If you walk outside of the grid or if the cell is already visited then return false
        if(R < 0 || C < 0 || R >= M || C >= N || grid[R][C] == -1)
            return false;

        // If the cell is unsafe then reduce the health by 1 
        if(grid[R][C] == 1)
            health--;

        // Edge case: If health is less than or equal to 0, then return false
        if(health <= 0)
            return false;

        // Edge case: If you can reach the lower-right corner with a health value of 1 or more, then return true
        if(R == M-1 && C == N-1)
            return health > 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[R][C][health] != -1)
            return memory[R][C][health];
        
        // Mark the cell (R, C) as visited
        int currCellValue = grid[R][C];
        grid[R][C] = -1; 

        // Recursively check all the possible directions and return true if any of the direction return true
        for(auto& dir : directions) 
            if(solveWithMemo(memory, grid, health, R + dir[0], C + dir[1])) 
                return memory[R][C][health] = true;

        // Mark the cell (R, C) as unvisited
        grid[R][C] = currCellValue;

        // Store the result value to the memoization table and then return it
        return memory[R][C][health] = false;
    }

public:
    // Method to check is if you can reach the final cell with a health value of 1 or more, using recursion with memoization - O(N*M*H) & (N*M*H) : Where H let be the health
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        M = grid.size(), N = grid[0].size();
        vector<vector<vector<int>>> memory(M, vector<vector<int>>(N, vector<int>(health + 1, -1)));
        return solveWithMemo(memory, grid, health, 0, 0);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Depth-First Search | Breadth-First Search | Graph | Memoization | Matrix
Link  : https://leetcode.com/problems/find-a-safe-walk-through-a-grid/
