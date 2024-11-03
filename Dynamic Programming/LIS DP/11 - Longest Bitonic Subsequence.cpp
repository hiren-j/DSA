// Code to find the length of the longest bitonic subsequence. A subsequence of array is called Bitonic if it is first strictly increasing, then strictly decreasing. A strictly increasing or a strictly decreasing sequence should not be considered as a bitonic sequence ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the length of the longest bitonic subsequence, using 1D tabulation - O(N*N) & O(N)
    int LongestBitonicSequence(int n, vector<int>& nums) {
        vector<int> LIS(n, 1); // LIS[index] represents the length of the LIS ending at that index
        vector<int> LDS(n, 1); // LDS[index] represents the length of the LDS ending at that index
        
        // Compute the length of the LIS of each index
        for(int index = 0; index < n; ++index) 
            for(int prevIndex = 0; prevIndex < index; ++prevIndex) 
                if(nums[prevIndex] < nums[index]) 
                    LIS[index] = max(LIS[index], 1 + LIS[prevIndex]);
                    
        // Compute the length of the LDS of each index
        for(int index = n-1; index >= 0; --index) 
            for(int nextIndex = n-1; nextIndex > index; --nextIndex) 
                if(nums[index] > nums[nextIndex]) 
                    LDS[index] = max(LDS[index], 1 + LDS[nextIndex]);
                    
        int maxLenBitonic = 0;
        
        for(int index = 0; index < n; ++index) {
            int lenLIS = LIS[index];
            int lenLDS = LDS[index];
            // If both types of subsequence exists then update the result value by the maximum length
            if(lenLIS > 1 && lenLDS > 1) {
                maxLenBitonic = max(maxLenBitonic, lenLIS + lenLDS - 1);
            }
        }
        
        return maxLenBitonic;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/longest-bitonic-subsequence0824/1
