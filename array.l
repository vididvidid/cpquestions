/* SECTION 1: Declarations (C code and setup) */
%{
    #include <stdio.h>
    #include <stdlib.h>
    
    // We will keep track of how many numbers we found
    int count = 0; 
%}

/* SECTION 2: Rules (The Regular Expressions) */
%%

[0-9]+          { 
                    /* If you see one or more digits, convert it and print it! */
                    int number = atoi(yytext); 
                    printf("Found number %d: %d\n", ++count, number); 
                }

[\[\], \t\n]+   { 
                    /* If you see brackets, commas, spaces, or newlines, do absolutely nothing (ignore them) */ 
                }

.               { 
                    /* The dot means "anything else". We flag it as an error. */
                    printf("Error: Unexpected character '%s'\n", yytext); 
                }

%%

/* SECTION 3: C Code (The main function) */
int main(int argc, char **argv) {
    printf("Type an array like [10, 20, 30] and press Enter (Ctrl+D to stop):\n");
    
    // yylex() is the magic function that starts the scanning!
    yylex(); 
    
    printf("\nTotal numbers found: %d\n", count);
    return 0;
}

// This function is required by lex. It just tells it when to stop reading.
int yywrap() {
    return 1;
}
