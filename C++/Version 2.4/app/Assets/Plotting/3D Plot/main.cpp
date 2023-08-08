#include <iostream>
#include <vector>
#include <cstdio>

int main()
{
    FILE *pipe = popen("gnuplot -persist", "w");
    if (pipe == NULL) { 
        return 1;
    }

    int size = 5;
    std::vector<std::vector<double>> Z = {{1,2,3,4,5}, {2,3,4,5,6}, {3,4,5,6,7}, {4,5,6,7,8}, {5,6,7,8,9}};

    fprintf(pipe, "splot '-' with lines\n");
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            fprintf(pipe, "%d %d %f\n", i, j, Z[i][j]);
        }
        fprintf(pipe, "\n");
    }
    fprintf(pipe, "e\n");
    fflush(pipe);

    pclose(pipe);
    return 0;
}
