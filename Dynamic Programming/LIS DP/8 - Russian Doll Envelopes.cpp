// Code to find the maximum number of envelopes you can Russian doll (i.e., put one inside the other). One envelope can fit into another if and only if both the width and height of one envelope are greater than the other envelope's width and height. You cannot rotate an envelope ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown_V1 {
public:
    // Method to find the maximum number of envelopes you can russian doll, using recursion with 2D memoization - O(N*N) & O(N*N)
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        sort(begin(envelopes), end(envelopes));
        vector<vector<int>> memory(n, vector<int>(n + 1, -1));
        return solveWithMemo(memory, envelopes, n, 0, -1);
    }

private:
    // O(2*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& envelopes, int n, int index, int prevIndex) {
        if(index == n)
            return 0;

        if(memory[index][prevIndex + 1] != -1)
            return memory[index][prevIndex + 1];

        int currSkip = solveWithMemo(memory, envelopes, n, index + 1, prevIndex);
        int currTake = 0;

        if(prevIndex == -1 || (envelopes[prevIndex][0] < envelopes[index][0] && envelopes[prevIndex][1] < envelopes[index][1]))
            currTake = 1 + solveWithMemo(memory, envelopes, n, index + 1, index);

        return memory[index][prevIndex + 1] = max(currSkip, currTake);
    }
    // Note: This solution can lead to the memory-limit exceed

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<vector<int>>& envelopes, int n, int index, int prevIndex) {
        if(index == n)
            return 0;

        int currSkip = solveWithoutMemo(envelopes, n, index + 1, prevIndex);
        int currTake = 0;

        if(prevIndex == -1 || (envelopes[prevIndex][0] < envelopes[index][0] && envelopes[prevIndex][1] < envelopes[index][1]))
            currTake = 1 + solveWithoutMemo(envelopes, n, index + 1, index);

        return max(currSkip, currTake);
    }
    // Note: This solution can lead to the time-limit exceed
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
class TopDown_V2 {
public:
    // Method to find the maximum number of envelopes you can russian doll, using recursion with 1D memoization - O(N*N) & O(N)
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        sort(begin(envelopes), end(envelopes));
        vector<int> memory(n + 1, -1);
        return solveWithMemo(memory, envelopes, n, 0, -1);
    }

private:
    // O(2*N*N) & O(N+N)
    int solveWithMemo(vector<int>& memory, vector<vector<int>>& envelopes, int n, int index, int prevIndex) {
        if(index == n)
            return 0;

        if(memory[prevIndex + 1] != -1)
            return memory[prevIndex + 1];

        int currSkip = solveWithMemo(memory, envelopes, n, index + 1, prevIndex);
        int currTake = 0;

        if(prevIndex == -1 || (envelopes[prevIndex][0] < envelopes[index][0] && envelopes[prevIndex][1] < envelopes[index][1]))
            currTake = 1 + solveWithMemo(memory, envelopes, n, index + 1, index);

        return memory[prevIndex + 1] = max(currSkip, currTake);
    }
};
// Note: This solution (TopDown_V2) is the space optimized version of the (TopDown_V1) solution. It can lead to the time-limit exceed

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V3 {
public:
    // Method to find the maximum number of envelopes you can russian doll, using recursion with 2D memoization - O(N^3) & O(N^2)
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        sort(begin(envelopes), end(envelopes));
        vector<vector<int>> memory(n, vector<int>(n + 1, -1));
        return solveWithMemo(memory, envelopes, n, 0, -1);
    }

