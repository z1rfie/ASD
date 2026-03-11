#include <iostream>
#include "../lib_monom/monom.h"
#include "../lib_list/list.h"

class Polynom {
    List<Monom> _polynom;
    std::string _name;
public:
    Polynom() {
        Monom zero;
        _polynom.push_back(zero);
    }

    Polynom(const Monom& monom) {
        _polynom.push_back(monom);
    }

    Polynom(const Polynom& other) {
        _polynom = other._polynom;
        _name = other._name;
    }

    Polynom(const std::string& str) {
        int i = 0;
        int n = str.size();

        while (i < n) {
            while (i < n && str[i] == ' ') i++;
            if (i >= n) break;

            double sign = 1.0;
            if (str[i] == '+') { sign = 1.0; i++; }
            else if (str[i] == '-') { sign = -1.0; i++; }
            while (i < n && str[i] == ' ') i++;

            int coef_start = i;
            while (i < n && (isdigit(str[i]) || str[i] == '.')) i++;
            double coef;
            if (i > coef_start) {
                coef = 0.0;
                int j = coef_start;
                while (j < i && isdigit(str[j])) {
                    coef = coef * 10 + (str[j] - '0');
                    j++;
                }
                if (j < i && str[j] == '.') {
                    j++;
                    double fraction = 0.1;
                    while (j < i && isdigit(str[j])) {
                        coef += (str[j] - '0') * fraction;
                        fraction *= 0.1;
                        j++;
                    }
                }
                coef *= sign;
            }
            else {
                coef = sign;
            }

            int powers[VARS_COUNT] = { 0, 0, 0 };
            char vars[] = { 'x', 'y', 'z' };
            while (i < n && str[i] != '+' && str[i] != '-') {
                if (str[i] == ' ') { i++; continue; }

                bool found = false;
                for (int v = 0; v < VARS_COUNT; v++) {
                    if (str[i] == vars[v]) {
                        i++;
                        if (i < n && str[i] == '^') {
                            i++; 
                            int power = 0;
                            while (i < n && isdigit(str[i])) {
                                power = power * 10 + (str[i] - '0');
                                i++;
                            }
                            powers[v] = power;
                        }
                        else {
                            powers[v] = 1;
                        }
                        found = true;
                        break;
                    }
                }
                if (!found) break;
            }

            Monom m(coef, powers);
            *this += m;
        }
    }

    List<Monom>::Iterator begin() const { return _polynom.begin(); }
    List<Monom>::Iterator end() const { return _polynom.end(); }

    Polynom& operator+=(const Monom& other) {
        auto it = _polynom.begin();
        Node<Monom>* prev_node = nullptr;

        while (it != _polynom.end() && *it > other) {
            prev_node = it.get_node();
            ++it;
        }

        if (it != _polynom.end() && *it == other) {
            *it += other;
            return *this;
        }

        if (prev_node == nullptr) {
            _polynom.push_front(other);
        }
        else {
            _polynom.insert(prev_node, other);
        }

        return *this;
    }

    Polynom operator+(const Monom& other) const {
        Polynom res(*this);
        res += other;
        return res;
    }

    Polynom& operator+=(const Polynom& other) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            *this += *it;
        }
        return *this;
    }

    Polynom operator+(const Polynom& other) const {
        Polynom res(*this);
        res += other;
        return res;
    }

    Polynom& operator-=(const Monom& other) {
        *this += -other;
        return *this;
    }

    Polynom operator-(const Monom& other) const {
        Polynom res(*this);
        res -= other;
        return res;
    }

    Polynom& operator-=(const Polynom& other) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            *this -= *it;
        }
        return *this;
    }

    Polynom operator-(const Polynom& other) const {
        Polynom res(*this);
        res -= other;
        return res;
    }

    Polynom& operator*=(const Monom& other) {
        for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
            *it *= other;
        }
        return *this;
    }

    Polynom operator*(const Monom& other) const {
        Polynom res(*this);
        res *= other;
        return res;
    }

    Polynom& operator*=(const Polynom& other) {
        *this = *this * other;
        return *this;
    }

    Polynom operator*(const Polynom& other) const {
        Polynom res;
        for (auto it1 = _polynom.begin(); it1 != _polynom.end(); ++it1) {
            for (auto it2 = other.begin(); it2 != other.end(); ++it2) {
                res += (*it1) * (*it2);
            }
        }
        return res;
    }

    Polynom& operator/=(const Monom& other) {
        for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
            *it /= other;
        }
        return *this;
    }

    Polynom operator/(const Monom& other) const {
        Polynom res(*this);
        res /= other;
        return res;
    }

    Polynom& operator=(const Polynom& other) {
        if (this != &other) {
            _polynom = other._polynom;
            _name = other._name;
        }
        return *this;
    }

    double calculate_value_point(double x, double y, double z) const {
        double res = 0.0;
        for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
            res += (*it).calculate_value_point_monom(x, y, z);
        }
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const Polynom& p) {
        bool first = true;
        for (auto it = p.begin(); it != p.end(); ++it) {
            if (!first) os << " + ";
            os << *it;
            first = false;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Polynom& p) {
        p = Polynom();
        Monom m;
        while (is >> m) {
            p += m;
        }
        return is;
    }

    friend Polynom operator+(const Monom& mon, const Polynom& pol) {
        return pol + mon;
    }

    friend Polynom operator-(const Monom& mon, const Polynom& pol) {
        Polynom res(mon);
        res -= pol;
        return res;
    }

    friend Polynom operator*(const Monom& mon, const Polynom& pol) {
        return pol * mon;
    }
};