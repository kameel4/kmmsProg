/*
В этой задаче нужно применить функцию std::lower_bound и итераторы
для быстрого поиска ближайшего элемента в отсортированном массиве.

Формат ввода:
В первой строке входных данных содержатся натуральные числа n и k, не превосходящие 100000.
Во второй строке задаются n целых чисел первого массива, отсортированного по неубыванию,
а в третьей строке – k целых чисел второго массива.
Каждое число в обоих массивах по модулю не превосходит 2 * 10^9.
Второй массив, в отличие от первого, не отсортирован.

Формат вывода:
Для каждого из k чисел выведите в отдельной строке число из первого массива,
наиболее близкое к данному. Если таких несколько, выведите меньшее из них.
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

int main(){
    try{
        std::ifstream in("input.txt");

        if (!in.is_open()){
            throw std::runtime_error("Файл входных дынных input.txt отсутсвует!");
        }
        // смысловое значение переменных n и k смотрите в описании задачи
        int n, k;
        in >> n >> k;

        // Будет ли эффективнее использовать array?
        std::vector<int> vector_to_choose_from;

        int elem_to_add;
        for (int i = 0; i < n; i++){
            in >> elem_to_add;
            vector_to_choose_from.push_back(elem_to_add);
        }

        int elem_to_approximate;
        int abs_diff_lower;
        int abs_diff_upper;
        auto begin = vector_to_choose_from.begin(), end = vector_to_choose_from.end() - 1;
        bool first = true;
        std::ofstream out("output.txt");
        for (int i = 0; i < k; i++){
            if (first){
                first = false;
            }else{
                out << std::endl;
            }

            in >> elem_to_approximate;
            auto lower_bound_iter = std::lower_bound(begin, end, elem_to_approximate);
            
            if (lower_bound_iter == begin || *lower_bound_iter == elem_to_approximate ||
            elem_to_approximate > *end){
                out << *lower_bound_iter;
            }else{
                abs_diff_lower = abs(*(lower_bound_iter - 1) - elem_to_approximate);
                abs_diff_upper = abs(*lower_bound_iter - elem_to_approximate);
                if (abs_diff_lower <= abs_diff_upper){
                    out << *(lower_bound_iter - 1);
                }else{
                    out << *lower_bound_iter;
                }
            }
        }

        std::cout << "Задача выполнена. Смотри результат в файле output.txt" << std::endl;
    }catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}