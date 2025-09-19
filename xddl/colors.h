#pragma once
#ifndef _TEST_HEADER_H_
#define _TEST_HEADER_H_

/* COLOR TABLE */
/*
Name            FG  BG
Black           30  40
Red             31  41
Green           32  42
Yellow          33  43
Blue            34  44
Magenta         35  45
Cyan            36  46
White           37  47
Bright Black    90  100
Bright Red      91  101
Bright Green    92  102
Bright Yellow   93  103
Bright Blue     94  104
Bright Magenta  95  105
Bright Cyan     96  106
Bright White    97  107
*/
#define underline "\033[4m"
#define double_underline "\033[21m"
#define line_through "\033[9m"
#define italic "\033[3m"

#define rc "\033[0m"// reset color
#define reset_color "\033[0m"

#define gray "\033[2m"
#define black "\033[30m"
#define red "\033[31m"
#define green "\033[32m"
#define yellow "\033[33m"
#define blue "\033[34m"
#define magenta "\033[35m"
#define cyan "\033[36m"
#define white "\033[37m"

#define black_bg "\033[40m"
#define red_bg "\033[41m"
#define green_bg "\033[42m"
#define yellow_bg "\033[43m"
#define blue_bg "\033[44m"
#define magenta_bg "\033[45m"
#define cyan_bg "\033[46m"
#define white_bg "\033[47m"

#endif
