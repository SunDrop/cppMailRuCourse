/**
 * Вам нужно создать умный указатель на объект класса std::string.
 * Он должен иметь защиту от разыменования NULL - при попытке это сделать
 * он должен конструировать внутри себя пустую строку.
 *
 * Следующий код должен работать.
 * ```code
 * std::string s1 = "Hello, world!";
 *
 * StringPointer sp1(&s1);
 * StringPointer sp2(NULL);
 *
 * std::cout << sp1->length() << std::endl;
 * std::cout << *sp1 << std::endl;
 * std::cout << sp2->length() << std::endl;
 * std::cout << *sp2 << std::endl;
 * ```code
 *
 * Так как ваш указатель при определенных случаях может конструировать
 * внутри себя пустую строку, не забудьте позаботиться об освобождении памяти в деструкторе.
 * Система не проверяет корректность работы в памятью, так что это остается на вашу совесть :)
 */

#include <iostream>
#include <string>

class StringPointer {
private:
    std::string *sp;
    bool needDelete = false;

    void createIfNull() {
        if (!sp) {
            sp = new std::string();
            needDelete = true;
        }
    }

public:
    StringPointer(std::string *pointer) : sp(pointer) {};

    std::string *operator->() {
        createIfNull();
        return sp;
    };

    operator std::string *() {
        createIfNull();
        return sp;
    };

    ~StringPointer() {
        if (sp && needDelete) {
            delete sp;
            sp = nullptr;
            needDelete = false;
        }
    };
};

int main() {
    std::string s1 = "Hello, world!";

    StringPointer sp1(&s1);
    StringPointer sp2(NULL);

    std::cout << sp1->length() << std::endl;
    std::cout << *sp1 << std::endl;
    std::cout << sp2->length() << std::endl;
    std::cout << *sp2 << std::endl;
    return 0;
}