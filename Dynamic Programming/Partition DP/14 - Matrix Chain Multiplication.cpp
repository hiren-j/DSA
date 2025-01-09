// Code to find the minimum cost required to multiply all the given matrices. The cost of matrix multiplication is defined as the number of scalar multiplications. A Chain of matrices A1, A2, A3,.....An is represented by a sequence of numbers in an array ‘arr’ where the dimension of 1st matrix is equal to arr[0] * arr[1] , 2nd matrix is arr[1] * arr[2], and so on ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    NOTE (REGARDING TIME COMPLEXITY OF `solveWithoutMemo` FUNCTION) => O(N * 2^N) : At each matrix, you're exploring 2 options or doing 2 partitions. 
                                                                                    As we have N-1 matrices, so for all of them, you're exploring 2 options, which makes it 2^(N-1) = O(2^N). 
                                                                                    Now, apart from this, in each recursive call, you will again explore 2 options on that same matrix, which you may 
                                                                                    have already explored for any other matrix in a different recursive call. So, in the worst case, we have N-1 matrices, 
                                                                                    so for each, you may do the same thing in the recursion, making it O(N * 2^N).
*/

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    // O(N * 2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int n, int i, int j) {
        // Base case: If there's only a single matrix then no multiplication is required or could say no cost is required
        if(i == j)
            return 0;

        // Stores the minimum cost required to multiply matrices lying within i to j (result value)
        int minCost = INT_MAX;

        // Consider each matrix as an unique start point and from a particular consideration find the total cost to multiply all the matrices. Among all the considerations choose the one which gives the minimum cost 
        for(int k = i; k < j; ++k) {
            int currCost = nums[i - 1] * nums[k] * nums[j] 
                         + solveWithoutMemo(nums, n, i, k)
                         + solveWithoutMemo(nums, n, k + 1, j);
            minCost = min(minCost, currCost);
        }

        // Return the result value
        return minCost;
    }
    /*
        Note: solve(i, j) represents the minimum "multiplications / cost" required to multiply matrices lying within i to j.
        Note: solve(k+1, j) represents the minimum "multiplications / cost" required to multiply matrices lying within k+1 to j.
    */

    // O(N * 2*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int n, int i, int j) {
        // Base case: If there's only a single matrix then no multiplication is required or could say no cost is required
        if(i == j)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[i][j] != -1)
            return memory[i][j];    

        // Stores the minimum cost required to multiply matrices lying within i to j (result value)
        int minCost = INT_MAX;

        // Consider each matrix as an unique start point and from a particular consideration find the total cost to multiply all the matrices. Among all the considerations choose the one which gives the minimum cost 
        for(int k = i; k < j; ++k) {
            int currCost = nums[i - 1] * nums[k] * nums[j] 
                         + solveWithMemo(memory, nums, n, i, k)
                         + solveWithMemo(memory, nums, n, k + 1, j);
            minCost = min(minCost, currCost);
        }

        // Stores the result value to the memoization table and then return it
        return memory[i][j] = minCost;
    }

public:
    // Method to find the minimum cost required to multiply all the matrices, using recursion with memoization - O(N^3) & O(N^2)
    int matrixMultiplication(vector<int>& nums, int n) {
        vector<vector<int>> memory(n, vector<int>(n, -1));
        return solveWithMemo(memory, nums, n, 1, n - 1);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the minimum cost required to multiply all the matrices, using 2D tabulation - O(N^3) & O(N^2)
    int matrixMultiplication_V1(vector<int> &nums, int n) {
        // 2D DP table
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));

        // Fill the table
        for(int i = n-1; i >= 1; --i) {
            for(int j = 1; j < n; ++j) {
                // Initialize the base case
                if(i == j) {
                    dp[i][j] = 0;
                }
                else {
                    int minCost = INT_MAX;

                    for(int k = i; k < j; ++k) {
                        int currCost = nums[i - 1] * nums[k] * nums[j] 
                                     + dp[i][k]
                                     + dp[k + 1][j];
                        minCost = min(minCost, currCost);
                    }

                    dp[i][j] = minCost;
                }
            }
        }

        // Return the result value
        return dp[1][n - 1];
    }

    // #2 Method to find the minimum cost required to multiply all the matrices, using 2D tabulation - O(N^3) & O(N^2)
    int matrixMultiplication_V2(vector<int>& nums, int n) {
        // 2D DP table
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Fill the table
        for(int i = n-1; i >= 1; --i) {
            for(int j = 1; j <= n-1; ++j) {
                // Ensure to handle the base case
                if(i == j)
                    continue;
                    
                int minCost = INT_MAX;
                
                for(int k = i; k < j; ++k) {
                    int currCost = nums[i - 1] * nums[k] * nums[j] 
                                 + dp[i][k] 
                                 + dp[k + 1][j];
                    minCost = min(minCost, currCost);
                }
                
                dp[i][j] = minCost; 
            }
        }

        // Return the result value
        return dp[1][n - 1];
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Matrix | Dynamic Programming
Links : https://www.geeksforgeeks.org/problems/matrix-chain-multiplication0303/1
        https://www.naukri.com/code360/problems/matrix-chain-multiplication_975344
