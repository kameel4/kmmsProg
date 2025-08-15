/*
Требуется написать шаблонную функцию Duplicate, которая получает на вход вектор
и дублирует все его элементы в конце вектора.
Например, из вектора с элементами 1, 2, 3 должен получиться вектор с элементами
1, 2, 3, 1, 2, 3. Вася написал вот такую реализацию, которая почему-то не работает:

#include <vector>

template <typename T>
void Duplicate(std::vector<T>& v) {
    for (auto it = v.begin(); it != v.end(); ++it) {
        v.push_back(*it);
    }
}
    
Вам надо исправить код Васи.
*/

#include <vector>

template <typename T>
void Duplicate(std::vector<T>& v) {
    v.reserve(v.size()*2);
    const auto original_end = v.end();
    for (auto it = v.begin(); it != original_end; ++it) {
        v.push_back(*it);
    }
}
