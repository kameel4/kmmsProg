/*
Напишите программу, которая будет обрабатывать последовательность запросов таких видов:

1. CLEAR — сделать очередь с приоритетами пустой (если в очереди уже были какие-то элементы, то удалить все).
2. ADD n — добавить в очередь с приоритетами число n (вмещается в стандартный тип int).
3. EXTRACT — вынуть из очереди с приоритетами максимальное значение.

Следует изменить данные в памяти и вывести на экран найденное максимальное значение,
или, если очередь была пустой, слово CANNOT.

Формат ввода:
Во входных данных записана произвольная последовательность запросов CLEAR, ADD и EXTRACT — каждый в отдельной строке.
Суммарное количество всех запросов не превышает 200000.

Формат вывода:
Для каждого запроса типа EXTRACT выведите его результат в отдельной строке.
*/

#include <fstream>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>

int main(){
    try{
        std::ifstream in("input.txt");

        if (!in.is_open()){
            std::runtime_error("Файл входных данных input.txt отсутствует!");
        }

        std::priority_queue<int> queue;
        std::ofstream out("output.txt");
        std::string clear_command  = "CLEAR";
        std::string add_command = "ADD";
        std::string extract_command = "EXTRACT";
        std::string command;
        bool first = true;
        int number_to_add;
        while (in >> command){
            if (command == add_command){
                in >> number_to_add;
                queue.push(number_to_add);
            } else if (command == clear_command){
                while (!queue.empty())
                {
                    queue.pop();
                }
            }else{
                if (first){
                    first = false;
                }else{
                    out << std::endl;
                }

                if (queue.empty()) {
                    out << "CANNOT";
                }else{
                    out << queue.top();
                    queue.pop();
                }
            }
        }
        
        std::cout<< "Задача выполнена. Смотри результат в файле output.txt" << std::endl;
    } catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}