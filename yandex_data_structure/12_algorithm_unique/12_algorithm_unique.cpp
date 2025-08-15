/*
Вам надо написать свою реализацию стандартного алгоритма unique. Заголовок функции должен быть таким:

template <typename Iter>
Iter Unique(Iter first, Iter last);

Функция должна переупорядочить элементы диапазона [first; last) так,
чтобы подряд идущие одинаковые элементы в ней не встречались.
Функция возвращает итератор за последний элемент итоговой последовательности.
Что останется в пределах от этого вернувшегося итератора до старого last — не важно.
Время работы функции должно линейно зависеть от длины диапазона.
*/

#include <algorithm>


template <typename Iter>
Iter Unique(Iter first, Iter last){
    if (last == first){return last;}

    auto unique_sequence_iter = first;
    auto unique_sequnce_end_iter = last;
    for (auto it = ++first; it != last; it++){
        if (*it != *unique_sequence_iter){
            std::swap(*++unique_sequence_iter, *it);
        }else{
            unique_sequnce_end_iter--;
        }
    }

    return unique_sequnce_end_iter;
}