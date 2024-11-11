// Code to find the length of the longest possible word chain with words chosen from the given list of words ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*

    DON'T IGNORE MUST READ: In the previous LIS problems, we implemented loop conversion, and we could do the same here. However, the Lines of Code (LOC) for this solution are already quite large, 
                            so I’m not including the loop-based recursive solution this time. By now, you likely understand the concept, so you can try it on your own if needed.
                            
*/
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown_V1 {
public:
    // Method to find the length of the longest word chain, using recursion with 2D memoization - O(N*N) & O(N*N)
    int longestStrChain(vector<string>& words) {
        int n = words.size();
        sort(begin(words), end(words), comparator);
        vector<vector<int>> memory(n, vector<int>(n + 1, -1));
        return solveWithMemo(memory, words, n, 0, -1);
    }

private:
    // O(2*N*N*32) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<string>& words, int n, int index, int prevIndex) {
        // Edge case: If all the values are exhausted then you can't take any more
        if(index == n)
            return 0;

        // Memoization table: If the current state is already computed then returh the computed value
        if(memory[index][prevIndex + 1] != -1)
            return memory[index][prevIndex + 1];

        // There are always two possibilities to perform at each index
        int currSkip = solveWithMemo(memory, words, n, index + 1, prevIndex); // Is to skip the index value
        int currTake = 0;                                                     // Is to take the index value   

        // If the previous word is the predecessor of the current word then take the index value 
        if(prevIndex == -1 || isPredecessor(words[prevIndex], words[index])) 
            currTake = 1 + solveWithMemo(memory, words, n, index + 1, index);

        // Store the result value to the memoization table and then return it
        return memory[index][prevIndex + 1] = max(currSkip, currTake);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<string>& words, int n, int index, int prevIndex) {
        // Edge case: If all the values are exhausted then you can't take any more
        if(index == n)
            return 0;

        // There are always two possibilities to perform at each index
        int currSkip = solveWithoutMemo(words, n, index + 1, prevIndex); // Is to skip the index value
        int currTake = 0;                                                // Is to take the index value   

        // If the previous word is the predecessor of the current word then take the index value 
        if(prevIndex == -1 || isPredecessor(words[prevIndex], words[index])) 
            currTake = 1 + solveWithoutMemo(words, n, index + 1, index);

        // As we're striving for the longest length hence return the maximum value
        return max(currSkip, currTake);
    }

