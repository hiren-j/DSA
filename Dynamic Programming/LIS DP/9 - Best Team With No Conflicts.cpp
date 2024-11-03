// Code to find the highest overall score of all possible basketball teams. You are the manager of a basketball team. For the upcoming tournament, you want to choose the team with the highest overall score. The score of the team is the sum of scores of all the players in the team. However, the basketball team is not allowed to have conflicts. A conflict exists if a younger player has a strictly higher score than an older player. A conflict does not occur between players of the same age ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
    vector<pair<int, int>> players;

    // O(2^N) & O(N+N)
    int solveWithoutMemo(int n, int index, int prevIndex) {
        // Edge case: If all the players are choosen then you can't choose more
        if(index == n)
            return 0;

        // There are always two possbilities to perform at each index value
        int currSkip = solveWithoutMemo(n, index + 1, prevIndex); // Is to skip it 
        int currTake = 0;                                         // Is to choose it  

        // If there's no conflict between young and the older player then you can choose the older player
        if(prevIndex == -1 || players[prevIndex].second <= players[index].second)
            currTake = players[index].second + solveWithoutMemo(n, index + 1, index);

        // As we're striving for the highest score hence return the maximum value
        return max(currSkip, currTake); 
    }

    // O(2*N*N) & O(N*N + N+N)
    int solveWithMemo(vector<vector<int>>& memory, int n, int index, int prevIndex) {
        // Edge case: If all the players are choosen then you can't choose more
        if(index == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][prevIndex + 1] != -1)
            return memory[index][prevIndex + 1];

        // There are always two possbilities to perform at each index value
        int currSkip = solveWithMemo(memory, n, index + 1, prevIndex); // Is to skip it 
        int currTake = 0;                                              // Is to choose it  

        // If there's no conflict between young and the older player then you can choose the older player
        if(prevIndex == -1 || players[prevIndex].second <= players[index].second)
            currTake = players[index].second + solveWithMemo(memory, n, index + 1, index);

        // Store the result value to the memoization table and then return it
        return memory[index][prevIndex + 1] = max(currSkip, currTake); 
    }

public:
    // Method to find the highest overall score of all possible basketball teams, using recursion with 2D memoization - O(N^2) & O(N^2)
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();

        // Create the list of players mapped with their age and score information
        for(int index = 0; index < n; ++index) {
            players.push_back({ages[index], scores[index]});
        }
        sort(begin(players), end(players));

        // 2D memoization table
        vector<vector<int>> memory(n, vector<int>(n + 1, -1));

        // Find and return the result value
        return solveWithMemo(memory, n, 0, -1);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
    vector<pair<int, int>> players;

    // O(2*N*N) & O(N+N+N)
    int solveWithMemo(vector<int>& memory, int n, int index, int prevIndex) {
        // Edge case: If all the players are choosen then you can't choose more 
        if(index == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[prevIndex + 1] != -1)
            return memory[prevIndex + 1];

        // There are always two possibilities to perform at each index value
        int currSkip = solveWithMemo(memory, n, index + 1, prevIndex); // Is to skip it
        int currTake = 0;                                              // Is to choose it

        // If there's no conflict between young and the older player then you can choose the older player
        if(prevIndex == -1 || players[prevIndex].second <= players[index].second)
            currTake = players[index].second + solveWithMemo(memory, n, index + 1, index);

        // Store the result value to the memoization table and then return it
        return memory[prevIndex + 1] = max(currSkip, currTake); 
    }

public:
    // Method to find the highest overall score of all possible basketball teams, using recursion with 1D memoization - O(N^2) & O(N)
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();

        // Create the list of players mapped with their age and score information
        for(int index = 0; index < n; ++index) {
            players.push_back({ages[index], scores[index]});
        }
        sort(begin(players), end(players));

        // 1D memoization table
        vector<int> memory(n + 1, -1);

        // Find and return the result value
        return solveWithMemo(memory, n, 0, -1);
    }
};
// Note: This solution (TopDown_V2) is the space optimized version of the (TopDown_V1) solution

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V3 {
    vector<pair<int, int>> players;

    // O(N*N*N) & O(N*N + N+N)
    int solveWithMemo(vector<vector<int>>& memory, int n, int startIndex, int prevIndex) {
        // Edge case: If all the players are choosen then you can't choose more
        if(startIndex == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex][prevIndex + 1] != -1)
            return memory[startIndex][prevIndex + 1];

        int maxScore = 0;

        // Iterate and if there's no conflict between young and the older player then you can choose the older player. Make sure to update the result by the maximum value 
        for(int index = startIndex; index < n; ++index)
            if(prevIndex == -1 || players[prevIndex].second <= players[index].second)
                maxScore = max(maxScore, players[index].second + solveWithMemo(memory, n, index + 1, index));

        return memory[startIndex][prevIndex + 1] = maxScore; 
    }
    // Note: `solveWithoutMemo` function will have O(N^N) time complexity and O(N+N) auxiliary space. You can easily create it by removing the memoization from this `solveWithMemo`, which is straightforward to implement. The full function isn't provided here to avoid larger code

