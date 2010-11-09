/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  calculate
 *
 *        Version:  1.0
 *        Created:  2010/11/09 15时43分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  free.wang (), freefis@gmail.com
 *        Company:  tuokouerchu.com
 *
 * =====================================================================================
 */


#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

namespace calculate
{
    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  Sum
     *  Description:  计算总和
     * =====================================================================================
     */
    double sum(double factorArray[],long int length)
    {
        double Sum = 0;
        long int i;

        for(i=0;i<length;i++) 
            Sum += factorArray[i];  // for Sum(x)
        
        return Sum;
    }

    
    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  geometric avarage
     *  Description:  几何平均
     * =====================================================================================
     */
    double geometric_avarage(double factorArray[],long int length)
    {
        double Multiplication;
        long int i;

        for(i=0;i<length;i++) 
            Multiplication *= factorArray[i];  

        return pow(Multiplication,(double)length);
    }		
    
    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  arithmetic_average
     *  Description:  算术平均
     * =====================================================================================
     */
    double arithmetic_average(double factorArray[],long int length) 
    {
        double Sum = sum(factorArray,length);
        return Sum / length;
    }

    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  variance
     *  Description:  计算方差
     * =====================================================================================
     */
    double variance(double factorArray[],long int length) 
    {
        double Avg = arithmetic_average(factorArray,length);
        double SquareSum = 0;

        long int i;
        for(i=0;i<length;i++) {
            SquareSum += factorArray[i]*factorArray[i] ;
        }

        return Avg*Avg - SquareSum/length;
    }


    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  standard_deviation
     *  Description:  标准差
     * =====================================================================================
     */
    double standard_deviation(double factorArray[],long int length) 
    {
        double Vrc = variance(factorArray,length);
        return pow(Vrc,0.5);
    }		
}