private:
    // Method to check wheather the word1 is a predecessor of word2 - O(16+16) & O(1) : In the worst case 16 could be the maximum possible length of any word
    bool isPredecessor(const string& word1, const string& word2) {
        int n = word1.size(), m = word2.size();

        // Early exit: If the length of word1 doesn't satisfy the condition of being a predecessor then return false
        if(n != m - 1)
            return false;

        int i = 0, j = 0;

        // Iterate and check all the letters of word1 are present in word2
        while(i < n && j < m) {
            if(word1[i] == word2[j]) 
                i++;
            j++;
        }

        // If word1 is exhausted then return true 
        return i == n;
    }

    // Method to choose the word based on the shorter length - O(1) & O(1)
    static bool comparator(const string& word1, const string& word2) {
        return word1.size() < word2.size();
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
public:
    // Method to find the length of the longest word chain, using recursion with 1D memoization - O(N*N) & O(N)
    int longestStrChain(vector<string>& words) {
        int n = words.size();
        sort(begin(words), end(words), comparator);
        vector<int> memory(n + 1, -1);
        return solveWithMemo(memory, words, n, 0, -1);
    }

private:
    // O(2*N*N*32) & O(N+N)
    int solveWithMemo(vector<int>& memory, vector<string>& words, int n, int index, int prevIndex) {
        // Edge case: If all the values are exhausted then you can't take any more
        if(index == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[prevIndex + 1] != -1)
            return memory[prevIndex + 1];

        // There are always two possibilities to perform at each index
        int currSkip = solveWithMemo(memory, words, n, index + 1, prevIndex); // Is to skip the index value
        int currTake = 0;                                                     // Is to take the index value

        // If the previous word is the predecessor of the current word then take the index value 
        if(prevIndex == -1 || isPredecessor(words[prevIndex], words[index])) 
            currTake = 1 + solveWithMemo(memory, words, n, index + 1, index);

        // Stores the result value to the memoization table and then return it
        return memory[prevIndex + 1] = max(currSkip, currTake);
    }
    
private:
    // Method to check wheather the word1 is a predecessor of word2 - O(16+16) & O(1) : In the worst case 16 could be the maximum possible length of any word
    bool isPredecessor(const string& word1, const string& word2) {
        int n = word1.size(), m = word2.size();

        // Early exit: If the length of word1 doesn't satisfy the condition of being a predecessor then return false
        if(n != m - 1)
            return false;

        int i = 0, j = 0;

        // Iterate and check all the letters of word1 are present in word2
        while(i < n && j < m) {
            if(word1[i] == word2[j]) 
                i++;
            j++;
        }

        // If word1 is exhausted then return true 
        return i == n;
    }

    // Method to choose the word based on the shorter length - O(1) & O(1)
    static bool comparator(const string& word1, const string& word2) {
        return word1.size() < word2.size();
    }
};
// Note: This solution (TopDown_V2) is the space optimized version of the (TopDown_V1) solution

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the length of the longest word chain, using 2D tabulation - O(N*N*32) & O(N*N)
    int longestStrChain_V1(vector<string>& words) {
        int n = words.size();
        sort(begin(words), end(words), comparator);

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for(int index = n-1; index >= 0; --index) {
            for(int prevIndex = n-1; prevIndex >= -1; --prevIndex) {
                int currSkip = dp[index + 1][prevIndex + 1];
                int currTake = 0;
                if(prevIndex == -1 || isPredecessor(words[prevIndex], words[index])) {
                    currTake = 1 + dp[index + 1][index + 1];
                }
                dp[index][prevIndex + 1] = max(currSkip, currTake);
            }
        }

        return dp[0][0];
    }
    // Note: This bottom-up solution is created from the memoized solution of (TopDown_V1)
    
    // #2 Method to find the length of the longest word chain, using 1D tabulation - O(N*N*32) & O(N)
    int longestStrChain_V2(vector<string>& words) {
        int n = words.size();
        sort(begin(words), end(words), comparator);

        vector<int> nextRow(n + 1), idealRow(n + 1);

        for(int index = n-1; index >= 0; --index) {
            for(int prevIndex = n-1; prevIndex >= -1; --prevIndex) {
                int currSkip = nextRow[prevIndex + 1];
                int currTake = 0;
                if(prevIndex == -1 || isPredecessor(words[prevIndex], words[index])) {
                    currTake = 1 + nextRow[index + 1];
                }
                idealRow[prevIndex + 1] = max(currSkip, currTake);
            }
            nextRow = idealRow;
        }

        return idealRow[0];
    }

private:
    // Method to check wheather the word1 is a predecessor of word2 - O(16+16) & O(1) : In the worst case 16 could be the maximum possible length of any word
    bool isPredecessor(const string& word1, const string& word2) {
        int n = word1.size(), m = word2.size();

        // Early exit: If the length of word1 doesn't satisfy the condition of being a predecessor then return false
        if(n != m - 1)
            return false;

        int i = 0, j = 0;

        // Iterate and check all the letters of word1 are present in word2
        while(i < n && j < m) {
            if(word1[i] == word2[j]) 
                i++;
            j++;
        }

        // If word1 is exhausted then return true 
        return i == n;
    }

    // Method to choose the word based on the shorter length - O(1) & O(1)
    static bool comparator(const string& word1, const string& word2) {
        return word1.size() < word2.size();
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Hash Table | Two Pointers | String | Dynamic Programming | Sorting 
Link  : https://leetcode.com/problems/longest-string-chain/description/
