#pragma once

#define DEBUG 0

//foreground colors
#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define MAGENTA "\033[35m"
#define WHITE "\033[37m"

//background colors
#define BG_GREEN "\033[42m"
#define BG_RED "\033[41m"
#define BG_BLUE "\033[44m"
#define BG_YELLOW "\033[43m"
#define BG_CYAN "\033[46m"
#define BG_MAGENTA "\033[45m"
#define BG_WHITE "\033[47m"

//text styles
#define RESET "\033[0m"
#define BOLD "\033[1m"

//misc
#define CLEAR "\033[2J\033[1;1H"

//arrow keys
#define UP_ARROW 65
#define DOWN_ARROW 66
#define RIGHT_ARROW 67
#define LEFT_ARROW 68

//other keys
#define BACKSPACE 127
#define ENTER 13
#define ESCAPE 27
#define TAB 9
#define CTRL_C 3
