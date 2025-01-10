// Program to merge the nodes lying in between zeros in a linked list ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>

// List template
class ListNode {
public:
    int val;
    ListNode* next;

    // Init constructor
    ListNode(int val, ListNode* next = nullptr)
    :
    val(val), next(next) {}

    // Init destructor
    ~ListNode() {
        if(next) {
            delete next;
        }
    }

    // Method to insert a node in the list - O(1) & O(1)
    void insertNodeInList(ListNode*& headNode, ListNode*& currNode, int userValue) {
        ListNode* newNode = new ListNode(userValue);
        if(!headNode)
            headNode = newNode, currNode = newNode;
        else
            currNode->next = newNode, currNode = currNode->next;
        currNode->next = nullptr;
    }

    // Method to print the list - O(N) & O(1)
    void printList(ListNode* headNode) {
        while(headNode) {
            std::cout<<headNode->val<<' ';
            headNode = headNode->next;
        }
        std::cout<<'\n';
    }
};

// Solution class:
class Solution {
public:
    // #1 Method to merge the nodes lying in between zeros using dynamic node creation - O(N) & O(N)
    ListNode* mergeNodes_V1(ListNode* headNode) {
        ListNode* newHead    = nullptr; // Tracks the head node of the new list
        ListNode* newCurrent = nullptr; // Tracks any node of the new list
        int subListSum = 0;             // Tracks the sum of any sublist with nodes value other than zero

        // Iterate the list
        while(headNode) {
            // When we reach the node with value zero
            if(headNode->val == 0) {
                // Create a new node its because a sublist with values other than zero is processed already 
                if(subListSum != 0) {
                    ListNode* newNode = new ListNode(subListSum);
                    // If the new list is empty then set the head node of the new list
                    if(!newHead)
                        newHead = newNode, newCurrent = newNode;
                    // Else then set the current node in the new list
                    else
                        newCurrent->next = newNode, newCurrent = newCurrent->next;
                }
                // Reset the sum to zero as we're forwarding to a new sublist
                subListSum = 0;
            }
            // Else sum the value of the node of the sublist
            else {
                subListSum += headNode->val;
            }
            // Move to the next node in the list
            headNode = headNode->next;
        }

        // Return the head node of the new list
        return newHead;
    }
    // Note: This solution can lead to the "memory leak issues" as the new list is created dynamically but never freed.

    // #2 Method to merge the nodes lying in between zeros using buffer only - O(N) & O(N)
    ListNode* mergeNodes_V2(ListNode* headNode) {
        // Stores the nodes of the resultant list
        std::vector<ListNode*> buffer;

        // Iterate the list
        while(headNode) {
            // Mark the node as the start point of a sublist with values other than zero
            ListNode* startNode = headNode;
            // Store the sum of the sublist in the start point of the sublist
            while(headNode->next && headNode->val != 0) {
                startNode->val += headNode->next->val;
                headNode = headNode->next;
            }
            // If the value of the start point is not zero then store the node into the buffer
            if(startNode->val != 0) {
                buffer.push_back(startNode);
            }
            // Move to the next node in the list
            headNode = headNode->next;
        }

        int size = buffer.size();

        // Link all the nodes of the resultant list
        for(int node = 0; node < size; ++node) {
            buffer[node]->next = nullptr;
            if(node > 0) buffer[node-1]->next = buffer[node];
        }   

        // If the list is not empty then return the head node of the resultant list
        return (size > 0) ? buffer[0] : nullptr;
    }

    // #3 Method to merge the nodes lying in between zeros using constant auxiliary space - O(N) & O(1)
    ListNode* mergeNodes_V3(ListNode* headNode) {
        ListNode* newHead    = nullptr; // Tracks the head node of the resultant list
        ListNode* newCurrent = nullptr; // Tracks any node of the resultant list

        // Iterate the list
        while(headNode) {
            // Mark the node as the start point of a sublist with values other than zero
            ListNode* startNode = headNode;
            // Store the sum of the sublist in the start point of the sublist
            while(headNode->next && headNode->val != 0) {
                startNode->val += headNode->next->val;
                headNode = headNode->next;
            }
            // If the value of the start point is not zero then set the "start point node" in the resultant list
            if(startNode->val != 0) {
                // If the resultant list is empty then set the head node of the list
                if(!newHead)
                    newHead = startNode, newCurrent = startNode;
                // Else then set the current node in the resultant list
                else
                    newCurrent->next = startNode, newCurrent = newCurrent->next;
                newCurrent->next = nullptr;
            }
            // Move to the next node in the list
            headNode = headNode->next;
        }

        // Return the head node of the resultant list
        return newHead;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;
    
    while(userWantsOperation) { 
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the number of nodes for the list
        int size; 
        std::cout<<"Enter the number of nodes for the list: ";
        std::cin>>size;

        // Check the given size is valid or not
        if(size <= 0) { 
            std::cout<<"Enter a valid size, application expects a positive integer!";    
            return 0;
        }

        ListNode* headNode = nullptr; // Tracks the head node of the list
        ListNode* currNode = nullptr; // Tracks the latest inserted node of the list
                
        // Input the nodes value of the list
        for(int node=1; node<=size; ++node) {
            int userValue;
            std::cout<<"Enter the value of the "<<node<<"th node: ";
            std::cin>>userValue;
            headNode-> insertNodeInList(headNode, currNode, userValue);
        }

        // Print call
        std::cout<<"\nOriginal list: ";
        headNode->printList(headNode);

        // Merge call
        Solution solution;
        solution.mergeNodes_V3(headNode);

        // Print call
        std::cout<<"Modified list: ";
        headNode->printList(headNode);

        // Deletion call (delete the head node and recursively the entire list)
        delete headNode; headNode = nullptr;

        // Input section to handle flow of iterations of the application
        char userChoise;
        std::cout<<"\nDo you want to perform the same operation on an another list? (Write Y for \"Yes\" else application will exit automatically): ";
        std::cin>>userChoise;
        userWantsOperation = (userChoise == 'Y') ? true : false;
    }

    return 0;
}
/*
    Topics: Linked List | Simulation
    Link  : https://leetcode.com/problems/merge-nodes-in-between-zeros/description/
    New Solutions Created By Me: https://leetcode.com/problems/merge-nodes-in-between-zeros/solutions/4381715/bruteoptimal-3solutions-self-explanatory-0d0r/
*/
