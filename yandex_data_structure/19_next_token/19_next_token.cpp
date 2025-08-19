/*
Вам надо написать функцию NextToken для выделения очередного токена в строке.
Токеном считается последовательность символов до указанного символа-разделителя (или до конца строки).

Использоваться функция будет примерно так:

int main() {
    std::string_view sv = "Hello world and good bye";

    const char delimiter = ' ';
    std::string_view token;

    // Делим строку на токены по разделителю и перебираем эти токены:
    while (NextToken(sv, delimiter, token)) {
        // обрабатываем очередной token
        // например, печатаем его на экране:
        std::cout << token << "\n";
    }
}
    
Результатом выполнения такой программы будет:

Hello
world
and
good
bye

Сдайте только код функции NextToken и подключите необходимые библиотеки.
Ваша функция будет скомпилирована с нашей функцией main.
Гарантируется, что входная строка не заканчивается на разделитель.
Догадайтесь сами, какие аргументы должна принимать функция NextToken.
Эта функция может менять первый аргумент (sv).*/

#include <fstream>
#include <iostream>
#include <string>

bool NextToken(std::string_view& sv, const char delimiter, std::string_view& token){
    if (sv.empty()) return false;

    int last_delimiter_index = 0;
    for (int i = 0; i < sv.size(); i++){
        if (sv[i] != delimiter){
            last_delimiter_index = i;
            break;
        }
    }

    if (last_delimiter_index == 0 && sv[0] == delimiter) return false;

    token = sv.substr(last_delimiter_index,
         sv.find(delimiter, last_delimiter_index) - last_delimiter_index);

    int new_delimiter_index = last_delimiter_index + token.size();
    sv = sv.substr(new_delimiter_index, sv.size());
    return true;
}

int main() {
    std::string_view sv = "         Hello    w  and good      bye";

    const char delimiter = ' ';
    std::string_view token;
    std::ofstream out("output.txt");

    // Делим строку на токены по разделителю и перебираем эти токены:
    while (NextToken(sv, delimiter, token)) {
        // обрабатываем очередной token
        // например, печатаем его на экране:
        out << token << "\n";
    }
}