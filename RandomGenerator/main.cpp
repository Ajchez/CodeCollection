#include "RandomGenerator.h"

#include <iostream>

int main()
{
    RandomGenerator<std::mt19937_64> rg;
    std::vector<double> random_vals1 = rg.GetRandomsVals<std::normal_distribution<double>>(20, 3.0, 5.0);
    std::vector<double> random_vals2 = rg.GetRandomsVals<std::normal_distribution<double>>(20, 3.0, 5.0);

    for (int i=0; i<20; ++i)
    {
        std::cout << random_vals1[i] << "     " << random_vals2[i] << std::endl;
    }
}
