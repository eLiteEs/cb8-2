/*
  @author: Blas - eLite (c) 2024
  @def File for working on the console
  @copyright eLite (c) 2024
  @category console
  @since 1.0
*/

#include "imports.cpp"

enum TextStyles {UNDERLINE, BOLD, REVERSE, DIM, BLINKING, RESET};

/*
 @def Function for clearing the screen
 @brief Clear the screen
 @example clearc()
*/
void clearc() {
#ifdef _WIN32
    std::system("cls");
#else
    // Assuming Unix-like system
    std::system("clear");
#endif
}
/*
 @def Function for pausing the console using "pause" command
 @brief Pause the console
 @example pausec()
*/
void pausec() {
    system("pause");
}
/*
 @def Function for going to an x and an y in the console.
 @brief Move the console cursor.
 @example gotoxyc(0,0)
 @param x Column of the console
 @param y Row of the console
*/
void gotoxyc(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}
/*
 @def Function for initializing windows terminal or old cmd for putting ANSI rgb text.
 @brief Initialize Windows Shells
 @example initc()
*/
void initc() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD originalAttributes = consoleInfo.wAttributes;
}
/*
 @def Change the foreground color to ANSI rbg color.
 @brief Change foreground color
 @example colorc(150, 150, 150)
 @param r Red level (0 to 255)
 @param g Green level (0 to 255)
 @param b Blue level (0 to 255)
*/
void colorc(int r, int g, int b) {
    std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m";
}
/*
 @def Change the text background color to ANSI rgb color.
 @brief Change text background color
 @example bgcolorc(150, 150, 150)
 @param r Red level (0 to 255)
 @param g Green level (0 to 255)
 @param b Blue level (0 to 255)
*/
void bgcolorc(int r, int g, int b) {
    std::cout << "\033[48;2;" << r << ";" << g << ";" << b << "m";
}
/*
 @def Reset the text background and foregroud to default.
 @brief Reset console colors.
 @example resetcc()
*/
void resetcc() {
    std::cout << "\033[0m";
}