#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>

/*
Computational Finance - Assignment 2
Part I: Basic option valuation of put option
T = 1, K = 99, r = 6, S = 100, sigma = 20

Experiment 1: For the above numbers, what is option price?
Experiment 2: Investigate the convergence by increasing N
Experiment 3: Adjust K and sigma

*/
double mean(double arr[], int size)
    {
        double sum;
        for (int i = 0; i < size; i++)
        {
            sum += arr[i];
        }
        std::cout << ' ';
        return sum/size;
    }

double standard_error(double arr[], int size)
    {
        double var = 0;
        double mu = mean(arr, size);
        for (int i = 0; i < size; i++)
        {
           var += (arr[i] - mu) * (arr[i] - mu);
        }
        var /= size;
        return sqrt(var)/sqrt(size);
    }

double european_put(int T, double K, double r, double S, double sigma, int trials, bool error)
    {
        std::random_device rd{};      
        std::mt19937 gen{rd()};       
        double S_adjust = S * exp(T * (r-0.5*sigma*sigma));
        double payoff_array[trials];
        double S_cur;
        
        for(int i = 0; i < trials; i++)
        {
            std::normal_distribution<float> d(0, 1);
            double Z = d(gen);
            S_cur = S_adjust * exp(sqrt(T *sigma*sigma)* Z);
            payoff_array[i] =  std::max(K - S_cur, 0.0);
        }
        
        if(error == false)
        {
        std::cout << "European call is valued at " << mean(payoff_array, trials) * exp(-r*T) ; 
        }
        else
        {
        std::cout << "European call is valued at " << mean(payoff_array, trials) * exp(-r*T) << ", SE = " <<  standard_error(payoff_array, trials) << std::endl ; 
        }

    }

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    // Define random number generator
    std::random_device rd{};
    std::mt19937 gen{rd()};
 
    // Variables
    int T = 1;
    double K = 99;
    float r = 0.06;
    double S = 100;
    float sigma = 0.2;
    int trials = 100;

    double S_adjust = S * exp(T * (r-0.5*sigma*sigma));
    double S_cur = 0.0;
    double payoff_sum = 0.0;

    // Experiment 1:
    std::cout << "Experiment 1: Calculate put option \n";
    european_put(T, K, r, S, sigma, trials, false);

    // Experiment 2:
    /*
    std::cout << "\n\n";
    std::cout << "Experiment 2: Evaluate convergence" << std::endl;

    for(int i = 1; i <= 1000000; i= i * 10)
    {
        european_put(T, K, r, S, sigma, i, true);
    }
*/
    // Experiment 3:
    std::cout <<"\n\n";
    std::cout<< "Experiment 3: Evaluate difference in K and Sigma \n" << std::flush;
    for(double k = 25; k <= 150; k = k + 25)
    {
        std::cout << k << european_put(T, k, r, S, sigma, 100000, true);
    }


    for(double i = 0.05; i <= 2; i = i + 0.05)
    {
        std::cout << i << european_put(T, K, r, S, i, 100000, true);
    }

    return 0;
}
