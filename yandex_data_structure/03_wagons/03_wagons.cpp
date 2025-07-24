/*
Вам поручено реализовать функцию void MakeTrain()

У каждого вагона есть номер (помещается в int). Номера вагонов внутри состава могут повторяться.
Изначально путь, на котором формируется состав, пустой. Вы должны уметь выполнять следующие команды,
которые поступают в отдельных строках на входе:
+left W — добавить вагон с номером W слева
+right W — добавить вагон с номером W справа
-left N — отцепить и убрать N вагонов слева
-right N — отцепить и убрать N вагонов справа

В последних двух командах N может быть больше текущей длины состава — в этом случае надо убрать
весь состав целиком. Отцеплять вагоны по одному может быть долго: постарайтесь сразу отцеплять по N штук.
Напечатайте через пробел номера вагонов получившегося состава, если смотреть на них слева направо.
В самом конце напечатайте перевод строки.

На вход подаются строки с командами в указанном формате. Всего будет не более 1 млн команд.
Оформите ваше решение в функции void MakeTrain(). Эта функция должна читать данные со стандартного
потока ввода и печатать их в стандартный поток вывода. Подключите все необходимые библиотеки.
В вашем решении не должно быть функции main.
*/

#include <deque>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

void MakeTrain(){
    std::deque<int> train;

        try {
            std::ifstream in("input.txt");
            
            if (!in.is_open()) {
			    throw std::runtime_error("Файл входных данных 02_input.txt отсутствует!");
		    }
        

            std::string operation;
            int wagon_number;

            while (in >> operation){
                in>>wagon_number;
                if (operation[0] == '+'){
                    if (operation == "+right") train.push_back(wagon_number);
                    if (operation == "+left") train.push_front(wagon_number);
                }else{
                    wagon_number = std::min(wagon_number, (int)train.size());
                    if (operation == "-left") train.erase(train.begin(), train.begin()+wagon_number);
                    if (operation == "-right") train.erase(train.end() - wagon_number, train.end());
                }
            }

            std::ofstream out("output.txt");
            bool first = true;
            for (int wagon: train){
                if (first){
                    out<<wagon;
                    first = false;
                }else{
                    out<<' '<<wagon;
                }
            }

		    std::cout << "Задача выполнена. Смотри результат в файле output.txt" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
}
