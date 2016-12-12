#include <stdio.h>
#include <stdlib.h>
#include "Complex.h"
#include <assert.h>
#include <string.h>

typedef struct Complex
{
    double re;
    double im;
} Complex;

/**
 * @brief create a new complex number
 *
 * @param s the string that contain the number. the syntax for Complex number is '<double number>,<double number>i'
 * for example : "0,0i","1.878,78i","-768,1i".
 * you can use atof for converting the <double_number>
 * @return ComplexP that is repesneted by the string. if the string do not match the syntax return NULL;
 */
ComplexP fromCharFunc(char * s)
{
    assert(s != NULL);

    int length = strlen(s);
    ComplexP complexp = (ComplexP) malloc(sizeof(Complex));
    char* line = NULL;
    line = strtok(s, ",");

    assert(line != NULL);

    complexp->re = atof(line);
    line = strtok(NULL, "i");

    assert(line != NULL);

    complexp->im = atof(line);

    return complexp;
}

/**
* @brief a string repesnets the complex number
*
* @param num is the number.
* @ str - Pointer to a buffer where the resulting C-string is stored.
*    The buffer should have a size of at least n characters
* @ n - Maximum number of bytes to be used in the buffer.
*     The generated string has a length of at most n-1, leaving space for the additional terminating null character.
* the syntax of the string should be '<double number>,<double number>i'
* for example : "0,0i","1.878,78i","-768,1i".
* @return  The number of characters that would have been written if n had been sufficiently large,
*  not counting the terminating null character. If an encoding error occurs, a negative number is returned.
*/
int toChar(char * str, int n, ConstComplexP num)
{

}

/**
 * @brief free the complex object
 *
 * @param num is the number.
 */
void freeComplex(ComplexP num)
{
    free(num);
}

/**
 * @brief create a new complex number which is the result of addition num2 to num1.
 *
 * @param num1 - the first Complex
 * @param num1 - the second Complex
 * @return ComplexP that = num1+num2 . if num1/num2 is NULL return NULL;
 */
ComplexP add(ConstComplexP num1,ConstComplexP num2)
{
    if ((num1 == NULL) || (num2 == NULL))
    {
        return NULL;
    }
    ComplexP complexp = (ComplexP) malloc(sizeof(Complex));
    complexp->re = num1->re + num2->re;
    complexp->im = num1->im + num2->im;
    return complexp;
}

/**
* @brief create a new complex number which is the result of multiplication of scalar*num1
*
* @param num1 - scalar double number
* @param num1 - the  Complex
* @return ComplexP that = scalar*num . if num is NULL return NULL;
*/
ComplexP multScalar(double scalar,ConstComplexP num)
{
    if (num == NULL)
    {
        return NULL;
    }
    ComplexP complexp = (ComplexP) malloc(sizeof(Complex));
    complexp->re = num->re * scalar;
    complexp->im = num->im * scalar;
    return complexp;
}

/**
* @brief create a new complex number which is the result of multiplication of num1*num2
*
* @param num1 - the first Complex
* @param num1 - the second Complex
* @return ComplexP that = num1*num2 . if num1/num2 is NULL return NULL;
*/
ComplexP mult(ConstComplexP num1,ConstComplexP num2)
{
    if ((num1 == NULL) || (num2 == NULL))
    {
        return NULL;
    }
    ComplexP complexp = (ComplexP) malloc(sizeof(Complex));
    complexp->re = (num1->re * num2->re) - (num2->im * num1->im);
    complexp->im = (num1->re * num2->im) + (num2->re * num1->im);
    return complexp;
}





