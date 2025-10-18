/*
 * Enhanced Calculator Program
 * First Week Assignment - Single Calculation Version
 * Covers: variables, input/output, conditionals, basic functions
 */

#include <stdio.h>
#include <math.h>

// Function prototype
void displayMenu();

int main() {
    double num1, num2, result;
    int operation;
    
    printf("==========================================\n");
    printf("   Welcome to the Enhanced Calculator!   \n");
    printf("==========================================\n\n");
    
    // Display menu
    displayMenu();
    
    // Get operation choice
    printf("Your choice: ");
    scanf("%d", &operation);
    
    // Validate operation choice
    if (operation < 1 || operation > 6) {
        printf("Error: Invalid operation. Please choose 1-6.\n");
        return 1;  // Exit with error code
    }
    
    // Get two numbers from user
    printf("Enter first number: ");
    scanf("%lf", &num1);
    
    printf("Enter second number: ");
    scanf("%lf", &num2);
    
    printf("\n");
    
    // Perform calculation based on operation
    if (operation == 1) {
        // Addition
        result = num1 + num2;
        printf("%.2f + %.2f = %.2f\n", num1, num2, result);
        
    } else if (operation == 2) {
        // Subtraction
        result = num1 - num2;
        printf("%.2f - %.2f = %.2f\n", num1, num2, result);
        
    } else if (operation == 3) {
        // Multiplication
        result = num1 * num2;
        printf("%.2f * %.2f = %.2f\n", num1, num2, result);
        
    } else if (operation == 4) {
        // Division
        if (num2 == 0.0) {
            printf("Error: Cannot divide by zero!\n");
        } else {
            result = num1 / num2;
            printf("%.2f / %.2f = %.2f\n", num1, num2, result);
        }
        
    } else if (operation == 5) {
        // Modulo
        if (num2 == 0.0) {
            printf("Error: Cannot perform modulo by zero!\n");
        } else {
            result = fmod(num1, num2);
            printf("%.2f %% %.2f = %.2f\n", num1, num2, result);
        }
        
    } else if (operation == 6) {
        // Power
        result = pow(num1, num2);
        printf("%.2f ^ %.2f = %.2f\n", num1, num2, result);
    }
    
    printf("\nThank you for using the calculator!\n");
    
    return 0;
}

/**
 * Displays the calculator menu with available operations
 */
void displayMenu() {
    printf("Select an operation:\n");
    printf("  1. Addition (+)\n");
    printf("  2. Subtraction (-)\n");
    printf("  3. Multiplication (*)\n");
    printf("  4. Division (/)\n");
    printf("  5. Modulo (%%)\n");
    printf("  6. Power (x^y)\n");
    printf("------------------------------------------\n");
}