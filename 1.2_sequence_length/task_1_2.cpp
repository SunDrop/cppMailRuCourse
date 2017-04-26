/**
 * Напишите на языке C/C++ программу поиска максимальной по длине монотонно
 * неубывающей подпоследовательности во входной последовательности вещественных чисел.
 * Если таких подпоследовательностей несколько, выведите первую из них (найденную при просмотре входного потока первой).
 * @link https://ru.wikipedia.org/wiki/%D0%9C%D0%BE%D0%BD%D0%BE%D1%82%D0%BE%D0%BD%D0%BD%D0%B0%D1%8F_%D0%BF%D0%BE%D1%81%D0%BB%D0%B5%D0%B4%D0%BE%D0%B2%D0%B0%D1%82%D0%B5%D0%BB%D1%8C%D0%BD%D0%BE%D1%81%D1%82%D1%8C
 *
 * Примечание: искомая подпоследовательность является «плотной»,
 * в ней нет разрывов и посторонних элементов, включая числовые значения.
 *
 * Вход: одно целое N (длина последовательности; возможно, со знаком «плюс»),
 * за которым следует k вещественных чисел в любой разрешенной форме записи (и, возможно, символ «перевод строки» /n).
 * Если k = N, анализируется входная последовательность вещественных целиком;
 * если k > N, анализируется только N первых (расположенных в традиционной записи слева) членов этой последовательности.
 * Если k < N (возможно, k = 0) или N < 2, входная последовательность некорректна.
 *
 * Выход: два целых (натуральных), первое из которых L соответствует длине,
 * а второе — порядковому номеру i первого элемента найденной подпоследовательности (принять i = 1, 2, 3, ...).
 * Если входная последовательность корректна, но искомая подпоследовательность не обнаружена,
 * вывести символ 0 (ноль). Во всех случаях подачи на вход некорректных,
 * в том числе символьных/строковых данных, вывести строку [error] (вместе с квадратными скобками).
 *
 * Sample Input:
 * 7 1 2 3 4 5 6 7
 * Sample Output:
 * 7 1
 */

#include <sstream>
#include <iostream>
#include <regex>

typedef std::array<int, 2> sequenceResult;

std::string getInputStream();

bool checkInputStream(const std::stringstream &inputStream);

int getSequenceLength(std::stringstream &input);

void compareMax(const sequenceResult &currentSequence, sequenceResult &maxSequence);

sequenceResult findMaxSequence(std::stringstream &input, int sequenceLength);

std::string getResult(std::string input);

#define THROW_ERROR "[error]"
#define THROW_ZERRO 0
#define SEQUENCE_POSITION 0
#define SEQUENCE_LENGTH 1

int main() {
    try {
        std::cout << getResult(getInputStream());
    }
    catch (char const *&e) {
        std::cout << e;
    }
    catch (int &e) {
        std::cout << e;
    }
    return 0;
}

std::string getInputStream() {
    std::string line;
    std::getline(std::cin, line);
    return line;
}

bool checkInputStream(const std::stringstream &inputStream) {
#define REGEXP_IS_FLOAT "((?:\\+|\\-)?(?:(?:\\d+)|(?:\\d+\\.)|(?:\\.\\d+)|(?:\\d+\\.\\d+)){1}(?:(?:e|E)(?:\\+|\\-)?\\d+)?)"
    std::regex rx(std::string("\\+?\\d+\\s") + REGEXP_IS_FLOAT + "(\\s" + REGEXP_IS_FLOAT + "){0,}");
    return std::regex_match(inputStream.str(), rx);
}

int getSequenceLength(std::stringstream &input) {
    int sequenceLength = 0;
    input >> sequenceLength;
    return sequenceLength;
}

void compareMax(const sequenceResult &currentSequence, sequenceResult &maxSequence) {
    if (maxSequence[SEQUENCE_LENGTH] < currentSequence[SEQUENCE_LENGTH] &&
        currentSequence[SEQUENCE_LENGTH] > 1) {
        maxSequence = currentSequence;
        maxSequence[SEQUENCE_POSITION] -= currentSequence[SEQUENCE_LENGTH] - 1;
    }
}

sequenceResult findMaxSequence(std::stringstream &input, int sequenceLength) {
    sequenceResult maxSequence = {0, 0};
    sequenceResult currentSequence = {1, 1};
    double_t currentValue(0);
    double_t previousValue(0);

    input >> previousValue;
    --sequenceLength;

    while (sequenceLength && input >> currentValue) {
        if (currentValue >= previousValue) {
            ++currentSequence[SEQUENCE_LENGTH];
        } else {
            compareMax(currentSequence, maxSequence);
            currentSequence[SEQUENCE_LENGTH] = 1;
        }
        --sequenceLength;
        previousValue = currentValue;
        ++currentSequence[SEQUENCE_POSITION];
    }

    // Если k < N (возможно, k = 0), входная последовательность некорректна.
    if (sequenceLength) {
        throw THROW_ERROR;
    }
    compareMax(currentSequence, maxSequence);

    return maxSequence;
}

std::string getResult(std::string input) {
    std::stringstream inputStream(input);
    if (!checkInputStream(inputStream)) {
        throw THROW_ERROR;
    }
    int sequenceLength = getSequenceLength(inputStream);
    if (sequenceLength < 2) {
        throw THROW_ERROR;
    }
    sequenceResult maxSequence = findMaxSequence(inputStream, sequenceLength);
    if (!maxSequence[SEQUENCE_LENGTH]) {
        throw THROW_ZERRO;
    }
    return std::to_string(maxSequence[SEQUENCE_LENGTH]) + " " + std::to_string(maxSequence[SEQUENCE_POSITION]);
}