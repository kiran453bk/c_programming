Prefix Sum Array in C

Overview
The prefix sum technique is used to efficiently calculate cumulative sums of an array. It is commonly used in range sum queries, subarray problems, and data preprocessing.

In a prefix sum array, each element at index i stores the sum of all elements from index 0 to i of the original array.

Concept
Given an array:
arr = [a0, a1, a2, a3, ..., an]

The prefix sum array is computed as:
prefix[0] = arr[0]
prefix[i] = prefix[i - 1] + arr[i]

Algorithm

Read the number of elements n

Read the array elements

Initialize prefix[0] with arr[0]

For each index i from 1 to n-1, compute
prefix[i] = prefix[i - 1] + arr[i]

Display the prefix sum array

C Program Implementation
This program reads an array from the user and generates its prefix sum array using an additional array.

Sample Input
5
1 2 3 4 5

Sample Output
1 3 6 10 15

Complexity Analysis
Time Complexity: O(n)
Space Complexity: O(n)

Applications

Range sum queries

Subarray sum problems

Competitive programming

Data preprocessing

Cumulative frequency analysis

Notes

Maximum array size is set to 100 (can be modified)

Works with both positive and negative integers