/*
На вход подаётся скобочная последовательность — строка, которая состоит из скобок ()[]{}.
Вам нужно определить, является ли она правильной. 
В правильной скобочной последовательности каждой открывающей скобке соответствует закрывающая и
пары скобок корректно вложены друг в друга.

Формат ввода:
Строка, состоящая из символов ()[]{}.

Формат вывода:
Напечатайте YES, если скобочная последовательность является правильной, и NO в противном случае.
*/

#include <fstream>
#include <iostream>
#include <stack>
#include <stdexcept>

int main(){
    try{
        std::ifstream in("input.txt");

        if (!in.is_open()){
            std::runtime_error("Файл входных данных input.txt отсутствует!");
        }

        std::stack<char> bracket_sequence;
        char open_brace = '{', close_brace = '}';
        char open_paren = '(', close_paren = ')';
        char open_bracket = '[', close_bracket = ']';
        char current_char;
        std::ofstream out("output.txt");
        bool is_sequence_correct = true;

        while (in >> current_char){
            if (current_char == open_brace ||
                current_char == open_paren ||
                current_char == open_bracket){
                    bracket_sequence.push(current_char);
            }else{
                if (bracket_sequence.empty()){ is_sequence_correct = false; break; }

                if ((current_char == close_brace && bracket_sequence.top() == open_brace) ||
                    (current_char == close_paren && bracket_sequence.top() == open_paren) ||
                    (current_char == close_bracket && bracket_sequence.top() == open_bracket)){
                    bracket_sequence.pop();
                }else{
                    is_sequence_correct = false; break;
                }
            }
        }

        if (is_sequence_correct && bracket_sequence.empty()){
            out << "YES";
        }else{
            out << "NO";
        }

        std::cout<< "Задача выполнена. Смотри результат в файле output.txt" << std::endl;
    } catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}