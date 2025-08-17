/*
Рассмотрим последовательность целых чисел длины n. 
По ней с шагом 1 двигается «окно» длины k. 
Другими словами, сначала в «окне» видны первые k чисел,
на следующем шаге в «окне» уже будут находиться k чисел, начиная со второго,
и так далее до конца последовательности.
Требуется для каждого положения «окна» определить в нём минимальное число.

Формат ввода:
В первой строке входных данных содержатся два натуральных числа
n и k — длины последовательности и «окна». При этом n ⩽ 150000, k ⩽ 10000, k ⩽ n.
На следующей строке находятся n чисел — сама последовательность.

Формат вывода:
Выходые данные должны содержать n − k + 1 строк — минимумы для каждого положения «окна».
*/

#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>
#include <vector>


int main(){
    try{
        std::ifstream in("input.txt");

        if (!in.is_open()){
            std::runtime_error("Файл входных данных input.txt отсутствует!");
        }

        int sequence_length, window_length;
        in >> sequence_length >> window_length;

        std::multiset<int> window;
        std::vector<int> sequence(sequence_length);
        int elem_to_add;

        for (int k = 0; k < window_length; k++){
            in >> elem_to_add;
            window.insert(elem_to_add);
            sequence[k] = elem_to_add;
        }

        std::ofstream out("output.txt");
        if (!window.empty()) {
            out << *window.begin();

            auto elem_to_erase_iter = sequence.begin();
            for (int i = 0; i < (sequence_length - window_length); i++){
                out << std::endl;
                

                in >> elem_to_add;
                window.insert(elem_to_add);
                sequence[i + window_length] = elem_to_add;
                window.erase(window.find(*elem_to_erase_iter++));
                out << *window.begin();
            }
        }

        std::cout<< "Задача выполнена. Смотри результат в файле output.txt" << std::endl;
    } catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}