// Code to find the number of teams you can form under the given conditions ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
public:
    // Method to find the number of teams you can form under the given conditions, using recursion with memoization - O(N^2) & O(N^2)
    int numTeams(vector<int>& rating) {
        n = rating.size();
        vector<vector<vector<int>>> memory1(n, vector<vector<int>>(n + 1, vector<int>(4, -1))), memory2(n, vector<vector<int>>(n + 1, vector<int>(4, -1)));
        int countIncreasingSubseqLen3 = solveWithMemo(memory1, rating, 3, 0, -1, true);
        int countDecreasingSubseqLen3 = solveWithMemo(memory2, rating, 3, 0, -1, false);
        return countIncreasingSubseqLen3 + countDecreasingSubseqLen3;
    }

private:
    int n;

    // O(2*N*N*4) & O(N*N*4 + N)
    int solveWithMemo(vector<vector<vector<int>>>& memory, vector<int>& rating, int k, int index, int prevIndex, bool toFindIncreasing) {
        // Edge case: If you've found a strictly increasing or decreasing subsequence of length 3 then return 1 
        if(k == 0)
            return 1;

        // Edge case: If all the values are exhausted then you can't pick any more
        if(index == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][prevIndex + 1][k] != -1)
            return memory[index][prevIndex + 1][k];

        // There are always two possibilities to perform at each index
        int currSkip = solveWithMemo(memory, rating, k, index + 1, prevIndex, toFindIncreasing); // Is to skip the index value 
        int currTake = 0;                                                                        // Is to pick the index value

        // If possible then take the index value
        if(prevIndex == -1 || (toFindIncreasing && rating[prevIndex] < rating[index]) || (!toFindIncreasing && rating[prevIndex] > rating[index])) 
            currTake = solveWithMemo(memory, rating, k - 1, index + 1, index, toFindIncreasing);

        // Store the result value to the memoization table and then return it
        return memory[index][prevIndex + 1][k] = (currSkip + currTake);
    }
    
    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& rating, int k, int index, int prevIndex, bool toFindIncreasing) {
        // Edge case: If you've found a strictly increasing or decreasing subsequence of length 3 then return 1 
        if(k == 0)
            return 1;

        // Edge case: If all the values are exhausted then you can't pick any more
        if(index == n)
            return 0;

        // There are always two possibilities to perform at each index
        int currSkip = solveWithoutMemo(rating, k, index + 1, prevIndex, toFindIncreasing); // Is to skip the value
        int currTake = 0;                                                                   // Is to pick the value

        // If possible then take the index value
        if(prevIndex == -1 || (toFindIncreasing && rating[prevIndex] < rating[index]) || (!toFindIncreasing && rating[prevIndex] > rating[index])) 
            currTake = solveWithoutMemo(rating, k - 1, index + 1, index, toFindIncreasing);

        // Return the result value
        return (currSkip + currTake);
    }
};
// Note: This solution can lead to the time-limit-exceed

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
public:
    // Method to find the number of teams you can form under the given conditions, using recursion with memoization - O(N^3) & O(N^2)
    int numTeams(vector<int>& rating) {
        n = rating.size();
        vector<vector<vector<int>>> memory1(n, vector<vector<int>>(n + 1, vector<int>(4, -1))), memory2(n, vector<vector<int>>(n + 1, vector<int>(4, -1)));
        int countIncreasingSubseqLen3 = solveWithMemo(memory1, rating, 3, 0, -1, true);
        int countDecreasingSubseqLen3 = solveWithMemo(memory2, rating, 3, 0, -1, false);
        return countIncreasingSubseqLen3 + countDecreasingSubseqLen3;
    }

