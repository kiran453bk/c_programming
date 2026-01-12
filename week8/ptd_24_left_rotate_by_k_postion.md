# Array Left Rotation in C

## Overview

This program performs a **left rotation** on an array by `k` positions.  
A left rotation operation shifts each element of the array to the left by `k` places, and the first `k` elements are moved to the end of the array.

## Features

- Accepts user input for array size and elements.
- Handles cases where `k > n` by using modulo operation (`k % n`).
- Efficiently rotates the array using a temporary buffer.

## How It Works

1. User enters the size of the array (`n`).
2. User inputs `n` array elements.
3. User provides the number of rotations (`k`).
4. Program:
   - Stores the first `k` elements in a temporary array.
   - Shifts the remaining elements to the left.
   - Copies the temporary elements to the end of the array.
5. Prints the rotated array.
