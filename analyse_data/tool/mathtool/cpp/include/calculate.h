/*
 * =====================================================================================
 *
 *       Filename:  calculate.h
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
#include <vector>

namespace mathtool
{
    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  Sum
     *  Description:  计算总和
     * =====================================================================================
     */
    double sum(std::vector <double> factorArray);

    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  geometric avarage
     *  Description:  算术平均
     * =====================================================================================
     */
    double geometric_avarage (std::vector <double> factorArray);
    
    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  arithmetic_average
     *  Description:  算术平均
     * =====================================================================================
     */
    double arithmetic_average(std::vector <double> factorArray);

    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  variance
     *  Description:  计算方差
     * =====================================================================================
     */
    double variance(std::vector <double> factorArray);

    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  standard_deviation
     *  Description:  标准差
     * =====================================================================================
     */
    double standard_deviation(std::vector <double> factorArray);

    
    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  sigma
     *  Description:  
     * =====================================================================================
     */
    double sigma (int i_button,int i_top,double * func);
}
