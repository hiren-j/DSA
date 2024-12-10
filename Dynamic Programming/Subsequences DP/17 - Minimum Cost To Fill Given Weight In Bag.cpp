// Code to find the minimum cost to buy exactly W kg of oranges. The cost array has a 1-based indexing. If buying exactly W kg of oranges is impossible then return -1 ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
public:
    // Method to find the minimum cost, using recursion with memoization - O(N*W) & O(N*W)
    int minimumCost(int N, int W, vector<int>& cost) {
        vector<vector<int>> memory(N + 1, vector<int>(W + 1, -1));
        int minCost = solveWithMemo(memory, cost, N, 1, W);
        return (minCost == INT_MAX) ? -1 : minCost;
    }
    
private:
    // O(2*N*W) & O(N*W + W)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& cost, int N, int KG, int W) {
        // Edge case: If W becomes zero then you have bought W kgs of oranges hence return 0 as a valid indication of it
        if(W == 0)
            return 0;
        
        // Edge case: If all the packets are exhausted then you can't buy any more kgs of oranges
        if(KG == N + 1)
            return INT_MAX;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[KG][W] != -1)
            return memory[KG][W];
            
        // There are always two possibilities to perform at each packet of oranges
        int currSkip = solveWithMemo(memory, cost, N, KG + 1, W); // Is to skip the kg packet
        int currBuy  = INT_MAX;                                   // Is to buy the kg packet
        
        // If the kg packet is availaible then buy the packet
        if(cost[KG - 1] != -1 && KG <= W) {
            int nextCost = solveWithMemo(memory, cost, N, KG, W - KG);
            currBuy = (nextCost != INT_MAX) ? cost[KG - 1] + nextCost : INT_MAX;
        }

        // Store the result value to the memoization table and then return it
        return memory[KG][W] = min(currSkip, currBuy);
    }

    // O(2^W) & O(W)
    int solveWithoutMemo(vector<int>& cost, int N, int KG, int W) {
        // Edge case: If W becomes zero then you have bought W kgs of oranges hence return 0 as a valid indication of it
        if(W == 0)
            return 0;
        
        // Edge case: If all the packets are exhausted then you can't buy any more kgs of oranges
        if(KG == N + 1)
            return INT_MAX;
                    
        // There are always two possibilities to perform at each packet of oranges
        int currSkip = solveWithoutMemo(cost, N, KG + 1, W); // Is to skip the kg packet
        int currBuy  = INT_MAX;                              // Is to buy the kg packet
        
        // If the kg packet is availaible then buy the packet
        if(cost[KG - 1] != -1 && KG <= W) {
            int nextCost = solveWithoutMemo(cost, N, KG, W - KG);
            currBuy = (nextCost != INT_MAX) ? cost[KG - 1] + nextCost : INT_MAX;
        }

        // As we're striving for the minimum cost hence return the minimum value
        return min(currSkip, currBuy);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
public:
    // Method to find the minimum cost, using recursion with memoization - O(N*N*W) & O(N*W)
    int minimumCost(int N, int W, vector<int>& cost) {
        vector<vector<int>> memory(N + 1, vector<int>(W + 1, -1));
        int minCost = solveWithMemo(memory, cost, N, 1, W);
        return (minCost == INT_MAX) ? -1 : minCost;
    }

private:
    // O(N*N*W) & O(N*W + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& cost, int N, int startIndex, int W) {
        // Edge case: If W becomes zero then you have bought weight kgs of oranges hence return 0 as a valid indication of it
        if(W == 0)
            return 0;
            
        // Edge case: If all the packets are exhausted then you can't buy any more kgs of oranges
        if(startIndex == N + 1)
            return INT_MAX;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex][W] != -1)
            return memory[startIndex][W];

        // Stores the result value
        int minCost = INT_MAX;

        // Iterate and if the kg packet is availaible then buy the packet
        for(int KG = startIndex; KG <= N; ++KG) {
            if(cost[KG - 1] != -1 && KG <= W) {
                int nextCost = solveWithMemo(memory, cost, N, KG, W - KG);
                if(nextCost != INT_MAX) {
                    minCost = min(minCost, nextCost + cost[KG - 1]);
                }
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[startIndex][W] = minCost;
    }
    
    // O(N^W) & O(N)
    int solveWithoutMemo(vector<int>& cost, int N, int startIndex, int W) {
        // Edge case: If W becomes zero then you have bought weight kgs of oranges hence return 0 as a valid indication of it
        if(W == 0)
            return 0;
            
        // Edge case: If all the packets are exhausted then you can't buy any more kgs of oranges
        if(startIndex == N + 1)
            return INT_MAX;

        // Stores the result value
        int minCost = INT_MAX;

        // Iterate and if the kg packet is availaible then buy the packet
        for(int KG = startIndex; KG <= N; ++KG) {
            if(cost[KG - 1] != -1 && KG <= W) {
                int nextCost = solveWithoutMemo(cost, N, KG, W - KG);
                if(nextCost != INT_MAX) {
                    minCost = min(minCost, nextCost + cost[KG - 1]);
                }
            }
        }

        // Return the result value
        return minCost;
    }
};
// Note: This solution (TopDown_V2) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V2)

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the minimum cost, using 2D tabulation - O(N*W) & O(N*W)
    int minimumCost_V1(int N, int W, vector<int>& cost) {
        // 2D DP table
        vector<vector<int>> dp(N + 2, vector<int>(W + 1, INT_MAX));

        // Initialize the first edge case: If W becomes zero then you have bought W kgs of oranges hence return 0 as a valid indication of it
        for(int KG = 0; KG <= N + 1; ++KG)
            dp[KG][0] = 0;

        // Fill the rest of the table
        for(int KG = N; KG >= 1; --KG) {
            for(int weight = 1; weight <= W; ++weight) {
                int currSkip = dp[KG + 1][weight];
                int currBuy  = INT_MAX;
                if(cost[KG - 1] != -1 && KG <= weight) {
                    int nextCost = dp[KG][weight - KG];
                    currBuy = (nextCost != INT_MAX) ? cost[KG - 1] + nextCost : INT_MAX;
                }
                dp[KG][weight] = min(currSkip, currBuy);
            }
        }   

        // Return the result value
        return (dp[1][W] == INT_MAX) ? -1 : dp[1][W];
    }

    // #2 Method to find the minimum cost, using 1D tabulation - O(N*W) & O(W)
    int minimumCost_V2(int N, int W, vector<int>& cost) {
        // 1D DP tables
        vector<int> nextRow(W + 1, INT_MAX), idealRow(W + 1, INT_MAX);
        nextRow[0] = 0;

        // Fill the rest of the table
        for(int KG = N; KG >= 1; --KG) {
            idealRow[0] = 0;
            for(int weight = 1; weight <= W; ++weight) {
                int currSkip = nextRow[weight];
                int currBuy  = INT_MAX;
                if(cost[KG - 1] != -1 && KG <= weight) {
                    int nextCost = idealRow[weight - KG];
                    currBuy = (nextCost != INT_MAX) ? cost[KG - 1] + nextCost : INT_MAX;
                }
                idealRow[weight] = min(currSkip, currBuy);
            }
            nextRow = idealRow;
        }

        // Return the result value
        return (nextRow[W] == INT_MAX) ? -1 : nextRow[W];
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/minimum-cost-to-fill-given-weight-in-a-bag1956/1?page=3&difficulty%5B%5D=1&category%5B%5D=Dynamic%2520Programming&sortBy=submissions*/
