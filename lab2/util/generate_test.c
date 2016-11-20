#include <stdio.h>

void generateTree(long nNodes, long nTreads, float rampfyFrequency)
{
    // printf("%ld\n", nNodes);
    // printf("%ld\n", nTreads);
    // printf("%f\n", rampfyFrequency);

    printf("%ld\n", nNodes);
    long level = 0;
    long fromOld, toOld, fromNew, toNew;
    fromNew = toNew = 0;
    fromOld = toOld = 0;
    float ramifySum = 1.0;
    long multiplier;
    long i, j, k;
    j = 1;
    while (j < nNodes)
    {
        ++level;
        if( ramifySum >= 1.0 )
        {
            multiplier = nTreads;
            ramifySum -= 1.0;
        }
        else
        {
            multiplier = 1;
        }
        ramifySum += rampfyFrequency;
        // recalculate froms & tos
        fromOld = fromNew;
        toOld = toNew;
        fromNew = toOld + 1;
        toNew = fromNew + (toOld - fromOld + 1) * multiplier - 1;
        for (i = fromOld; i <= toOld; ++i) {
            for (k = 0; k < multiplier; ++k){
                if (j < nNodes) {
                    printf("%ld %ld\n", i, j);
                }
                ++j;
            }
        }
    }
    printf("%ld\n", level);
}

int main(int argv, char * argc[])
{
    if (argv != 4)
    {
        fprintf(stderr, "Error: Invalid number of argumets\n");
        fprintf(stderr, "Need: <generate> <number of nodes> <number of treads> <ramify frequency>\n");
        return 3;
    }
    char * end = NULL;
    long nNodes;
    long nTreads;
    float rampfyFrequency;
    if (!sscanf(argc[1], "%ld", &nNodes)) {
        fprintf(stderr, "Error: Invalid <number of nodes> need long\n");
        return 2;        
    }
    if (!sscanf(argc[2], "%ld", &nTreads)) {
        fprintf(stderr, "Error: Invalid <number of treads> need long\n");
        return 2;        
    }
    if (!sscanf(argc[3], "%f", &rampfyFrequency)) {
        fprintf(stderr, "Error: Invalid <ramify frequency> need float\n");
        return 3;        
    }
    if (rampfyFrequency < 0 || rampfyFrequency > 1){
        fprintf(stderr, "Error: Ramify frequency must lie in [0, 1]\n");
        return 3;        
    }

    // long nNodes = strtol(argc[1], &end, 10);
    // long nTreads = strtol(argc[2], &end, 10);
    // float rampfyFrequency = strtof(argc[3], &end, 10);

    generateTree(nNodes, nTreads,rampfyFrequency);

    return 0;
}