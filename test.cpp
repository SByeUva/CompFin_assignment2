#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>

double mean(double arr[], int size)
    // This method calculates the mean of Monte-Carlo 
    {
        double sum;
        for (int i = 0; i < size; i++)
        {
            sum += arr[i];
        }
        std::cout << sum/size << "\n";
        return sum/size;
    }

double standard_error(double arr[], int size)
    // This method computes the standard error of Monte-Carlo
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

void european_put(int T, double K, double r, double S, double sigma, int trials, bool error)
    // This computes the price of European put option 
    {
        double S_adjust = S * exp(T * (r-0.5*sigma*sigma));
        double payoff_array[trials];
        double S_cur;
        
        for(int i = 0; i < trials; i++)
        {
            double Z = normal();
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
    // Initial variables
    int T = 1;
    double K = 99;
    float r = 0.06;
    double S = 100;
    float sigma = 0.2;
    int trials = 100000;
    double payoff_sum = 0.0;

    // Experiment 1:
    std::cout << "Experiment 1: Calculate put option \n";
    european_put(T, K, r, S, sigma, trials, false);
        
    
    }
