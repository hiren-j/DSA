// Code to partition the string "s" such that every substring of the partition is a palindrome and to find the minimum cuts needed for a palindrome partitioning of "s" ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the brute force approach:
class DP_V1 {
    // Method to check whether a string is a palindrome or not - O(N) & O(1)
    static bool isPalindrome(string& s, int start, int end) {
        while(start < end) {
            if(s[start] != s[end]) {
                return false;
            }
            start++; 
            end--;
        }
        return true;
    }

public:
    // Subclass to implement the Top-down approach:
    class TopDown {
        // O(N^3) & O(N+N)
        int solveWithMemo(vector<int>& memory, string& s, int n, int startIndex) {
            // Edge case: If all the elements are exhausted then you can't do more partitions
            if(startIndex == n) 
                return 0;

            // Memoization table: If the current state is already computed then return the computed value
            if(memory[startIndex] != -1)
                return memory[startIndex];

            // Stores the result value
            int minCuts = INT_MAX;
            
            // Perform all the palindrome partitions and update the result by the minimum value
            for(int index = startIndex; index < n; ++index) {
                if(isPalindrome(s, startIndex, index)) {
                    int nextCuts = solveWithMemo(memory, s, n, index + 1);
                    minCuts = (index != n-1 ? minCuts = min(minCuts, 1 + nextCuts) : nextCuts);
                }
            }

            // Store the result value to the memoization table and then return it
            return memory[startIndex] = minCuts;
        }

    public:
        // Method to find the minimum cuts needed for such palindrome partitioning, using recursion with memoization - O(N^3) & O(N)
        int minCut(string& s) {
            int n = s.size();
            vector<int> memory(n, -1);
            return solveWithMemo(memory, s, n, 0);
        }
    };

    // Subclass to implement the Bottom-up approach:
    class BottomUp {
    public:
        // Method to find the minimum cuts needed for such palindrome partitioning, using 1D tabulation - O(N^3) & O(N)
        int minCut(string& s) {
            int n = s.size();

            // 1D DP table
            vector<int> dp(n + 1, 0);

            // Fill the table
            for(int startIndex = n-1; startIndex >= 0; --startIndex) {
                int minCuts = INT_MAX;

                for(int index = startIndex; index < n; ++index) {
                    if(isPalindrome(s, startIndex, index)) {
                        int nextCuts = dp[index + 1];
                        minCuts = (index != n-1 ? minCuts = min(minCuts, 1 + nextCuts) : nextCuts);
                    }
                }
                
                dp[startIndex] = minCuts;
            }

            // Return the result value
            return dp[0];
        }
    };
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the optimized approach:
class DP_V2 {
    // Method to check whether a string is a palindrome or not, using recursion with memoization :-
    static bool isPalindrome(vector<vector<int>>& memory, const string& s, int start, int end) {
        // Edge case: If all the letters are equal then the string is a palindrome
        if(start >= end)
            return true;

        // Edge case: If both the letters are not same then the string is not a palindrome
        if(s[start] != s[end])
            return false;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[start][end] != -1)
            return memory[start][end];

        // Store the result value to the memoization table and then return it
        return memory[start][end] = isPalindrome(memory, s, start + 1, end - 1);
    }

public:
    // Subclass to implement the Top-down approach:
    class TopDown {
        // O(N^2 + N^2) & O(N^2 + N+N)
        int solveWithMemo(vector<vector<int>>& memory1, vector<int>& memory2, const string& s, int n, int startIndex) {
            // Edge case: If all the elements are exhausted then you can't do more partitions
            if(startIndex == n) 
                return 0;

            // Memoization table: If the current state is already computed then return the computed value
            if(memory2[startIndex] != -1)
                return memory2[startIndex];

            // Stores the result value
            int minCuts = INT_MAX;

            // Perform all the palindrome partitions and update the result by the minimum value
            for(int index = startIndex; index < n; ++index) {
                if(isPalindrome(memory1, s, startIndex, index)) {
                    int nextCuts = solveWithMemo(memory1, memory2, s, n, index + 1);
                    minCuts = (index != n-1 ? minCuts = min(minCuts, 1 + nextCuts) : nextCuts);
                }
            }

            // Store the result value to the memoization table and then return it
            return memory2[startIndex] = minCuts;
        }

    public:
        // Method to find the minimum cuts needed for such palindrome partitioning, using recursion with memoization - O(N^2) & O(N^2)
        int minCut(string& s) {
            int n = s.size();
            vector<vector<int>> memory1(n, vector<int>(n, -1));
            vector<int> memory2(n, -1);
            return solveWithMemo(memory1, memory2, s, n, 0);
        }
    };

    // Subclass to implement the Bottom-up approach:
    class BottomUp {
    public:
        // Method to find the minimum cuts needed for such palindrome partitioning, using 2D and 1D tabulation - O(N^2) & O(N^2)
        int minCut(string& s) {
            int n = s.size();
            
            // DP tables
            vector<vector<int>> dp1(n, vector<int>(n, -1));
            vector<int> dp2(n + 1, 0);

            // Fill the table
            for(int startIndex = n-1; startIndex >= 0; --startIndex) {
                int minCuts = INT_MAX;

                for(int index = startIndex; index < n; ++index) {
                    if(isPalindrome(dp1, s, startIndex, index)) {
                        int nextCuts = dp2[index + 1];
                        minCuts = (index != n-1 ? minCuts = min(minCuts, 1 + nextCuts) : nextCuts);
                    }
                }

                dp2[startIndex] = minCuts;
            }

            // Return the result value
            return dp2[0];
        }
    };
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Link  : https://leetcode.com/problems/palindrome-partitioning-ii/description/
