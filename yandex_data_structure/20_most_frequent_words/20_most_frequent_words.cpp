/*
Выведите k самых частотных слов текста и их частоты.

Формат ввода:
В первой строке указано натуральное число k, не превосходящее 1000.
Далее идут строки текста объёмом до 1 Mб.
Слова в тексте разделены пробелами или переводами строк.
Различать регистр и обрабатывать пунктуацию не нужно.

Формат вывода:
В выводе должно быть не более k самых частотных слов текста.
Через табуляцию после слова напечатайте его частоту.
Слова должны быть упрядочены по убыванию частоты, а при равенстве частот — по алфавиту.
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

int main(){
    try{
        std::ifstream in("input.txt");
        // значение переменной k описано в условии
        int k;
        in >> k;

        std::unordered_map<std::string, int> words_frequency;
        std::string word;
        while(in >> word){
            words_frequency[word]++;
        }

        std::vector<std::pair<std::string, int>> vector_copy_words_frequency(
            words_frequency.begin(),
            words_frequency.end()
        );

        std::sort(
            vector_copy_words_frequency.begin(),
            vector_copy_words_frequency.end(),
            [](const auto& p1, const auto& p2) {
                return std::tie(p2.second, p1.first) < std::tie(p1.second, p2.first);
            }
        );

        std::ofstream out("output.txt");
        if (k > (int) vector_copy_words_frequency.size()) k = vector_copy_words_frequency.size();
        for (int i = 0; i < k; i++){
            if (i != 0) out << std::endl;

            out << vector_copy_words_frequency[i].first << '\t' << vector_copy_words_frequency[i].second;
        }
        
        std::cout<< "Задача выполнена. Смотри результат в файле output.txt" << std::endl;
    } catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}