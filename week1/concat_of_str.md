//readme_file of  concat_of_str

1. Program demonstrates string concatenation in C without using `strcat()`.  
2. It takes two strings as input from the user.  
3. Finds the end of the first string manually.  
4. Appends the second string character by character to the first string.  
5. Adds a null terminator at the end to complete the concatenated string.  
6. Displays the final concatenated result.  
7. Uses `gets()` for input, which is unsafe and should not be used in real applications.  
8. For safer input handling, `fgets()` is recommended.  
9. To run the program:  
   - Save code in a file named `concat_of_str.c`.  
   - Compile using `gcc concat_of_str.c -o concat_of_str`.  
   - Run with `./concat_of_str`.  
10. Example output:  
    - Enter first string: Hello  
    - Enter second string: World  
    - Concatenated string: HelloWorld  
11. Learning outcome: practice of manual string manipulation and concatenation in C.  
