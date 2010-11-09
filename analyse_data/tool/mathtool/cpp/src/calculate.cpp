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

namespace mathtool
{
    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  Sum
     *  Description:  计算总和
     * =====================================================================================
     */
    double sum(vector <double> factorArray)
    {
        double Sum;
        vector <double>::iterator iter;
        for(iter=factorArray.begin();iter!=factorArray.end();iter++) {
            Sum += *iter;  // for Sum(x)
        }
        return Sum;
    }

    
    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  geometric avarage
     *  Description:  算术平均
     * =====================================================================================
     */
    double geometric_avarage (vector <double> factorArray)
    {
        double Multiplication;
        vector <double>::iterator iter;
        for(iter=factorArray.begin();iter!=factorArray.end();iter++) {
            Multiplication *= *iter;  
        }
        return pow(Multiplication,(double)factorArray.size()*(-1));
    }		
    
    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  arithmetic_average
     *  Description:  算术平均
     * =====================================================================================
     */
    double arithmetic_average(vector <double> factorArray)
    {
        double Sum = sum(factorArray);
        return Sum / factorArray.size(); 
    }

    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  variance
     *  Description:  计算方差
     * =====================================================================================
     */
    double variance(vector <double> factorArray)
    {
        double Avg = arithmetic_average(factorArray);
        double SquareSum = 0;

        vector <double>::iterator iter;
        for(iter=factorArray.begin();iter!=factorArray.end();iter++) {
            SquareSum += (*iter) * (*iter) ;
        }

        double length = factorArray.size();
        return Avg*Avg - SquareSum/length;
    }


    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  standard_deviation
     *  Description:  标准差
     * =====================================================================================
     */
    double standard_deviation(vector <double> factorArray)
    {
        double Vrc = variance(factorArray);
        return pow(Vrc,0.5);
    }		


    
    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  sigma
     *  Description:  
     * =====================================================================================
     */
    double sigma (int i_button,int i_top,double * func)
    {
        return  0;
    }		


}
