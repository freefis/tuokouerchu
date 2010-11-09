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

namespace calculate
{
    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  Sum
     *  Description:  计算总和
     * =====================================================================================
     */
    double sum(double factorArray[],long int length);
    
    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  geometric avarage
     *  Description:  几何平均
     * =====================================================================================
     */
    double geometric_avarage(double factorArray[],long int length);
    
    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  arithmetic_average
     *  Description:  算术平均
     * =====================================================================================
     */
    double arithmetic_average(double factorArray[],long int length);

    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  variance
     *  Description:  计算方差
     * =====================================================================================
     */
    double variance(double factorArray[],long int length);


    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  standard_deviation
     *  Description:  标准差
     * =====================================================================================
     */
    double standard_deviation(double factorArray[],long int length);
}
