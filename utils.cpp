/*
  @author: Blas - eLite (c) 2024
  @def File with useful functions
  @copyright eLite (c) 2024
  @category utils, functions
  @since 1.0
*/

#include "imports.cpp"

/*
 @def Function for checking if two variables of different types are the same.
 @brief Check if two variables are equal.
 @example areeqs("1", 1)
 @param a Variable 1
 @param b Variable 2
 @return true if the two variables are the same
 @return false if the two variables aren't the same
*/
template<typename T, typename U>
bool areeqs(const T& a, const U& b) {
    if constexpr(std::is_same_v<T, U>) {
        return a == b;
    } else {
        if constexpr(std::is_convertible_v<U, std::string>) {
            return std::to_string(a) == b;
        } else if constexpr(std::is_convertible_v<T, std::string>) {
            return a == std::to_string(b);
        } else {
            // Types cannot be compared
            return false;
        }
    }
}