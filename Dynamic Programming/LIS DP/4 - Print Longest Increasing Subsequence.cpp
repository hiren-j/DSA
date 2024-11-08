// Code to find the longest increasing subsequence of the given array ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the longest increasing subsequence, using 1D tabulation - O(N*N) & O(N) 
    vector<int> getLIS(vector<int>& nums) {
        int n = nums.size();

        vector<int> dp(n, 1);    // dp[index] represents the length of the LIS ending at that index 
        vector<int> temp(n, -1); // temp[index] represents the index of the recently seen value which is considered as the part of the LIS ending at that index

        // Find the length of the LIS ending at each index
        for(int index = 0; index < n; ++index) {   
            temp[index] = index;
            for(int prevIndex = 0; prevIndex < index; ++prevIndex) {
                if(nums[prevIndex] < nums[index] && 1 + dp[prevIndex] > dp[index]) {
                    dp[index]   = max(dp[index], 1 + dp[prevIndex]);
                    temp[index] = prevIndex;
                }
            }
        }

        int resultIndex = -1; // Stores the index of the value which has to be taken (result value)
        int maxLength   = -1; // Stores the length of the LIS

        // Find the length of the LIS 
        for(int index = 0; index < n; ++index) {
            if(dp[index] > maxLength) {
                maxLength   = dp[index];
                resultIndex = index;
            }
        }

        // Stores the result values
        vector<int> LIS;

        // Iterate and store the result values
        while(resultIndex != temp[resultIndex]) {
            LIS.push_back(nums[resultIndex]);
            resultIndex = temp[resultIndex];
        }
        LIS.push_back(nums[resultIndex]);

        // Reverse the result array to get the actual order
        reverse(begin(LIS), end(LIS));
        
        // Return the result array
        return LIS;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/printing-longest-increasing-subsequence/1
