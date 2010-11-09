/**
 * A C interface to mmseg-cpp. Will be compiled to a
 * shared library.
 */

#include "calculate.h"
#include  <iostream>

#if defined(_MSC_VER) // Microsoft compiler
#    define DLLEXPORT __declspec(dllexport)
#elif defined(__GNUC__) // GNU compiler
#    define DLLEXPORT
#else
#    error Unknown compiler, donot know how to process dllexport
#endif


extern "C" {
    
    DLLEXPORT
    double sum(double a[],long int l)
    {
        return calculate::sum(a,l);
    }

    DLLEXPORT
    double geometric_avarage(double a[],long int l)
    {
        return calculate::geometric_avarage(a,l); 
    }

    DLLEXPORT
    double arithmetic_average(double a[],long int l)
    {
        return calculate::arithmetic_average(a,l); 
    }

    DLLEXPORT
    double variance(double a[],long int l)
    {
        return calculate::variance(a,l); 
    }

    DLLEXPORT
    double standard_deviation(double a[],long int l)
    {
        return calculate::standard_deviation(a,l); 
    }

}
