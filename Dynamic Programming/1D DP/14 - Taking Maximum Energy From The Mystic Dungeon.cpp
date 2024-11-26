// Code to find the maximum possible energy you can gain by performing the specified teleportation ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the maximum possible energy you can gain, using recursion with memoization - O(N) & O(N)
    int maximumEnergy(std::vector<int>& energy, int k) {
        int n = energy.size(), maxEnergy = INT_MIN;

        // 1D memoization table
        std::vector<int> memory(n, -1);
        
        // Gain the total energy you can get from each magician and update the result by the maximum value
        for(int magician = 0; magician < n; ++magician)
            maxEnergy = std::max(maxEnergy, energy[magician] + solveWithMemo(memory, energy, k, n, magician));
        
        // Return the maximum possible energy you can gain
        return maxEnergy;
    }
    
private:
    // O(N) & O(N+N)
    int solveWithMemo(std::vector<int>& memory, std::vector<int>& energy, int k, int n, int magician) {    
        // Edge case: If all the magicians are visited then you can't gain any more energy
        if(magician >= n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[magician] != -1)
            return memory[magician];
        
        // Stores the energy you can gain for the current magician
        int currEnergy = 0;
        
        // If it's possible to teleport to the kth magician then take the energy of the current magician and teleport to the kth magician
        if(magician + k < n)
            currEnergy += energy[magician + k] + solveWithMemo(memory, energy, k, n, magician + k);
        
        // Stores the result value to the memoization table and then return it
        return memory[magician] = currEnergy;
    }
    
    // O(N*N) & O(N)
    int solveWithoutMemo(std::vector<int>& energy, int k, int n, int magician) {    
        // Edge case: If all the magicians are visited then you can't gain any more energy
        if(magician >= n)
            return 0;
        
        // Stores the energy you can gain for the current magician
        int currEnergy = 0;
        
        // If it's possible to teleport to the kth magician then take the energy of the current magician and teleport to the kth magician
        if(magician + k < n)
            currEnergy += energy[magician + k] + solveWithoutMemo(energy, k, n, magician + k);
        
        // Return the result value
        return currEnergy;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V1 {
public:
    // Method to find the maximum possible energy you can gain, using 1D tabulation - O(N) & O(N) 
    int maximumEnergy(std::vector<int>& energy, int k) {
        int n = energy.size();

        // 1D table: dp[magician] represents the maximum possible energy you can gain for the individual magician
        std::vector<int> dp(n+1, 0);

        // Fill the table
        for(int magician = n-1; magician >= 0; --magician) {
            int currEnergy = 0;

            if(magician + k < n)
                currEnergy += energy[magician + k];
            if(magician + k <= n)
                currEnergy += dp[magician + k];

            dp[magician] = currEnergy;
        }

        // Stores the result value
        int maxEnergy = INT_MIN;

        // Iterate and update the result by the maximum value
        for(int magician = 0; magician < n; ++magician)
            maxEnergy = std::max(maxEnergy, energy[magician] + dp[magician]);
        
        // Return the result value
        return maxEnergy;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V2 {
public:
    // Method to find the maximum possible energy you can gain, using constant auxiliary space - O(N) & O(1)
    int maximumEnergy(std::vector<int>& energy, int k) {
        int n = energy.size();

        // Gain the total energy you can get for each magician from their corresponding kth magician
        for(int magician = n-k-1; magician >= 0; --magician)
            energy[magician] += energy[magician + k];

        // Return the maximum possible energy you can gain
        return *max_element(begin(energy), end(energy));
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Prefix Sum | Dynamic Programming
Link  : https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon/description/
