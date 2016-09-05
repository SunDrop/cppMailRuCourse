/**
 * Напишите на языке C/C++ программу,
 * определяющую номер треугольного числа
 * (см. также последовательность A000217 в «Энциклопедии целочисленных последовательностей»).
 * @link https://oeis.org/A000217
 *
 * Примечание: число 0 (ноль) не считается принадлежащим ряду,
 * который считается начинающимся с единицы: 1, 3, 6, 10, 15, 21, 28, ...
 *
 * Вход: одно целое (возможно, со знаком «плюс» и символом «перевод строки» \n)
 * число в диапазоне от 1 до 9'223'372'036'854'775'807.
 *
 * Выход: порядковый номер поданного на вход числа в последовательности треугольных чисел
 * или 0 (ноль), если такого числа в последовательности нет.
 * Символ 0 (ноль) должен выдаваться и во всех случаях подачи на вход некорректных
 * (отрицательных и лежащих вне допустимого диапазона положительных числовых, а также символьных / строковых) данных.
 *
 * Sample Input:
 * 10
 * Sample Output:
 * 4
 */

#include <iostream>
#include <regex>
#include <climits>

uint64_t readNumber();

uint64_t getSequenceNum(uint64_t number);

int main_1_1() {
    std::cout << getSequenceNum(readNumber());
    return 0;
}

uint64_t readNumber() {
    uint64_t number(0);
    std::string inputString("");
    try {
        getline(std::cin, inputString);
        if (std::regex_match(inputString, std::regex("\\+?[0-9]+"))) {
            number = std::strtoul(inputString.c_str(), nullptr, 10);
            if (number > LLONG_MAX || number <= 0) {
                throw std::out_of_range(inputString + " incorrect");
            }
        }
    }
    catch (...) {
        number = 0;
    }
    return number;
}

uint64_t getSequenceNum(uint64_t number) {
    if (!number) {
        return 0;
    }
    double_t root(0);
    root = (1.0 - sqrt(1.0 + 8.0 * number)) / -2.0;
    double result(0);
    if (0.0 == std::modf(root, &result)) {
        return static_cast<uint64_t >(result);
    }

    return 0;
}
