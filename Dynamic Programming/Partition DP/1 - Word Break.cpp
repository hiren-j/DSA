// Code to check whether given string can be segmented into a space-separated sequence of one or more dictionary words ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ: This Partition DP pattern is designed to help you understand different ways to partition an array or string to solve complex problems. The pattern contains a total of 14 problems:
    
        -> Problems 1 to 11: These problems involve making a single partition on the right side after reaching any point in the array or string. For example, consider an array [1, 2, 3]. If you choose index 1 as the partition point, you split the array into [1] and [2, 3]. 
                            You then solve the problem for the right side starting from index 2. In these problems, you are considering only one cut or one partition at a time.
    
        -> Problems 12 to 14: These problems involve making two cuts or two partitions simultaneously to cover multiple segments of the array or string. For example, with the array [1, 2, 3, 4, 5], if you make two cuts at indices 1 and 3, you divide the array into [1], [2, 3, 4], and [5]. 
                             Here, you are considering two cuts or two partitions at the same time to cover multiple segments.
    
        -> Difference: In problems 1 to 11, you only need to make one cut at a time to split the array or string into segments. In problems 12 to 14, you need to consider making two cuts simultaneously to define multiple segments. 
                       Understanding this difference is crucial for applying the correct strategy.
    
        -> If this distinction isn’t clear yet, don’t worry—solving the problems will help you grasp the concept better. This note is just to highlight the key differences.
*/

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    unordered_set<string> dictionary;
    int n;

    // O(N^N) & O(N+M)
    bool solveWithoutMemo(string& s, int startIndex) {
        // Edge case: If all the letters of the string are exhausted then return true
        if(startIndex == n)
            return true;

        string word;

        // Consider each letter into the word one by one and simultaneously check for it's existence in the dictionary. If it exists then consider a partition on that index and do the same from the next index
        for(int index = startIndex; index < n; ++index) {
            word += s[index];
            if(dictionary.count(word) && solveWithoutMemo(s, index + 1)) {
                return true;
            }
        }
        
        // If reached here then it's not possible for the string to become such sequence hence return false
        return false;
    }

    // O(N*N) & O(N+N+M)
    bool solveWithMemo(vector<int>& memory, string& s, int startIndex) {
        // Edge case: If all the letters of the string are exhausted then return true
        if(startIndex == n)
            return true;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex] != -1)
            return memory[startIndex];

        string word;

        // Consider each letter into the word one by one and simultaneously check for it's existence in the dictionary. If it exists then consider a partition on that index and do the same from the next index
        for(int index = startIndex; index < n; ++index) {
            word += s[index];
            if(dictionary.count(word) && solveWithMemo(memory, s, index + 1)) {
                return true;
            }
        }

        // Store the value to the memoization table and then return it
        return memory[startIndex] = false;
    }

public:
    // Method to check whether given string can be segmented into a space-separated sequence of one or more dictionary words, using recursion with memoization - O(N*N) & O(N+M) : Where M let be the size of "dictionary"
    bool wordBreak(string& s, vector<string>& wordDict) {
        n = s.size();
        for(auto& word : wordDict) dictionary.insert(word);
        vector<int> memory(n, -1);
        return solveWithMemo(memory, s, 0);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to check whether given string can be segmented into a space-separated sequence of one or more dictionary words, using 1D tabulation - O(N*N) & O(N+M)
    bool wordBreak(string& s, vector<string>& wordDict) {
        int n = s.size();

        unordered_set<string> dictionary(begin(wordDict), end(wordDict));

        // 1D DP table
        vector<bool> dp(n + 1, false);

        // Initialize the edge case: If all the letters of the string are exhausted then return true
        dp[n] = true;

        // Fill the rest of the table
        for(int startIndex = n-1; startIndex >= 0; --startIndex) {
            string word;
            for(int index = startIndex; index < n; ++index) {
                word += s[index];
                if(dictionary.count(word) && dp[index + 1]) {
                    dp[startIndex] = true;
                }
            }
        }

        // Return the result value
        return dp[0];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Array | Hash Table | String | Dynamic Programming | Memoization 
Link  : https://leetcode.com/problems/word-break/description/
