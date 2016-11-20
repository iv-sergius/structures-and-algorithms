#include <stdio.h>

int main (int argv, char * argc[])
{
    if (argv != 2)
    {
        fprintf(stderr, "Error: Need only one argument\n");
        fprintf(stderr, "Need: <lab2> <name of file with node>\n");
        return 3;
    }
    FILE *fileIn;
    if (!(fileIn = fopen(argc[1], "r")))
    {
        fprintf(stderr, "Error: Can't open the file\n");
        return 2;	
    }
    fclose(fileIn);
    return 0;
}