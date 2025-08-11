/*
Вам даны слова. Выведите в алфавитном порядке список общих букв всех слов.

Формат ввода
На вход поступают слова (по одному в строке), состоящие из маленьких латинских букв алфавита. Длина слов не превосходит 100 символов, а количество слов не превосходит 1000.

Формат вывода
Выведите в алфавитном порядке без пробелов список букв, которые присутствуют в каждом слове.
*/

#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_set>

int main(){
    std::map<char, int> letters;

    try{
        std::ifstream in ("input.txt");

        if (!in.is_open()){
            throw std::runtime_error("Файл входных данных input.txt отсутствует!");
        }

        std::string word;
        std::unordered_set<char> seen;
        int words_counter = 0;
        while (in >> word){
            words_counter++;
            for (char c: word){
                if (!seen.contains(c)){
                    letters[c]++;
                    seen.insert(c);
                }
            }
            seen.clear();
        }

        std::ofstream out("output.txt");
        for (const auto& [c, freq] : letters){
            if(freq == words_counter){
                out<< c;
            }
        }

        std::cout<< "Задача выполнена. Смотри результат в файле output.txt" << std::endl;
    } catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}