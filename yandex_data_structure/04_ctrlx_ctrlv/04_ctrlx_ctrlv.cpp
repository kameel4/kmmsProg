/*
Петя решил написать свой собственный текстовый редактор
На текущей стадии разработки в редакторе есть только возможность загрузить файл и выполнять с ним такие действия:
переместить курсор на строчку вниз (Down)
переместить курсор на строчку вверх (Up)
вырезать текущую строку в буфер обмена (Ctrl+X)
вставить строку из буфера перед текущей строкой (Ctrl+V)

Изначально курсор находится на первой (начальной) строке.

Операции Down с курсором на последней строке и Up с курсором на первой строке должны игнорироваться.

Любой текстовый файл в системе заканчивается переводом строки. Поэтому последняя строка любого файла является пустой.
Операция Ctrl+X на пустой строке ничего не делает.

Изначально буфер редактора пустой. Операция Ctrl+X перезаписывает буфер, если в нём уже было какое-то значение.
Операция Ctrl+V не очищает буфер и может быть использована несколько раз подряд.
Операция Ctrl+V при пустом буфере ничего не делает.

Напишите программу, которая по заданному файлу и набору команд выводит получившийся файл.

Формат ввода
Программе на вход подаётся набор строк, разделённых переносом строки. Длина каждой строки не превышает 3000 символов.
Последняя строка в файле является пустой. Она означает завершение ввода файла. Других пустых строк в файле быть не может.
После этого и до окончания ввода программе подаются команды Down, Up, Ctrl+X, Ctrl+V.

Формат вывода
Выведите получившийся файл построчно.
*/

#include <fstream>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>

int main(){
    std::list<std::string> file_txt;

    try {
        std::ifstream in("input.txt");

        if (!in.is_open()){
            throw std::runtime_error("Файл входных данных input.txt отсутсвует!");
        }

        std::string data;
        while (std::getline(in, data) && data != ""){
            file_txt.push_back(data);
        }

        std::string operation;
        std::string clipboard = "";
        auto pointed_line = file_txt.begin();
        while (std::getline(in, operation))
        {
            if (operation == "Down" && pointed_line != --file_txt.end()){
                pointed_line++;
            }else if (operation == "Up" && pointed_line != file_txt.begin()){
                pointed_line--;
            }else if (operation == "Ctrl+X" && (!(*pointed_line).empty())){
                clipboard = *pointed_line;
                
                // Избежание инвалидации, в случае удаления последнего элемента
                if (pointed_line == --file_txt.end()){
                    file_txt.erase(pointed_line);
                    file_txt.push_back("");
                    pointed_line = --file_txt.end();
                }else{
                    pointed_line = file_txt.erase(pointed_line);
                }
            }else if (operation == "Ctrl+V" && !clipboard.empty()){
                file_txt.insert(pointed_line, clipboard);
            }
        }

        std::ofstream out("output.txt");
        for (std::string output_string: file_txt){
            if (output_string !="") out << output_string << std::endl;
        }

        std::cout<< "Задача выполнена. Смотри результат в файле 04_output.txt" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}