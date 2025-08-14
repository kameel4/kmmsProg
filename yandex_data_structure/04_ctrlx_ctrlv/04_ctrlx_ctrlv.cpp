/*
Петя решил написать свой собственный текстовый редактор.
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

Формат ввода:
Программе на вход подаётся набор строк, разделённых переносом строки. Длина каждой строки не превышает 3000 символов.
Последняя строка в файле является пустой. Она означает завершение ввода файла. Других пустых строк в файле быть не может.
После этого и до окончания ввода программе подаются команды Down, Up, Ctrl+X, Ctrl+V.

Формат вывода:
Выведите получившийся файл построчно.
*/

#include <fstream>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>

int main() {
    try {
		/* 
			Я бы разбил текст и список действий на два разных файла: 
			text_file.txt, actions_file.txt.
			
			Тогда код считывания данных задачи был бы более понятен
			и с именованиями переменных было бы полегче.
			+ Логичнее: разные виды данных приходят из разных источников.
		*/
        std::ifstream in("input.txt");

        if (!in.is_open()) {
            throw std::runtime_error("Файл входных данных input.txt отсутсвует!");
        }

		std::list<std::string> input_text;
        std::string line;
        while (std::getline(in, line) && !line.empty()) {
            input_text.push_back(line);
        }

		// action чаще употребляется и + короче
        std::string operation;
        std::string clipboard = "";
		// Это итератор и в названии это часто отражают.
        auto pointed_line_iter = input_text.begin();
		const std::string down_operation = "Down";
		const std::string up_operation = "Up";
		const std::string cut_operation = "Ctrl+X";
		const std::string paste_operation = "Ctrl+V";
        while (std::getline(in, operation)) {
            if (operation == down_operation && pointed_line_iter != --input_text.end()) {
                pointed_line_iter++;
            } else if (operation == up_operation && pointed_line_iter != input_text.begin()) {
                pointed_line_iter--;
            } else if (operation == cut_operation && (!(*pointed_line_iter).empty())) {
                clipboard = *pointed_line_iter;
                
                // Избежание инвалидации, в случае удаления последнего элемента
                if (pointed_line_iter == --input_text.end()) {
                    input_text.erase(pointed_line_iter);
					// Должно быть объяснение: "В чём смысл добавки пустого символа?"
                    input_text.push_back("");
                    pointed_line_iter = --input_text.end();
                } else {
                    pointed_line_iter = input_text.erase(pointed_line_iter);
                }
            } else if (operation == paste_operation && !clipboard.empty()) {
                input_text.insert(pointed_line_iter, clipboard);
            }
        }

        std::ofstream out("output.txt");
        for (std::string output_string: input_text) {
            if (!output_string.empty()) out << output_string << std::endl;
        }

        std::cout << "Задача выполнена. Смотри результат в файле 04_output.txt" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
