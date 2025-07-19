#include <iostream>
// #include <iterator>
#include <string>

template <typename Container>
void Print(const Container& data, const std::string& delimiter) {
    for (auto iter = std::begin(data); iter != std::end(data); ++iter) {
        std::cout << *iter;
        if (std::next(iter) != std::end(data)) {
            std::cout << delimiter;
        }
    }
    std::cout << "\n";
}