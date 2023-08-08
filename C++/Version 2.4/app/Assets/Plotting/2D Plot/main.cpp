#include <cmath>
#include <cstdio>

int main()
{
    FILE *pipe = popen("gnuplot -persist", "w");
    if (pipe == NULL) { 
        return 1;
    }

    fprintf(pipe, "plot '-' with lines\n");
    for (double x = -10; x <= 10; x += 0.1) {
        fprintf(pipe, "%f %f\n", x, std::pow(x, 3) - 3*std::pow(x, 2) + 2*x);
    }
    fprintf(pipe, "e\n");
    fflush(pipe);

    pclose(pipe);
    return 0;
}