private:
    int n;

    // O(N*N*N*4) & O(N*N*4 + N)
    int solveWithMemo(vector<vector<vector<int>>>& memory, vector<int>& rating, int k, int startIndex, int prevIndex, bool toFindIncreasing) {
        // Edge case: If you've found a strictly increasing or decreasing subsequence of length 3 then return 1 
        if(k == 0)
            return 1;

        // Edge case: If all the values are exhausted then you can't pick any more
        if(startIndex == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex][prevIndex + 1][k] != -1)
            return memory[startIndex][prevIndex + 1][k];

        // Stores the result value
        int count = 0;

        // Iterate and if possible then take the index value
        for(int index = startIndex; index < n; ++index)
            if(prevIndex == -1 || (toFindIncreasing && rating[prevIndex] < rating[index]) || (!toFindIncreasing && rating[prevIndex] > rating[index])) 
                count += solveWithMemo(memory, rating, k - 1, index + 1, index, toFindIncreasing);

        // Store the result value to the memoization table and then return it
        return memory[startIndex][prevIndex + 1][k] = count;
    }
    // Note: `solveWithoutMemo` function will have O(N^N) time complexity and O(N) auxiliary space. You can easily create it by removing the memoization from this `solveWithMemo`, which is straightforward to implement. The full function isn't provided here to avoid larger code
};
// Note: This solution (TopDown_V2) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V2). It will give time-limit-exceed

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the number of teams you can form under the given conditions, using 2D and 3D tabulation :-
    int numTeams(vector<int>& rating) {
        n = rating.size();
        int countIncreasingSubseqLen3 = solveUsing2DTable(rating, 3, true);
        int countDecreasingSubseqLen3 = solveUsing2DTable(rating, 3, false);
        return countIncreasingSubseqLen3 + countDecreasingSubseqLen3;
    }

private:
    int n;

    // O(N*N*3) & O(2*N*4)
    int solveUsing2DTable(vector<int>& rating, int k, bool toFindIncreasing) {
        // 2D DP tables
        vector<vector<int>> nextRow(n + 1, vector<int>(4, 0)), idealRow(n + 1, vector<int>(4, 0));
        
        // Initialize the first edge case: If you've found a strictly increasing or decreasing subsequence of length 3 then return 1
        for(int prevIndex = 0; prevIndex <= n; ++prevIndex)
            nextRow[prevIndex][0] = 1;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(int prevIndex = n-1; prevIndex >= -1; --prevIndex) {
                idealRow[prevIndex + 1][0] = 1;
                for(int k = 1; k <= 3; ++k) {
                    int currSkip = nextRow[prevIndex + 1][k];
                    int currTake = 0;
                    if(prevIndex == -1 || (toFindIncreasing && rating[prevIndex] < rating[index]) || (!toFindIncreasing && rating[prevIndex] > rating[index])) {
                        currTake = nextRow[index + 1][k - 1];
                    }
                    idealRow[prevIndex + 1][k] = (currSkip + currTake);
                }
            }
            nextRow = idealRow;
        }

        // Return the result value
        return idealRow[0][3];
    }

    // O(N*N*3) & O(N*N*4)
    int solveUsing3DTable(vector<int>& rating, int k, bool toFindIncreasing) {
        // 3D DP table
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1, vector<int>(4, 0)));

        // Initialize the first edge case: If you've found a strictly increasing or decreasing subsequence of length 3 then return 1
        for(int index = 0; index <= n; ++index)
            for(int prevIndex = 0; prevIndex <= n; ++prevIndex)
                dp[index][prevIndex][0] = 1;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(int prevIndex = n-1; prevIndex >= -1; --prevIndex) {
                for(int k = 1; k <= 3; ++k) {
                    int currSkip = dp[index + 1][prevIndex + 1][k];
                    int currTake = 0;
                    if(prevIndex == -1 || (toFindIncreasing && rating[prevIndex] < rating[index]) || (!toFindIncreasing && rating[prevIndex] > rating[index])) {
                        currTake = dp[index + 1][index + 1][k - 1];
                    }
                    dp[index][prevIndex + 1][k] = (currSkip + currTake);
                }
            }
        }

        // Return the result value
        return dp[0][0][3];
    }
    // Note: This solution can lead to the time-limit-exceed
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/count-number-of-teams/description/
