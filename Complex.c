#include <stdio.h>
#include "Complex.h"
#include <assert.h>

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
    Complex
}