public:
    // Method to find the highest overall score of all possible basketball teams, using recursion with 2D memoization - O(N^3) & O(N^2)
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();

        // Create the list of players mapped with their age and score information
        for(int index = 0; index < n; ++index) {
            players.push_back({ages[index], scores[index]});
        }
        sort(begin(players), end(players));

        // 2D memoization table
        vector<vector<int>> memory(n, vector<int>(n + 1, -1));

        // Find and return the result value
        return solveWithMemo(memory, n, 0, -1);
    }
};
// Note: This solution (TopDown_V3) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V3)

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V1 {
public:
    // #1 Method to find the highest overall score of all possible basketball teams, using 2D tabulation - O(N^2) & O(N^2)
    int bestTeamScore_V1(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();

        // Create the list of players mapped with their age and score information
        vector<pair<int, int>> players;
        for(int index = 0; index < n; ++index) {
            players.push_back({ages[index], scores[index]});
        }
        sort(begin(players), end(players));

        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        // Fill the table
        for(int index = n-1; index >= 0; --index) {
            for(int prevIndex = n-1; prevIndex >= -1; --prevIndex) {
                int currSkip = dp[index + 1][prevIndex + 1];
                int currTake = 0;
                if(prevIndex == -1 || players[prevIndex].second <= players[index].second) {
                    currTake = players[index].second + dp[index + 1][index + 1];
                }
                dp[index][prevIndex + 1] = max(currSkip, currTake); 
            }
        }

        // Return the result value
        return dp[0][0];
    }

    // #2 Method to find the highest overall score of all possible basketball teams, using 1D tabulation - O(N^2) & O(N)
    int bestTeamScore_V2(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();

        // Create the list of players mapped with their age and score information
        vector<pair<int, int>> players;
        for(int index = 0; index < n; ++index) {
            players.push_back({ages[index], scores[index]});
        }
        sort(begin(players), end(players));

        // 1D DP tables
        vector<int> nextRow(n + 1, 0), idealRow(n + 1, 0);

        // Fill the table
        for(int index = n-1; index >= 0; --index) {
            for(int prevIndex = n-1; prevIndex >= -1; --prevIndex) {
                int currSkip = nextRow[prevIndex + 1];
                int currTake = 0;
                if(prevIndex == -1 || players[prevIndex].second <= players[index].second) {
                    currTake = players[index].second + nextRow[index + 1];
                }
                idealRow[prevIndex + 1] = max(currSkip, currTake); 
            }
            nextRow = idealRow;
        }

        // Return the result value
        return idealRow[0];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V2 {
public:
    // Method to find the highest overall score of all possible basketball teams, using 1D tabulation - O(N^2) & O(N)
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size(), maxScore = 0;

        // Create the list of players mapped with their age and score information
        vector<pair<int, int>> players;
        for(int index = 0; index < n; ++index) {
            players.push_back({ages[index], scores[index]});
        }
        sort(begin(players), end(players));

        // 1D DP table: dp[i] represents the maximum score you can get by considering the players from index 0 to i
        vector<int> dp(n, 0);

        // Fill the table
        for(int index = 0; index < n; ++index) {
            dp[index] = players[index].second;
            for(int prevIndex = 0; prevIndex < index; ++prevIndex) {
                if(players[prevIndex].second <= players[index].second) {
                    dp[index] = max(dp[index], players[index].second + dp[prevIndex]);
                }
            }
            maxScore = max(maxScore, dp[index]);
        } 

        // Return the result value
        return maxScore;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Sorting
Link  : https://leetcode.com/problems/best-team-with-no-conflicts/description/
