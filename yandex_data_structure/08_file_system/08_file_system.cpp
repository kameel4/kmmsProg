/*
Дан список всех файлов в некоторой файловой системе.
Необходимо вывести все непустые директории этой файловой системы в лексикографическом порядке.

Гарантируется, что все пути начинаются от корня файловой системы.
Все пути состоят из слешей (/), латинских символов, цифр и точек.
Два слеша никогда не стоят подряд.

Формат ввода
На вход подаются строки, описывающие пути ко всем файлам в системе.
Каждый путь содержится в отдельной строке. Число строк не превосходит 10000.

Формат вывода
Выведите все непустые директории в этой файловой системе в лексикографическом порядке.
Каждый путь должен начинаться со слеша и заканчиваться слешом.
*/

#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>

int main(){
    std::set<std::string> non_empty_directories;

    try{

        std::ifstream in("input.txt");

        if (!in.is_open()){
            throw std::runtime_error("Файл входных данных input.txt отсутствует!");
        }

        std::string current_path;
        std::string substring;
        while (std::getline(in, current_path)){
            for (std::string::iterator it = current_path.begin(); it != current_path.end(); it++){
                substring = current_path.substr(0, it - current_path.begin());
                if (*it == '/' && substring != "/" && !substring.empty()){
                    non_empty_directories.insert(substring + "/");
                }
            }
        }

        std::ofstream out("output.txt");
        out<<"/";
        for (std::string dir: non_empty_directories){
            out << std::endl << dir;
        }

        std::cout<< "Задача выполнена. Смотри результат в файле 04_output.txt" << std::endl;
    } catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}