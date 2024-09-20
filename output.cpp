/*
  @author: Blas - eLite (c) 2024
  @def File for output on console 
  @copyright eLite (c) 2024
  @category console output
  @since 1.0
*/

#include "imports.cpp" // Import everything and also the new lang

/*
 @def Function for print text to screen with a new line
 @brief Print text with new line
 @example print("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
template <typename T, typename... Args>
void print(const T& first, const Args&... args) {
    std::ostringstream oss;
    oss << first;
    using expander = int[];
    (void)expander{0, (void(oss << args), 0)...};
    std::cout << oss.str() << "\n";
}
/*
 @def Function for print text to screen with a new line
 @brief Print text with new line
 @example print("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
fun print() {
    cout << "\n";
}
/*
 @def Function for print text to screen with a new line
 @brief Print text with new line
 @example print("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function print(String s) {
    standard::cout << s << "\n";
}
/*
 @def Function for print text to screen with a new line
 @brief Print text with new line
 @example print("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function print(Number n) {
    standard::cout << n << "\n";
}
/*
 @def Function for print text to screen with a new line
 @brief Print text with new line
 @example print("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function print(bool b) {
    standard::cout << b << "\n";
}
/*
 @def Function for print text to screen with a new line
 @brief Print text with new line
 @example print("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function print(float f) {
    standard::cout << f << "\n";
}
/*
 @def Function for print text to screen with a new line
 @brief Print text with new line
 @example print("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function print(long l) {
    standard::cout << l << "\n";
}
/*
 @def Function for print text to screen with a new line
 @brief Print text with new line
 @example print("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function print(short s) {
    standard::cout << s << "\n";
}
/*
 @def Function for print text to screen with a new line
 @brief Print text with new line
 @example print("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function print(double d) {
    standard::cout << d << "\n";
}
/*
 @def Function for print text to screen with a new line
 @brief Print text with new line
 @example print("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function print(char c) {
    standard::cout << c << "\n";
}
/*
 @def Function for print text to screen with a new line
 @brief Print text with new line
 @example print("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function print(const char* ca) {
    standard::cout << ca << "\n";
}
/*
 @def Function for print a vector with a understandable way
 @brief Print a list
 @example print(myList);
 @param v Vector to print
*/
template<typename T>
void print(const std::vector<T>& v) {
    // Iterate over the elements of the vector and do something
    std::cout << "[";
    int i = 1;
    for (const auto& element : v) {
        if(i == v.size()) {
            std::cout << element;
        } else {
            std::cout << element << ", ";
        }
        i++;
    }
    std::cout << "]";
    std::cout << std::endl;
}
/*
 @def Function for print text to screen with a new line
 @brief Print text with new line
 @example print("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function print(const auto& t) {
    standard::cout << t << "\n";
}


/*
 @def Function for print text to screen without a new line
 @brief Print text without new line
 @example printf("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function printf(String s) {
    standard::cout << s;
}/*
 @def Function for print text to screen without a new line
 @brief Print text without new line
 @example printf("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function printf(Number n) {
    standard::cout << n;
}/*
 @def Function for print text to screen without a new line
 @brief Print text without new line
 @example printf("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function printf(bool b) {
    standard::cout << b;
}/*
 @def Function for print text to screen without a new line
 @brief Print text without new line
 @example printf("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function printf(float f) {
    standard::cout << f;
}/*
 @def Function for print text to screen without a new line
 @brief Print text without new line
 @example printf("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function printf(long l) {
    standard::cout << l;
}/*
 @def Function for print text to screen without a new line
 @brief Print text without new line
 @example printf("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function printf(short s) {
    standard::cout << s;
}/*
 @def Function for print text to screen without a new line
 @brief Print text without new line
 @example printf("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function printf(double d) {
    standard::cout << d;
}/*
 @def Function for print text to screen without a new line
 @brief Print text without new line
 @example printf("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function printf(char c) {
    standard::cout << c;
}
/*
 @def Function for print a vector with a understandable way
 @brief Print a list
 @example printf(myList);
 @param v Vector to print
*/
template<typename T>
void printf(const std::vector<T>& v) {
    // Iterate over the elements of the vector and do something
    std::cout << "[";
    int i = 1;
    for (const auto& element : v) {
        if(i == v.size()) {
            std::cout << element;
        } else {
            std::cout << element << ", ";
        }
        i++;
    }
    std::cout << "]";
    std::cout << std::endl;
}
/*
 @def Function for print text to screen without a new line
 @brief Print text without new line
 @example printf("Hello World!");
 @param s/n/b/l/s/d/c/t/ca Text or number to print
*/
function printf(const auto& t) {
    standard::cout << t;
}
