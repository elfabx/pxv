#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "xye.h"

int read_xye(char* fn, double* x, double* y, int skip)
{
    char line[256];

    int n = -1;
    std::ifstream inp(fn);
    std::string fns(fn);

    std::cout << fn << std::endl;
    std::cout << skip << std::endl;
    if (skip > 0)
    {
        for (int i=0; i < skip; ++i)
        {
            inp.getline(line,255);
        }
    }
    while (inp.good())
    {
        inp.getline(line,255);
        double a,b;
        std::istringstream parse(line);
        parse >> a >> b;
        ++n;
        if (n==50000) return(n);
        x[n] = a;
        y[n] = b;
    }

    return(n);

}

