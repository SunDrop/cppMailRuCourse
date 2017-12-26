// Выберите все случаи, где преобразование static_cast<> в правой части обязательно.

int a = 27;
int const b = 412;
int * pa = &a;

int main() {

    int const * const * p4 = const_cast<int const * const *>(&pa);

    return 0;
}