private:
    // O(N*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& envelopes, int n, int startIndex, int prevIndex) {
        if(startIndex == n)
            return 0;

        if(memory[startIndex][prevIndex + 1] != -1)
            return memory[startIndex][prevIndex + 1];

        int maxEnvelopes = 0;

        for(int index = startIndex; index < n; ++index)
            if(prevIndex == -1 || (envelopes[prevIndex][0] < envelopes[index][0] && envelopes[prevIndex][1] < envelopes[index][1]))
                maxEnvelopes = max(maxEnvelopes, 1 + solveWithMemo(memory, envelopes, n, index + 1, index));

        return memory[startIndex][prevIndex + 1] = maxEnvelopes;
    }
    // Note: `solveWithoutMemo` function will have O(N^N) time complexity and O(N) auxiliary space. You can easily create it by removing the memoization from this `solveWithMemo`, which is straightforward to implement. The full function isn't provided here to avoid larger code
};
// Note: This solution (TopDown_V3) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V3). It can lead to the memory-limit exceed

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V1 {
public:
    // #1 Method to find the maximum number of envelopes you can russian doll, using 2D tabulation - O(N*N) & O(N*N)
    int maxEnvelopes_V1(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        sort(begin(envelopes), end(envelopes));

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for(int index = n-1; index >= 0; --index) {
            for(int prevIndex = n-1; prevIndex >= -1; --prevIndex) {
                int currSkip = dp[index + 1][prevIndex + 1];
                int currTake = 0;

                if(prevIndex == -1 || (envelopes[prevIndex][0] < envelopes[index][0] && envelopes[prevIndex][1] < envelopes[index][1]))
                    currTake = 1 + dp[index + 1][index + 1];

                dp[index][prevIndex + 1] = max(currSkip, currTake);
            }
        }

        return dp[0][0];
    }
    // Note: This bottom-up solution is created from the memoized solution of (TopDown_V1). It can lead to the memory-limit-exceed

    // #2 Method to find the maximum number of envelopes you can russian doll, using 1D tabulation - O(N*N) & O(N)
    int maxEnvelopes_V2(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        sort(begin(envelopes), end(envelopes));

        vector<int> nextRow(n + 1, 0), idealRow(n + 1, 0);

        for(int index = n-1; index >= 0; --index) {
            for(int prevIndex = n-1; prevIndex >= -1; --prevIndex) {
                int currSkip = nextRow[prevIndex + 1];
                int currTake = 0;

                if(prevIndex == -1 || (envelopes[prevIndex][0] < envelopes[index][0] && envelopes[prevIndex][1] < envelopes[index][1]))
                    currTake = 1 + nextRow[index + 1];

                idealRow[prevIndex + 1] = max(currSkip, currTake);
            }
            nextRow = idealRow;
        }

        return idealRow[0];
    }
    // Note: This solution can lead to the time-limit-exceed
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V2 {
public:
    // Method to find the maximum number of envelopes you can russian doll, using 1D tabulation - O(N*N) & O(N)
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size(), maxLength = 0;
        sort(begin(envelopes), end(envelopes));

        vector<int> dp(n, 1);

        for(int index = 0; index < n; ++index) {
            for(int prevIndex = 0; prevIndex < index; ++prevIndex) {
                if(envelopes[prevIndex][0] < envelopes[index][0] && envelopes[prevIndex][1] < envelopes[index][1]) {
                    dp[index] = max(dp[index], dp[prevIndex] + 1);
                }
            }
            maxLength = max(maxLength, dp[index]);
        }

        return maxLength;
    }
};
// Note: This solution can lead to the time-limit-exceed

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V3 {
    static bool comparator(vector<int>& nums1, vector<int>& nums2){
        // If widths are same then sort by height in descending order
        if(nums1[0] == nums2[0]) 
            return nums1[1] > nums2[1];  

        // Otherwise, sort by width in ascending order
        return nums1[0] < nums2[0];  
    }

public:
    // Method to find the maximum number of envelopes you can russian doll, using binary search - O(NLogN) & O(N)
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size(), maxLength = 1;  

        // Suppose you're placing envelopes in ascending order by width and then an upcoming envelope have the same width as the previously placed one. Now we want to put maximum envelopes in one another and if the height of this new envelope is greater then the previous one then you can easily put the previous one in it. So that's why when the widths are same then sorting by height in descending order is required 
        sort(begin(envelopes), end(envelopes), comparator);

        // This array doesn't necessarily store the values of the LIS in the correct order. This is due to updates made during the binary search. However, it will correctly provide the length of the actual LIS
        vector<int> LIS;
        LIS.push_back(envelopes[0][1]);

        for(auto& currEnvelope : envelopes) {
            if(LIS.back() < currEnvelope[1]) {
                LIS.push_back(currEnvelope[1]);
                maxLength++;
            }
            else {
                int i = lower_bound(begin(LIS), end(LIS), currEnvelope[1]) - begin(LIS);
                if(i >= 0 && i < maxLength) {
                    LIS[i] = currEnvelope[1];
                }
            }
        }

        // Return the length of the LIS
        return maxLength;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Binary Search | Dynamic Programming | Sorting
Link  : https://leetcode.com/problems/russian-doll-envelopes/description/
