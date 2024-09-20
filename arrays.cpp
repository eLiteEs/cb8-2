/*
  @author: Blas - eLite (c) 2024
  @def Functions to work with Arrays
  @copyright eLite (c) 2024
  @category arrays, sorting
  @since 1.0
*/

#include "imports.cpp"

/*
 @def Function for sorting a Number, double, float, long or short numbers array from minumun to max.
 @brief Sort a number array from min to max.
 @example sortbmin(numbervector)
 @param vec Vector to sort
 @return Nothing: it replaces the vector's content
*/
template<typename T>
void sortbmin(std::vector<T>& vec) {
    std::sort(vec.begin(), vec.end());
}
/*
 @def Function for sorting a Number, double, float, long or short numbers array from max to minumun.
 @brief Sort a number array from max to min.
 @example sortbmax(numbervector)
 @param vec Vector to sort
 @return Nothing: it replaces the vector's content
*/
template<typename T>
void sortbmax(std::vector<T>& vec) {
    std::sort(vec.begin(), vec.end(), std::greater<T>());
}
/*
 @def Function for sorting an array of String from numbers to uppercase characters to lowercase characters and symbols.
 @brief Sort a String array using abc.
 @example sortbcha(stringvector)
 @param v Vector to sort
 @return Nothing: it replaces the vector's content
*/
void sortbcha(std::vector<std::string>& v) {
    auto customComparator = [](const std::string& a, const std::string& b) -> bool {
        auto getCategoryAndValue = [](const std::string& str) -> std::pair<int, std::string> {
            if (!str.empty()) {
                char firstChar = str[0];
                if (std::isdigit(firstChar)) return {0, str};
                if (std::isupper(firstChar)) return {1, str};
                if (std::islower(firstChar)) return {2, str};
            }
            return {3, str};
        };

        auto [categoryA, valueA] = getCategoryAndValue(a);
        auto [categoryB, valueB] = getCategoryAndValue(b);

        if (categoryA != categoryB) {
            return categoryA < categoryB;
        }

        return valueA < valueB;
    };

    std::sort(v.begin(), v.end(), customComparator);
}
/*
 @def Function for shuffle an array.
 @brief Shuffle a vector.
 @example rondomize(vector)
 @param v Vector to shuffle
 @return Nothing: it replaces the vector's content
*/
template<typename T>
void randomize(std::vector<T>& v) {
    // Use a random device as a source of randomness
    std::random_device rd;

    // Use a random number engine with the random device as seed
    std::mt19937 gen(rd());

    // Shuffle the vector using the random number engine
    std::shuffle(v.begin(), v.end(), gen);
}
/*
 @def Function for getting a random item from an array.
 @brief Get a random item from an array.
 @example getrandi(vector)
 @param v Vector to get item
 @return Type of vector content: random item from that vector
*/
template<typename T>
T getrandi(const std::vector<T>& vec) {
    // Use a random device as a source of randomness
    std::random_device rd;

    // Use a random number engine with the random device as seed
    std::mt19937 gen(rd());

    // Generate a random index within the bounds of the vector
    std::uniform_int_distribution<size_t> dist(0, vec.size() - 1);
    size_t randomIndex = dist(gen);

    // Return the element at the random index
    return vec[randomIndex];
}
/*
 @def Function for split an array in equal parts
 @brief Split an array.
 @example splitv(vector, 4)
 @param vec Vector to split
 @param parts Cuantity of parts to split
 @return vector<vector<type of initial vector content>>: vector of splitted vectors.
*/
template<typename T>
std::vector<std::vector<T>> splitv(const std::vector<T>& vec, size_t parts) {
    std::vector<std::vector<T>> result;

    // Calculate the size of each segment
    size_t segmentSize = vec.size() / parts;
    size_t remainder = vec.size() % parts;

    // Initialize iterators
    auto it = vec.begin();
    auto end = vec.end();

    // Split the vector into parts
    for (size_t i = 0; i < parts; ++i) {
        size_t segmentLength = segmentSize + (i < remainder ? 1 : 0);
        result.push_back(std::vector<T>(it, it + segmentLength));
        it += segmentLength;
    }

    return result;
}