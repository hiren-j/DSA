// Code to find the minimum possible height that the total bookshelf can be after placing shelves in this manner ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
DON'T IGNORE MUST READ: The (currentShelve) variable is assumed to indicate the shelve at which the books are being placed. 
                        Initially (currentShelve == 0) refers to the topmost shelve of the bookcase and then as the (currentShelve) increases 
                        imagine we're moving to the next shelve of the bookcase and so on.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the minimum possible height, using recursion with memoization - O(N*N) & O(N)
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();
        vector<int> memory(n, -1);
        return solveWithMemo(books, shelfWidth, n, 0, memory);
    }

private:   
    // O(N*N) & O(N+N)
    int solveWithMemo(vector<vector<int>>& books, int shelfWidth, int n, int currentShelve, vector<int>& memory) {
        // Edge case: If all the books are exhausted then you can't place any more to the bookcase
        if(currentShelve == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[currentShelve] != -1)
            return memory[currentShelve];

        int sumThickness = 0;       // Stores the thickness sum of books placed in the current shelve
        int maxHeight    = 0;       // Stores the maximum height of any book placed in the current shelve 
        int resultHeight = INT_MAX; // Stores the result value

        // Perform all the partitions of placing the books and update the result by the minimum value
        for(int book = currentShelve; book < n; ++book) {
            sumThickness += books[book][0];
            if(sumThickness > shelfWidth) {
                break;
            }
            maxHeight      = max(maxHeight, books[book][1]);
            int nextResult = solveWithMemo(books, shelfWidth, n, book + 1, memory);
            resultHeight   = min(resultHeight, nextResult + maxHeight);
        }

        // Store the result value to the memoization table and then return it
        return memory[currentShelve] = resultHeight;
    }

    // O(N^N) & O(N)
    int solveWithoutMemo(vector<vector<int>>& books, int shelfWidth, int n, int currentShelve) {
        // Edge case: If all the books are exhausted then you can't place any more to the bookcase
        if(currentShelve == n)
            return 0;

        int sumThickness = 0;       // Stores the thickness sum of books placed in the current shelve
        int maxHeight    = 0;       // Stores the maximum height of any book placed in the current shelve 
        int resultHeight = INT_MAX; // Stores the result value

        // Perform all the partitions of placing the books and update the result by the minimum value
        for(int book = currentShelve; book < n; ++book) {
            sumThickness += books[book][0];
            if(sumThickness > shelfWidth) {
                break;
            }
            maxHeight      = max(maxHeight, books[book][1]);
            int nextResult = solveWithoutMemo(books, shelfWidth, n, book + 1);
            resultHeight   = min(resultHeight, nextResult + maxHeight);
        }

        // Return the result value
        return resultHeight;
    }
};  

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the minimum possible height, using 1D tabulation - O(N*N) & O(N)
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();

        // 1D DP table
        vector<int> dp(n+1, INT_MAX);

        // Initialize the edge case: If all the books are exhausted then you can't place any more to the bookcase
        dp[n] = 0;

        // Fill the rest of the table
        for(int currentShelve = n-1; currentShelve >= 0; --currentShelve) {
            int sumThickness = 0, maxHeight = 0, resultHeight = INT_MAX;

            for(int book = currentShelve; book < n; ++book) {
                sumThickness += books[book][0];
                if(sumThickness > shelfWidth) {
                    break;
                }
                maxHeight      = max(maxHeight, books[book][1]);
                int nextResult = dp[book + 1];
                resultHeight   = min(resultHeight, nextResult + maxHeight);
            }

            dp[currentShelve] = resultHeight;
        }

        // Return the result value
        return dp[0];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/filling-bookcase-shelves/description/?envType=daily-question&envId=2024-07-31
