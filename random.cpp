#include <cstdlib>
#include <iostream>
#include <time.h> 
#include <math.h>

double normal()
    // This generates a random normal variable
    {
    
    double x = 0.0;
    double y = 0.0;
    double euclid_sq = 0.0;

    // Continue generating two uniform random variables
    // until the square of their "euclidean distance" 
    // is less than unity
    do {
        x = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
        y = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
        euclid_sq = x*x + y*y;
    } while (euclid_sq >= 1.0);

    return x*sqrt(-2*log(euclid_sq)/euclid_sq);
    
    }


int main() 
    {
        std::cout << "Fuck\n";

        for(int i = 0; i < 100; i++){
        std::cout << normal() << "\n";
        }
    }
