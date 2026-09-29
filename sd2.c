#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack for characters
char opStack[MAX];
int top = -1;

// Stack for integers
int valStack[MAX];
int valTop = -1;

// Push operator
void pushOp(char c) {
    opStack[++top] = c;
}

// Pop operator
char popOp() {
    return opStack[top--];
}

// Push value
void pushVal(int value) {
    valStack[++valTop] = value;
}

// Pop value
int popVal() {
    return valStack[valTop--];
}

// Return precedence of operator
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

// Check whether character is operator
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' ||
           c == '/' || c == '^';
}

// Infix to postfix
void infixToPostfix(char infix[], char postfix[]) {
    int i, j = 0;
    char c;

    for (i = 0; infix[i] != '\0'; i++) {
        c = infix[i];

        // Ignore spaces
        if (c == ' ')
            continue;

        // If operand, add to postfix
        if (isalnum(c)) {
            postfix[j++] = c;
        }

        // If opening parenthesis
        else if (c == '(') {
            pushOp(c);
        }

        // If closing parenthesis
        else if (c == ')') {
            while (top != -1 && opStack[top] != '(')
                postfix[j++] = popOp();

            if (top != -1)
                popOp(); // Remove '('
        }

        // If operator
        else if (isOperator(c)) {
            while (top != -1 &&
                   opStack[top] != '(' &&
                   precedence(opStack[top]) >= precedence(c)) {
                postfix[j++] = popOp();
            }

            pushOp(c);
        }
    }

    // Pop remaining operators
    while (top != -1)
        postfix[j++] = popOp();

    postfix[j] = '\0';
}

// Evaluate postfix expression
int evaluatePostfix(char postfix[]) {
    int i, a, b;
    char c;

    for (i = 0; postfix[i] != '\0'; i++) {
        c = postfix[i];

        // If operand
        if (isdigit(c)) {
            pushVal(c - '0');
        }

        // If operator
        else if (isOperator(c)) {
            b = popVal();
            a = popVal();

            switch (c) {
                case '+':
                    pushVal(a + b);
                    break;

                case '-':
                    pushVal(a - b);
                    break;

                case '*':
                    pushVal(a * b);
                    break;

                case '/':
                    pushVal(a / b);
                    break;

                case '^': {
                    int result = 1;
                    for (int k = 0; k < b; k++)
                        result *= a;
                    pushVal(result);
                    break;
                }
            }
        }
    }

    return popVal();
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    printf("Result: %d\n", evaluatePostfix(postfix));

    return 0;
}
