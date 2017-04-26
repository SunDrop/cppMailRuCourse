/**
 * Задача простая - найти производную многочлена.
 * Многочлен может быть большой, но только с неотрицательными целыми степенями и целыми коэффициентами.
 * Подумайте, каким образом его лучше представить в памяти?
 *
 * Вывод должен быть без пробелов и в порядке убывания степеней, хотя ввод этому правилу может не удовлетворять.
 * Также на ввод может быть подан многочлен с неприведенными слагаемыми.
*/

#include <iostream>
#include <map>
#include <vector>
#include <regex>

std::string trim(const std::string &str, const char &trim = ' ') {
    size_t first = str.find_first_not_of(trim);
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(trim);
    return str.substr(first, (last - first + 1));
}

bool isDelimiter(const char &c, const std::string &delimiters) {
    for (int i = 0; i < delimiters.size(); ++i) {
        if (delimiters[i] == c) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> splitString(std::string input, std::string delimiters) {
    std::vector<std::string> out;
    std::string word = "";
    for (auto const &c: input) {
        if (c == ' ') {
            continue;
        }
        if (isDelimiter(c, delimiters)) {
            if (!word.empty()) {
                out.push_back(trim(word, '+'));
                word = "";
            }
        }
        word.push_back(c);
    }
    out.push_back(trim(word, '+'));

    return out;
}

class Polynomial {
private:
    std::map<const int, int, std::greater<int>> polynomial;

public:
    Polynomial() {};

    Polynomial(std::string s) {
        this->fromString(s);
    };

    void fromString(std::string init) {
        std::regex regex("(\\-?[0-9]*)\\*?x\\^?([0-9]*)");
        auto members = splitString(init, "-+");
        for (auto const &member: members) {
            int pow = 0, cof = 1;
            if (std::regex_match(member, regex)) {
                std::smatch match;
                std::regex_match(member, match, regex);

                try {
                    pow = stoi(match[2]);
                } catch (std::invalid_argument) {
                    pow = 1;
                }

                try {
                    cof = stoi(match[1]);
                } catch (std::invalid_argument) {
                    cof = match[1] == "-" ? -1 : 1;
                }

                polynomial[pow] += cof;
            }
        }
    }

    static std::string simplifyPow(int pow) {
        if (pow == 1) {
            return "";
        }

        return "^" + std::to_string(pow);
    }

    static std::string simplifyCof(int cof) {
        if (cof == 1) {
            return "+";
        } else if (cof == -1) {
            return "-";
        } else if (cof > 1) {
            return "+" + std::to_string(cof) + "*";
        }

        return std::to_string(cof) + "*";
    }

    std::string derivative() {
        std::string out = "";
        int pow, cof;
        for (auto const &a: polynomial) {
            cof = a.second * a.first;
            pow = a.first - 1;

            if (pow) {
                out += Polynomial::simplifyCof(cof);
                out += "x";
                out += Polynomial::simplifyPow(pow);
            } else {
                if (cof > 0) {
                    out += "+" + std::to_string(cof);
                } else {
                    out += std::to_string(cof);
                }
            }
        }

        return trim(out, '+');
    }

    std::string toString() {
        std::string out = "";
        for (auto const &a: polynomial) {
            out += Polynomial::simplifyCof(a.second);
            out += "x";
            out += Polynomial::simplifyPow(a.first);
        }
        return trim(out, '+');
    }

    void print() {
        std::cout << toString() << std::endl;
    }
};

std::string derivative(std::string polynomial) {
    Polynomial p(polynomial);
    return p.derivative();
}


int main() {
    std::cout << derivative("x^2+x") << std::endl;
    std::cout << derivative("2*x+1") << std::endl;
    std::cout << derivative("2*x^100+100*x^2") << std::endl;
    std::cout << derivative("200*x^99+200*x") << std::endl;
    std::cout << derivative("x^10000+x+1") << std::endl;
    std::cout << derivative("-x^2-x^3") << std::endl;
    std::cout << derivative("-3*x^2-2*x") << std::endl;
    std::cout << derivative("x+x+x+x+x+x+x+x+x+x") << std::endl;
    std::cout << derivative("10") << std::endl;
    std::cout << derivative("-100+200 - x + 2*x^1 - x^2 - x^3") << std::endl;

    return 0;
}