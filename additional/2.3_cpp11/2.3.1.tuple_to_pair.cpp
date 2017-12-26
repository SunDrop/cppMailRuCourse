/**
 * Напишите шаблонную функцию to_pair,
 * которая принимает произвольный std::tuple и два индекса внутри
 * и возвращает std::pair,
 * содержащий элементы переданного std::tuple с соответствующими индексами.
 * 
 * Пример:
 *
 * auto t = std::make_tuple(0, 3.5, "Hello");
 * std::pair<double, char const *> p = to_pair<1,2>(t); 
 * // p содержит 3.5 и "Hello"
 */

#include <iostream>
#include <tuple>



template<int a, int b, class ... Args>
auto to_pair(std::tuple<Args...> t)
-> decltype(std::make_pair(std::get<a>(t), std::get<b>(t)))
{
    return std::make_pair(std::get<a>(t), std::get<b>(t));
}

int main() {
    auto t = std::make_tuple(0, 3.5, "Hello");
    std::pair<double, char const *> p = to_pair<1,2>(t);

    return 0;
}