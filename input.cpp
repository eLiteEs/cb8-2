/*
  @author: Blas - eLite (c) 2024
  @def File for userinput on console
  @copyright eLite (c) 2024
  @category console input
  @since 1.0
*/

#include "imports.cpp"

/*
 @def Function for make a user input echoing the text
 @brief Make an user input
 @example input<String>("username: ")
 @param prompt Text to print before user input
 @return Inserted text
*/
String input(const string& prompt) {
    cout << prompt;
    String ret;
    getline(cin, ret);
    return ret;
}

/*
 @def Function for make a user input without echoing the text
 @brief Make an password user input
 @example privinput<String>("password: ")
 @param prompt Text to print before user input
 @return Inserted text
*/

#include <conio.h>

String privinput(const string& prompt) {
    String input;
    string inputStr;
    char ch_input;
    cout << prompt;

    while (true) {
        ch_input = _getch(); // Read character without echoing

        if (ch_input == '\r') { // Enter key pressed
            cout << endl;
            break;
        } else if (ch_input == '\b' && !inputStr.empty()) { // Backspace key pressed
            inputStr.pop_back();
            cout << "\b \b"; // Erase previously printed character
        } else if (ch_input == '\b' && inputStr.empty()) { // Backspace key pressed at the beginning of the line
            continue;
        } else { // Other keys pressed
            inputStr.push_back(ch_input);
        }
    }
    return inputStr;
}
/*
 @def Function for make a user input enabling a character to show instead of the text
 @brief Make an password user input
 @example pprivinput<String>("password: ", "*")
 @param prompt Text to print before user input
 @param sp Character to show instead of the text
 @return Inserted text
*/
String pprivinput(const string& prompt, char sp) {
    string inputStr;
    char ch_input;
    cout << prompt;

    while (true) {
        ch_input = _getch(); // Read character without echoing

        if (ch_input == '\r') { // Enter key pressed
            cout << endl;
            break;
        } else if (ch_input == '\b' && !inputStr.empty()) { // Backspace key pressed
            inputStr.pop_back();
            cout << "\b \b"; // Erase previously printed character
        } else if (ch_input == '\b' && inputStr.empty()) { // Backspace key pressed at the beginning of the line
            continue;
        } else { // Other keys pressed
            cout << sp;
            inputStr.push_back(ch_input);
        }
    }
    return inputStr;
}