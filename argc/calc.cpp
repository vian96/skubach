#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

enum calc_op {
    CALC_NONE = 0,
    CALC_SUM = 1, CALC_SUB = 2, 
    CALC_MUL = 3, CALC_DIV = 4
};

calc_op get_calc_op (const char *str);

float calculate (float a, float b, calc_op op);

int main (int argc, char **argv) {
    if (argc <= 3) {
        printf ("ERROR: not enough args, use \"calc number1 number2 cmd\"!\n");
        return 0;
    }

    calc_op op = get_calc_op (argv[3]);
    if (!op)
        printf ("ERROR: wrong operator\n");
    float a = atoi (argv[1]);
    float b = atoi (argv[2]);
    
    printf ("Answer is %f\n", calculate (a, b, op));
}

calc_op get_calc_op (const char *str) {
    if (!strcmp ("sub", str))
        return CALC_SUB;
    if (!strcmp ("sum", str))
        return CALC_SUM;
    if (!strcmp ("mul", str))
        return CALC_MUL;
    if (!strcmp ("div", str))
        return CALC_DIV;
    return CALC_NONE;
}

float calculate (float a, float b, calc_op op) {
    switch (op)
    {
    case CALC_SUB:
        return a-b;
    case CALC_SUM:
        return a+b;
    case CALC_MUL:
        return a*b;
    case CALC_DIV:
        return a/b;
    default:
        return NAN;
    } 
}

