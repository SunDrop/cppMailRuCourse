/**
 * Напишите возвращающую bool шаблонную функцию compare, которая принимает две константные ссылки на объекты одного типа и указатель на константный метод этого типа без параметров, который в свою очередь возвращает значение какого-то второго типа. Функция должна сравнивать объекты по значениям, которые для них вернёт соответствующий метод, и возвращать true, если значение для первого объекта оказалось меньше, чем для второго.

 * Пример использования функции compare:
 * std::string s1("Elf");
 * std::string s2("Archer");
 * 
 * // сравнение строк по длине
 * bool r1 = compare(s1, s2, &std::string::size); // true
 * bool r2 = compare(s1, s1, &std::string::size); // false

//template<...>
//... compare(... a, ... b, ... mptr)
//{
//
//}

 */


#include <string>
#include <iostream>

template< typename T, typename R>
bool compare(T const & s1, T const & s2, R (T::* mptr)() const) {
    return (s1.*mptr)() < (s2.*mptr)();
}

int main() {
    std::string s1("Elf");
    std::string s2("Archer");

    bool r1 = compare(s1, s2, &std::string::size); // true
    bool r2 = compare(s1, s1, &std::string::size); // false

    std::cout << "1: " << (int)r1 << std::endl;
    std::cout << "2: " << (int)r2 << std::endl;
    return 0;
}