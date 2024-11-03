// Code to find the number of longest increasing subsequences. Notice that the sequence has to be strictly increasing ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the number of longest increasing subsequences, using 1D tabulation - O(N*N) & O(N)
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();

        vector<int> dp(n, 1);    // dp[index] represents the length of the LIS ending at that index
        vector<int> count(n, 1); // count[index] represents the count of the LIS ending at that index

        for(int index = 0; index < n; ++index) {
            for(int prevIndex = 0; prevIndex < index; ++prevIndex) {
                if(nums[prevIndex] < nums[index]) {
                    if(dp[prevIndex] + 1 == dp[index]) {
                        count[index] += count[prevIndex];
                    }
                    else if(dp[prevIndex] + 1 > dp[index]) {
                        dp[index]    = max(dp[index], 1 + dp[prevIndex]); 
                        count[index] = count[prevIndex];
                    }
                }
            }
        }

        int lengthOfLIS = *max_element(begin(dp), end(dp));
        int countOfLIS  = 0;

        // Iterate and count the total number of LIS
        for(int index = 0; index < n; ++index) {
            if(dp[index] == lengthOfLIS) {
                countOfLIS += count[index];
            }
        }

        return countOfLIS;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming 
Link  : https://leetcode.com/problems/number-of-longest-increasing-subsequence/description/
