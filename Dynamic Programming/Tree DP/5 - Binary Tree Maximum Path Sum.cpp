// Code to find the maximum path sum of any non-empty path. A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root. The path sum of a path is the sum of the node's values in the path ~ coded by Hiren 

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ:

        `solveWithoutMemo` - Time complexity: O(N*N) 
                             Explanation: The total number of nodes is N and for each node we're calling the `solveWithoutMemo` function so the overall time complexity is O(N*N),
                                          where the `solveWithoutMemo` auxiliary time is O(N) its because the `solveWithoutMemo` is visiting all the nodes in the recursion.
                            
                           - Auxiliary space : O(N*3 + N)
                             Explanation: The first N*3 represents the overall space taken by the adjacency list. It's because for any node there can be at most 3 neighbours, its because we're dealing with a binary tree. 
                                          So as we're storing neighbours of each node thus the total space taken by the adjacency list is N*3.
                                          The second term N represents the maximum depth of the recursion stack.

        `solveWithMemo` - Time complexity: O(NLogN) 
                          Explanation: The size of the memoization table could be N*3 which can be simplified as N. As you could see that the table is an ordered map and we're doing operations such as insertion and searching in it, which takes logarithmic time. 
                                       More clearly both the insertion and searching will end up taking `Log(sizeofmap)` time. More clearly Log(N) time and as we're doing it for each node hence the overall time complexity becomes NLogN.
                                       
                        - Auxiliary space : O(N*3 + N*3 + N)
                          Explanation: The first N*3 represents the overall space taken by the adjacency list. It's because for any node there can be at most 3 neighbours, its because we're dealing with a binary tree. 
                                       So as we're storing neighbours of each node thus the total space taken by the adjacency list is N*3.
                                       The second N*3 represents the overall space taken by the memoization table. 
                                       It will store results for each state of "node and parent" and as we're dealing with a binary tree and even if we convert it to a graph then still for any node you could you have 3 different parents only so considering this the memoization table will end up storing results for O(N*3) states only.
                                       The third term N represents the maximum depth of the recursion stack.
*/

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
// Class to implement the Top-down approach:
class DynamicProgramming {
    // Stores the list of neighours of each node
    unordered_map<TreeNode*, vector<TreeNode*>> adjList; 

    void constructGraph(TreeNode* node, TreeNode* parent) {
        if(!node)
            return;

        if(parent) {
            adjList[node].push_back(parent);
            adjList[parent].push_back(node);
        }

        constructGraph(node->left, node);
        constructGraph(node->right, node);
    }

private:
    // Memoization table
    map<pair<TreeNode*, TreeNode*>, int> memory; 

    int solveWithoutMemo(TreeNode* node, TreeNode* parent) {
        int maxPathSum = 0;

        // If the neighbour of the node is not it's parent then explore the path and get the maximum path sum you can get
        for(auto& neighbor : adjList[node]) 
            if(neighbor != parent) 
                maxPathSum = max(maxPathSum, solveWithoutMemo(neighbor, node));

        return maxPathSum + node->val;
    }

    int solveWithMemo(TreeNode* node, TreeNode* parent) {
        // Memoization table: If the current state is already computed then return the computed value
        if(memory.count({node, parent}))
            return memory[{node, parent}];

        int maxPathSum = 0;

        // If the neighbour of the node is not it's parent then explore the path and get the maximum path sum you can get
        for(auto& neighbor : adjList[node]) 
            if(neighbor != parent) 
                maxPathSum = max(maxPathSum, solveWithMemo(neighbor, node));

        // Store the result value to the memoization table and then return it
        return memory[{node, parent}] = maxPathSum + node->val;
    }

public:
    // Method to find the maximum path sum of any non-empty path, using recursion with memoization :-
    int maxPathSum(TreeNode* rootNode) {
        // Construct the undirected graph form of the tree
        constructGraph(rootNode, nullptr);

        int result = INT_MIN;

        // Consider each node as an unique root node and then find the maximum path sum from it and then update the result by the maximum value
        for(auto& [node, neighbors] : adjList) 
            result = max({result, node->val, solveWithMemo(node, nullptr)});

        // If there's only a single node in the tree then return it's value else return the maximum path sum we got
        return (result == INT_MIN) ? rootNode->val : result;
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Tree | Depth-First Search | Binary Tree
Link  : https://leetcode.com/problems/binary-tree-maximum-path-sum/description/
