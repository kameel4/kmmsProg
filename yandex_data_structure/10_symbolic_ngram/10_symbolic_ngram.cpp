/*
Будем называть символьной n-граммой последовательность из
n последовательно идущих символов в одном слове в тексте.
Для данного числа n подсчитайте суммарное количество каждой n-граммы в тексте.

Формат ввода
В первой строке заданы два числа: m — число слов в тексте (от 1 до 100000) и n — длина n-граммы (от 1 до 5). 
Далее идет m слов. Можно считать, что слова отделены пробелами или переносами строк.
Обработку пунктуации и регистра реализовывать не нужно. Читайте слова просто через std::cin >> word.

Формат вывода
Выведите все n-граммы, отсортированные по убыванию частоты, а в случае равных частот —
лексикографически (по алфавиту). 
Для каждой n-граммы напечатайте также её частоту (смотрите формат в примере).
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

int main(){
    std::unordered_map<std::string, int> ngrams_frequency;

    try{
        std::ifstream in("input.txt");

        if(!in.is_open()){
            throw std::runtime_error("Файл входных данных input.txt отсутствует!");
        }

        std::string word;
        std::string current_ngram;
        int number_of_words;
        // n - length of n-gram
        int n;

        in >> number_of_words >> n;

        for (int i = 0; i < number_of_words; i++){
            in >> word;
            if (word.size() >= n){
                for (size_t j = 0; j < word.size() - n + 1; j++){
                    current_ngram = word.substr(j, n);
                    ngrams_frequency[current_ngram]++;
                }
            }
        }

        std::vector<std::pair<std::string, int>> sortedByFreq(
            ngrams_frequency.begin(),
            ngrams_frequency.end()
        );

        std::sort(
            sortedByFreq.begin(),
            sortedByFreq.end(),
            [](const auto& p1, const auto& p2) {
                return std::tie(p2.second, p1.first) < std::tie(p1.second, p2.first);
            }
        );


        bool first = true;
        std::ofstream out("output.txt");
        for (const auto& [ngram, freq]: sortedByFreq){
            if (first){
                out<< ngram << " - " << freq;
                first = false;
            }else{
                out << std::endl << ngram << " - " << freq;
            }
        }
        //std::cout<< "Задача выполнена. Смотри результат в файле output.txt" << std::endl;
    }catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}