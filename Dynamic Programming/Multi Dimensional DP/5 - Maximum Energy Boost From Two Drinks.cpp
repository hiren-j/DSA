// Code to find the maximum total energy boost you can gain in the next n hours by following the specified instructions ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    typedef long long LL;
    int n;

    // O(2^N) & O(N)
    LL solveWithoutMemo(vector<int>& arr1, vector<int>& arr2, int idx, int useArr1) {
        // Edge case: If you've exhausted all the energy boosts then you can't gain more energy
        if(idx == n)
            return 0;

        LL maxEnergy = 0;
        
        // If its time to consume energyDrink A, then you've two options to perform on the energy boosts of it
        if(useArr1) {
            maxEnergy = arr1[idx] + solveWithoutMemo(arr1, arr2, idx + 1, 1);     // Is to drink it and then drink the next boost of energyDrink A
            maxEnergy = max(maxEnergy, solveWithoutMemo(arr1, arr2, idx + 1, 0)); // Is to make a switch to the next boost of energyDrink B
        }
        // Else, if its time to consume energyDrink B, then you've two options to perform on the energy boosts of it
        else {
            maxEnergy = arr2[idx] + solveWithoutMemo(arr1, arr2, idx + 1, 0);     // Is to drink it and then drink the next boost of energyDrink B
            maxEnergy = max(maxEnergy, solveWithoutMemo(arr1, arr2, idx + 1, 1)); // Is to make a switch to the next boost of energyDrink A
        }

        return maxEnergy;
    }

    // O(2 * N*2) & O(N*2 + N)
    LL solveWithMemo(vector<vector<LL>>& memory, vector<int>& arr1, vector<int>& arr2, int idx, int useArr1) {
        // Edge case: If you've exhausted all the energy boosts then you can't gain more energy
        if(idx == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[idx][useArr1] != -1)
            return memory[idx][useArr1];

        LL maxEnergy = 0;
        
        // If its time to consume energyDrink A, then you've two options to perform on the energy boosts of it
        if(useArr1) {
            maxEnergy = arr1[idx] + solveWithMemo(memory, arr1, arr2, idx + 1, 1);     // Is to drink it and then drink the next boost of energyDrink A
            maxEnergy = max(maxEnergy, solveWithMemo(memory, arr1, arr2, idx + 1, 0)); // Is to make a switch to the next boost of energyDrink B
        }
        // Else, if its time to consume energyDrink B, then you've two options to perform on the energy boosts of it
        else {
            maxEnergy = arr2[idx] + solveWithMemo(memory, arr1, arr2, idx + 1, 0);     // Is to drink it and then drink the next boost of energyDrink B
            maxEnergy = max(maxEnergy, solveWithMemo(memory, arr1, arr2, idx + 1, 1)); // Is to make a switch to the next boost of energyDrink A
        }

        // Store the result value to the memoization table and then return it
        return memory[idx][useArr1] = maxEnergy;
    }

public:
    // Method to find the maximum total energy boost you can gain, using recursion with memoization - O(N) & O(N)
    LL maxEnergyBoost(vector<int>& arr1, vector<int>& arr2) {
        n = arr1.size();
        vector<vector<LL>> memory1(n, vector<LL>(2, -1)), memory2(n, vector<LL>(2, -1));
        LL maxEnergy1 = solveWithMemo(memory1, arr1, arr2, 0, 1);
        LL maxEnergy2 = solveWithMemo(memory2, arr1, arr2, 0, 0);
        return max(maxEnergy1, maxEnergy2);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    typedef long long LL;
    int n;

    // O(N*2) & O(N*2)
    LL solveUsing2DTable(vector<int>& arr1, vector<int>& arr2, int idx, int useArr1) {
        // 2D DP table
        vector<vector<LL>> dp(n + 1, vector<LL>(2, 0));

        // Fill the table
        for(int idx = n-1; idx >= 0; --idx) {
            for(int col = (useArr1 == 1 ? 0 : 1); (useArr1 == 1 ? col <= 1 : col >= 0); (useArr1 == 1 ? col++ : col--)) {   
                LL maxEnergy = 0;

                if(col) {
                    maxEnergy = arr1[idx] + dp[idx + 1][1];
                    maxEnergy = max(maxEnergy, dp[idx + 1][0]);
                }
                else {
                    maxEnergy = arr2[idx] + dp[idx + 1][0];
                    maxEnergy = max(maxEnergy, dp[idx + 1][1]);
                }

                dp[idx][col] = maxEnergy;
            }   
        }

        // Return the result value
        return dp[0][useArr1];
    }

    // O(N*2) & O(1)
    LL solveUsing1DTable(vector<int>& arr1, vector<int>& arr2, int idx, int useArr1) {
        // 1D DP tables
        vector<LL> nextRow(2, 0), currRow(2, 0);

        // Fill the table
        for(int idx = n-1; idx >= 0; --idx) {
            for(int col = (useArr1 == 1 ? 0 : 1); (useArr1 == 1 ? col <= 1 : col >= 0); (useArr1 == 1 ? col++ : col--)) {   
                LL maxEnergy = 0;

                if(col) {
                    maxEnergy = arr1[idx] + nextRow[1];
                    maxEnergy = max(maxEnergy, nextRow[0]);
                }
                else {
                    maxEnergy = arr2[idx] + nextRow[0];
                    maxEnergy = max(maxEnergy, nextRow[1]);
                }

                currRow[col] = maxEnergy;
            }   
            nextRow = currRow;
        }

        // Return the result value
        return nextRow[useArr1];
    }

public:
    // Method to find the maximum total energy boost you can gain, using tabulation :-
    LL maxEnergyBoost(vector<int>& arr1, vector<int>& arr2) {
        n = arr1.size();
        LL maxEnergy1 = solveUsing1DTable(arr1, arr2, 0, 1);
        LL maxEnergy2 = solveUsing1DTable(arr1, arr2, 0, 0);
        return max(maxEnergy1, maxEnergy2);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/maximum-energy-boost-from-two-drinks/description/
