/*
На вход подаётся последовательность целых чисел.
Для каждого числа выведите в отдельной строке слово YES,
если это число ранее встречалось в последовательности, и NO, если не встречалось.

Формат ввода
Вводится список чисел. Все числа списка находятся на одной строке и разделены пробелом.
Каждое число представимо типом int.

Формат вывода
Выведите ответ на задачу.
*/

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>

int main(){
    std::unordered_set<int> numbers;

    try{
        std::ifstream in ("input.txt");

        if (!in.is_open()){
            throw std::runtime_error("Файл входных данных input.txt отсутствует!");
        }

        int current_number = 0;
        std::ofstream out("output.txt");
        while (in >> current_number){
            if (numbers.contains(current_number)){
                out<< "YES";
            }else{
                out<< "NO";
                numbers.insert(current_number);
            }
        }

        std::cout<< "Задача выполнена. Смотри результат в файле output.txt" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

}