#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define NO_IDENTIFICATOR        0
#define IDENTIFICATOR_BEGIN     1
#define IDENTIFICATOR_END       2
#define IDENTIFICATOR_REPEAT    3
#define IDENTIFICATOR_UNTIL     4
#define IN_COMMA                5
#define IN_QUOTES               6

char toUpperCase(char ch)
{
    if (ch >= 'a' && ch <='z')
    {
        return ch - 'a' + 'A';
    }
    return ch;
}

int isAfterIdentificatorChar(char ch)
{
    return ((ch == ' ') || (ch == ';') || (ch == '{') || (ch == '\n') 
    || (ch == '\'') || (ch == EOF));
}

int isBeforeIdentificatorChar(char ch)
{
    return ((ch == ' ') || (ch == ';') || (ch == '}') || (ch == '\n')
    || (ch == '\''));
}

int checkPascal(FILE *fileIn)
{
    int nLine, nSymbol;
    char ch, prevCh;
    int state = NO_IDENTIFICATOR;
    int findIdentificator = NO_IDENTIFICATOR;
    prevCh = ' ';
    struct stack *operatorsStack = NULL;
    nLine = 1;
    nSymbol = 0;
    while ((ch = fgetc(fileIn)) != EOF)
    {
        ch = toUpperCase(ch);
        // begin new identificator if nothing don't prevent
        if (state == NO_IDENTIFICATOR)
        {
            if (isBeforeIdentificatorChar(prevCh))
            {
                if (ch == 'B') state = IDENTIFICATOR_BEGIN;
                else if (ch == 'E') state = IDENTIFICATOR_END;
                else if (ch == 'R') state = IDENTIFICATOR_REPEAT;
                else if (ch == 'U') state = IDENTIFICATOR_UNTIL;
                // printf("%d-%c  ", state, ch);
            }
        }
        else if (state == IDENTIFICATOR_BEGIN)
        {
            if ( (prevCh != 'B' || ch != 'E') && 
                 (prevCh != 'E' || ch != 'G') &&
                 (prevCh != 'G' || ch != 'I') &&
                 (prevCh != 'I' || ch != 'N') )
            {
                state = NO_IDENTIFICATOR;
            }
            if ( (prevCh == 'N') && isAfterIdentificatorChar(ch) )
            {
                //puts("find BEGIN");
                if (pushToStack(&operatorsStack, 'B'))
                {
                    puts("Internal Error");
                    return 1;
                }
            }
        }
        else if (state == IDENTIFICATOR_END)
        {
            if ( (prevCh != 'E' || ch != 'N') && 
                 (prevCh != 'N' || ch != 'D') )
            {
                state = NO_IDENTIFICATOR;
            }
            if ( (prevCh == 'D') && (isAfterIdentificatorChar(ch) || (ch == '.')) )
            {
                // puts("find END");
                int lastOperator;
                if (popFromStack(&operatorsStack, &lastOperator)) 
                { // error
                    printf("Syntax error in %d line : %d symbol > ", nLine, nSymbol - 3);
                    puts("Need BEGIN before END");
                    return 2;
                }
                else
                { // Stack don't empty
                    if (lastOperator != 'B')
                    {
                        printf("Syntax error in %d line : %d symbol > ", nLine, nSymbol - 3);
                        puts("Need BEGIN before END");
                        return 2;                       
                    }
                }
            }
        }
        else if (state == IDENTIFICATOR_REPEAT)
        {
            if ( (prevCh != 'R' || ch != 'E') && 
                 (prevCh != 'E' || ch != 'P') &&
                 (prevCh != 'P' || ch != 'E') &&
                 (prevCh != 'E' || ch != 'A') &&
                 (prevCh != 'A' || ch != 'T') )
            {
                state = NO_IDENTIFICATOR;
            }
            if ( (prevCh == 'T') && isAfterIdentificatorChar(ch) )
            {
                // puts("find REPEAT");
                if (pushToStack(&operatorsStack, 'R'))
                {
                    puts("Internal Error");
                    return 1;
                }
            }
        }
        else if (state == IDENTIFICATOR_UNTIL)
        {
            if ( (prevCh != 'U' || ch != 'N') && 
                 (prevCh != 'N' || ch != 'T') &&
                 (prevCh != 'T' || ch != 'I') &&
                 (prevCh != 'I' || ch != 'L') )
            {
                state = NO_IDENTIFICATOR;
            }
            if ( (prevCh == 'L') && isAfterIdentificatorChar )
            {
                // puts("find UNTIL");
                int lastOperator;
                if (popFromStack(&operatorsStack, &lastOperator)) 
                { // error
                    printf("Syntax error in %d line : %d symbol > ", nLine, nSymbol - 5);
                    puts("Need REPEAT before UNTIL");
                    return 2;
                }
                else
                { // Stack don't empty
                    if (lastOperator != 'R')
                    {
                        printf("Syntax error in %d line : %d symbol > ", nLine, nSymbol - 5);
                        puts("Need REPEAT before UNTIL");
                        return 2;                       
                    }
                }
            }
        }
        else if (state == IN_COMMA)
        {
            if (ch == '}')
            {
                state = NO_IDENTIFICATOR;
            }
        };
        if (ch == '\'')
        {
            if (state == IN_QUOTES)
            {
                state = NO_IDENTIFICATOR;
            }
            else if (state != IN_COMMA)
            {
                state = IN_QUOTES;
            };
        }
        if (ch == '{')
        {
            state = IN_COMMA;
        }
        ++nSymbol;
        if (ch == '\n')
        {
            ++nLine;
            nSymbol = 1;
        }
        prevCh = ch;
    }
    if (state == IDENTIFICATOR_END && prevCh == 'D')
    {// file end with END
        int lastOperator;
        if (popFromStack(&operatorsStack, &lastOperator)) 
        { // error
            printf("Syntax error in %d line : %d symbol > ", nLine, nSymbol - 3);
            puts("Need BEGIN before END");
            return 2;
        }
        else
        { // Stack don't empty
            if (lastOperator != 'B')
            {
                printf("Syntax error in %d line : %d symbol > ", nLine, nSymbol - 3);
                puts("Need BEGIN before END");
                return 2;                       
            }
        }
    }
    int lastOperator;
    if (!popFromStack(&operatorsStack, &lastOperator))
    { // stack don't empty
        if (lastOperator == 'B')
        {
            printf("Syntax error in %d line : %d symbol > ", nLine, nSymbol);
            puts("BEGIN is uncloused");
            return 1;
        }
        else if (lastOperator == 'R')
        {
            printf("Syntax error in %d line : %d symbol > ", nLine, nSymbol);
            puts("REPEAT is uncloused");
            return 1;
        }
    }
    return 0;
}

int main(int argv, char* argc[])
{

    if (argv != 2)
    {
        fprintf(stderr ,"Need only one argument");
        return 1;
    }
    FILE *fileIn;
    if (!(fileIn = fopen(argc[1], "r")))
    {
        puts("Can't open file");
        return 2;	
    }

    int checkResult = checkPascal(fileIn);
    if (!checkResult)
    {
        puts("File is correct");
        return 0;
    }
    else
    {
        puts("File checking failed");
        return 3;
    }
}
