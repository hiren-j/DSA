// Code to find the minimum total cost of the cuts by performing the cuts in the specified way ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the minimum total cost of the cuts, using recursion with memoization - O(M^3) & O(M^2)
    int getMinimumCost(int n, vector<int>& cuts) {
        cuts.insert(begin(cuts), 0);
        sort(begin(cuts), end(cuts));
        cuts.push_back(n);
        int m = cuts.size();
        vector<vector<int>> memory(m-1, vector<int>(m-1, -1));
        return solveWithMemo(memory, cuts, 1, m-2);
    }

private:
    // O(M * 2*M*M) & O(M*M + M)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& cuts, int i, int j) {
        // Edge case: If all the cut points are exhausted then you can't perform more cuts
        if(i > j)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[i][j] != -1)
            return memory[i][j];
        
        int minCost = INT_MAX;

        // Consider each cut as an unique start point and for a particular consideration find the total cost to cut the stick. Among all the considerations choose the one which gives the minimum cost
        for(int k = i; k <= j; ++k) {
            int currCost = cuts[j + 1] - cuts[i - 1]
                         + solveWithMemo(memory, cuts, i, k - 1)
                         + solveWithMemo(memory, cuts, k + 1, j);
            minCost = min(minCost, currCost);
        }

        // Store the result value to the memoization table and then return it
        return memory[i][j] = minCost;
    }
    
    // O(M * 2^M) & O(M)
    int solveWithoutMemo(vector<int>& cuts, int i, int j) {
        // Edge case: If all the cut points are exhausted then you can't perform more cuts
        if(i > j)
            return 0;

        int minCost = INT_MAX;

        // Consider each cut as an unique start point and for that particular consideration find the minimum cost to cut the stick. Among all the considerations choose the one which gives the minimum cost
        for(int k = i; k <= j; ++k) {
            int currCost = cuts[j + 1] - cuts[i - 1]
                         + solveWithoutMemo(cuts, i, k - 1)
                         + solveWithoutMemo(cuts, k + 1, j);
            minCost = min(minCost, currCost);
        }

        return minCost;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the minimum total cost of the cuts, using 2D tabulation - O(M^3) & O(M^2)
    int getMinimumCost(int n, vector<int>& cuts) {
        // Inserting 0 and n helps to easily find the cost of any particular cut. Sorting ensures the cuts are in the correct order for processing each subproblem
        cuts.insert(begin(cuts), 0);
        sort(begin(cuts), end(cuts));
        cuts.push_back(n);

        int m = cuts.size();

        // 2D DP table
        vector<vector<int>> dp(m, vector<int>(m, INT_MAX));

        // Fill the table
        for(int i = m-2; i >= 1; --i) {
            for(int j = 1; j <= m-2; ++j) {
                // Initialize the edge case
                if(i > j) {
                    dp[i][j] = 0;
                }
                else {
                    int minCost = INT_MAX;

                    for(int k = i; k <= j; ++k) {
                        int currCost  = cuts[j + 1] - cuts[i - 1];
                        int costLeft  = dp[i][k - 1];
                        int costRight = dp[k + 1][j];
                        if(costLeft != INT_MAX) currCost += costLeft;
                        if(costRight != INT_MAX) currCost += costRight;
                        minCost = min(minCost, currCost);
                    }

                    dp[i][j] = minCost;
                }
            }
        }

        // Return the result value
        return dp[1][m - 2];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Sorting
Link  : https://leetcode.com/problems/minimum-cost-to-cut-a-stick/
