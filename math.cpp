/*
  @author: Blas - eLite (c) 2024
  @def File for userful math operations
  @copyright eLite (c) 2024
  @category math
  @since 1.0
*/

#include "imports.cpp"

/*
 @def Function for get the lowest value
 @brief Get lowest number
 @example mmin(2,1)
 @param n1, n2 Numbers to compare
 @return Lowest value
*/
template<typename T>
const T& mmin(const T& n1, const T& n2) {
    return (n1 <= n2) ? n1 : n2;
}
/*
 @def Function for get the highest value
 @brief Get highest number
 @example mmax(2,1)
 @param n1, n2 Numbers to compare
 @return Highest value
*/
template<typename T>
const T& mmax(const T& n1, const T& n2) {
    return (n1 >= n2) ? n1 : n2;
}
/*
 @def Function for get if the values are the same
 @brief Check if the values are the same
 @example maeq(2,1)
 @param n1, n2 Numbers to compare
 @return true or false
*/
template<typename T> 
bool maeq(const T& n1, const T& n2) {
    return (n1 == n2) ? true : false;
}
/*
 @def Function for get the fibonacci of a number
 @brief Get the fibonacci of a number
 @example mfib(2)
 @param n Numbers to calculate
 @return Fibonacci of n
*/
template<typename T>
T mfib(const T& n) {
    if (n <= 1) {
        return n;
    } else {
        return mfib(n - 1) + mfib(n - 2); // corrected function name to mfib
    }
}
/*
 @def Function for generating a random number with a minimun number and a maximun number
 @brief Generate a random number inside bounds
 @example mran(0,4)
 @param minNumber Minimun number
 @param maxNumber Maximun number
 @return Random number between minNumber and maxNumber
*/
template <typename T>
T mran(T minNumber, T maxNumber) {
    std::random_device rd;
    std::mt19937 gen(rd());
    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> distribution(minNumber, maxNumber);
        return distribution(gen);
    } else {
        std::uniform_real_distribution<T> distribution(minNumber, maxNumber);
        return distribution(gen);
    }
}
/*
 @def Function for getting the mediam of a vector<class T> array
 @brief Get the median of a vector
 @example mmed(numbers)
 @param v List of numbers
 @return Median number on v list
 @throw invalid_argument v is empty
*/
template <typename T>
T mmed(const std::vector<T>& v) {
    if (v.empty()) {
        throw std::invalid_argument("Cannot compute median of an empty vector");
    }

    std::vector<T> sorted_v = v;
    std::sort(sorted_v.begin(), sorted_v.end());

    size_t size = sorted_v.size();
    size_t mid = size / 2;

    if (size % 2 == 0) {
        // Even number of elements, average the middle two
        return (sorted_v[mid - 1] + sorted_v[mid]) / 2;
    } else {
        // Odd number of elements, return the middle one
        return sorted_v[mid];
    }
}