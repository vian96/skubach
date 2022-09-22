#include <unistd.h>
#include <getopt.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

enum calc_op {
    CALC_NONE = 0,
    CALC_ADD = 'a', CALC_SUB = 's', 
    CALC_MUL = 'm', CALC_DIV = 'd'
};

calc_op get_calc_op (const char *str);

float calculate (float a, float b, calc_op op);

int main (int argc, char **argv) {
    if (argc <= 3) {
        printf ("ERROR: not enough args, use \"calc number1 number2 cmd\"!\n");
        return 0;
    }

    const struct option long_option[] =
    {
        {"add", no_argument, NULL, 'a'},
        {"sub", no_argument, NULL, 's'}, 
        {"mul", no_argument, NULL, 'm'}, 
        {"div", no_argument, NULL, 'd'}, 
        {NULL, no_argument, NULL, 0}
    };
	int long_index = 0;
    int opt = 0;
    const char short_option[] = "asmd";

    bool flag_a = 0, flag_s = 0, flag_d = 0, flag_m = 0;
    
    while((opt = getopt_long(argc, argv, short_option, long_option, &long_index)) != -1)
        switch(opt) {
            case 'a': 
                flag_a = 1;
                break;
            case 's': 
                flag_s = 1;
                break;
            case 'd': 
                flag_d = 1;
                break;
            case 'm': 
                flag_m = 1;
                break;
            case '?': 
                printf("Unknown parameter: -%c\n", optopt);
                break;
        }
    
    if (optind + 1 >= argc) {
        printf ("ERROR: not enough numbers, there should be at least two\n");
        return 0;
    }

    float res = atoi (argv[optind]);
    float b = atoi (argv[optind + 1]);
    if (flag_a)
        res += b;
    if (flag_s)
        res -= b;
    if (flag_m)
        res *= b;
    if (flag_d)
        res /= b;
    
    printf ("Answer is %f\n", res);
}

calc_op get_calc_op (const char *str) {
    if (!strcmp ("sub", str))
        return CALC_SUB;
    if (!strcmp ("add", str))
        return CALC_ADD;
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
    case CALC_ADD:
        return a+b;
    case CALC_MUL:
        return a*b;
    case CALC_DIV:
        return a/b;
    default:
        return NAN;
    } 
}

