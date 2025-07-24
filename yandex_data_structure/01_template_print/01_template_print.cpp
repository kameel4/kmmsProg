/*
Вам надо написать функцию Print, которая умеет печатать в поток std::cout элементы переданного контейнера через
указанную строку-разделитель. Первый аргумент функции — контейнер. Гарантируется, что по этому контейнеру можно
проитерироваться с помощью стандартного цикла range-based for, и что элементы контейнера можно напечатать в поток
std::cout с помощью стандартного оператора <<. Второй аргумент функции — строка-разделитель, которую надо печатать
между элементами. В конце необходимо напечатать перевод строки \n.

Примечание
В вашем решении должен быть только код функции Print без функции main.
Подключите все необходимые для реализации библиотеки.
Используйте константные ссылки для получения параметров и при итерации в цикле,
чтобы избежать лишних копирований: если этого не сделать, то программа не скомпилируется.
*/

#include <iostream>
#include <string>
#include <vector>

template <typename Container>
void print(
    const Container& data,
    const std::string& delimiter
    );

int main() {
    std::vector<int> data = {1, 2, 3};
    print(data, ", ");  // 1, 2, 3
}


template <typename Container>
void print(const Container& data, const std::string& delimiter) {
    for (auto iter = std::begin(data); iter != std::end(data); ++iter) {
        std::cout << *iter;
        if (std::next(iter) != std::end(data)) {
            std::cout << delimiter;
        }
    }
    std::cout << std::endl;
}