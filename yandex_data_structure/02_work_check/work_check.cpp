/*
N студентов сдают свои работы в общую стопку, причем некоторые кладут свою работу сверху,
а другие (считая, что чем позже их работу проверят, тем лучше) — снизу.
Проверяются работы в том порядке, в котором лежат, начиная с верхней.
Определите, чья работа будет проверена k-й по счёту.

Формат ввода
Первая строка содержит одно натуральное число
N, не превосходящее 10000, — число студентов.
Каждая из последующих N строк содержит фамилию студента — строку из латинских
букв длиной от 2 до 10 символов, и через пробел слово top или
bottom — положил этот студент свою работу сверху или снизу.
Следующая строка содержит одно целое число M от 0 до 10000 —
для какого числа работ нужно определить их автора.
Следующие M строк содержат по одному числу x от 1 до N
N — номер в стопке очередной интересующей нас работы.

Формат вывода
Выведите M строк. В i-й строке выведите фамилию студента, чья работа будет проверена Xi-й по счёту.
*/


#include <deque>
#include <fstream>
#include <iostream>
#include <string>

int main(){
    std::deque<std::string> stopka;

    try{
        std::ifstream in("input.txt");
        if (!in.is_open()){
            throw std::runtime_error("Файл входных данных input.txt отстутсвует!");
        }

        int num_of_works;
        in >> num_of_works;

        for (int i = 0; i<num_of_works; ++i){
            std::string last_name, deque_end;
            in>> last_name >> deque_end;

            if (deque_end == "top"){
                stopka.push_back(last_name);
            }else{
                stopka.push_front(last_name);
            }

        }

        int num_of_requests;
        in >> num_of_requests;

        std::ofstream out("output.txt");

        for (int i = 0; i<num_of_requests; ++i){
            int work_index;
            in>>work_index;
            out<<stopka[num_of_works - work_index]<<std::endl;
        }

        std::cout << "Задача выполнена. Смотри результат в файле output.txt" << std::endl;
    } catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}