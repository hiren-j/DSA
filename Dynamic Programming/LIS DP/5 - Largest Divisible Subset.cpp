// Code to find the largest subset answer such that every pair (answer[i], answer[j]) of elements in this subset satisfies: answer[i] % answer[j] == 0, or answer[j] % answer[i] == 0 ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the largest divisible subset, using 1D tabulation - O(N*N) & O(N)
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        sort(begin(nums), end(nums));
        
        vector<int> dp(n, 1);    // dp[index] represents the length of the LDS ending at that index 
        vector<int> temp(n, -1); // temp[index] represents the index of the recently seen value which is considered as the part of the LDS ending at that index
        
        // Find the length of the LDS ending at each index
        for(int index = 0; index < n; ++index) {
            temp[index] = index;
            for(int prevIndex = 0; prevIndex < index; ++prevIndex) {
                if(nums[index] % nums[prevIndex] == 0) {
                    if(1 + dp[prevIndex] > dp[index]) {
                        dp[index]   = 1 + dp[prevIndex];
                        temp[index] = prevIndex;
                    }
                }
            }
        }
        
        int resultIndex = -1; // Stores the index of the value which has to be taken (result value)
        int lengthLDS   = -1; // Stores the length of the LDS
        
        // Find the length of the LDS
        for(int index = 0; index < n; ++index) {
            if(dp[index] > lengthLDS) {
                lengthLDS = dp[index];
                resultIndex = index;
            }
        }
            
        // Stores the result values
        vector<int> LDS;

        // Iterate and store the result values
        while(resultIndex != temp[resultIndex]) {
            LDS.push_back(nums[resultIndex]);
            resultIndex = temp[resultIndex];
        }
        LDS.push_back(nums[resultIndex]);
        
        // Reverse the result array to get the actual order
        reverse(begin(LDS), end(LDS));

         // Return the result array
        return LDS;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/largest-divisible-subset/description/
