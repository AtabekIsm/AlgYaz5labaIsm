#include <iostream>
#include <string>
#include <utility>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>
#include <set>
#include <unordered_set>
#include <functional> // для hash

using namespace std;

class Bank_vkl
{
    string naz = "";
    double sum = 0;
    string tp = "";
    double st = 0;

public:
    // Конструктор инициализации
    Bank_vkl(string nzz, string tpp, double summ, double stt) : naz(nzz), sum(summ), tp(tpp), st(stt) {}

    // Конструктор копирования
    Bank_vkl(const Bank_vkl& other) : naz(other.naz), sum(other.sum), tp(other.tp), st(other.st) {}

    // Конструктор перемещения
    Bank_vkl(Bank_vkl&& other) noexcept : naz(move(other.naz)), sum(other.sum), tp(move(other.tp)), st(other.st) {}

    // Операция присваивания с копированием
    Bank_vkl& operator=(const Bank_vkl& other)
    {
        if (this != &other) // Защита от самоприсваивания
        {
            naz = other.naz;
            sum = other.sum;
            tp = other.tp;
            st = other.st;
        }
        return *this;
    }

    // Операция присваивания с перемещением
    Bank_vkl& operator=(Bank_vkl&& other) noexcept
    {
        if (this != &other) // Защита от самоприсваивания
        {
            naz = move(other.naz);
            sum = other.sum;
            tp = move(other.tp);
            st = other.st;
        }
        return *this;
    }

    // Геттеры
    string get_naz() const
    {
        return naz;
    }
    double get_sum() const
    {
        return sum;
    }
    string get_tp() const
    {
        return tp;
    }
    double get_st() const
    {
        return st;
    }

    // Дружественная функция для операции вставки в поток
    friend ostream& operator<<(ostream& os, const Bank_vkl& vkl);

    // Операция сравнения для set (сортировка по названию)
    bool operator<(const Bank_vkl& other) const
    {
        return naz < other.naz; // Сортировка по названию
    }

    // Операция сравнения для unordered_set
    bool operator==(const Bank_vkl& other) const
    {
        return naz == other.naz; // Сравнение по названию
    }
};

// Реализация операции вставки в поток для Bank_vkl
ostream& operator<<(ostream& os, const Bank_vkl& vkl)
{
    os << vkl.naz << endl << vkl.sum << endl << vkl.tp << endl << vkl.st;
    return os;
}

// Дружественная функция для операции вставки в поток для vector<Bank_vkl>
ostream& operator<<(ostream& os, const vector<Bank_vkl>& v)
{
    for (const auto& item : v) {
        os << item << endl; // Вывод каждого элемента вектора
    }
    return os;
}

// Специализация hash для Bank_vkl
namespace std {
    template <>
    struct hash<Bank_vkl> {
        size_t operator()(const Bank_vkl& vkl) const {
            return hash<string>{}(vkl.get_naz()); // Хешируем по названию
        }
    };
}

int main()
{
    string nz, tt;
    double ss, sst;
    vector<Bank_vkl> bvk;
    int n;
    ifstream ifs;
    ofstream ofs;
    ifs.open("input5.txt");
    ifs >> n;
    for (int i = 0; i < n; i++)
    {
        ifs >> nz;
        ifs >> ss;
        ifs >> tt;
        ifs >> sst;
        Bank_vkl g(nz, tt, ss, sst);
        bvk.push_back(g);
    }

     //Сортировка вектора по названию
    sort(bvk.begin(), bvk.end(), [](const Bank_vkl& a, const Bank_vkl& b) {
        return a.get_naz() < b.get_naz(); // Сортировка по названию
    });

    // Копирование вектора в deque
    deque<Bank_vkl> dq;
    copy(bvk.begin(), bvk.end(), back_inserter(dq));

    // Добавление объектов в set (сортировка по названию)
    set<Bank_vkl> bank_set(bvk.begin(), bvk.end());

    // Добавление объектов в unordered_set
    unordered_set<Bank_vkl> bank_unordered_set(bvk.begin(), bvk.end());

    // Вывод результатов в файл
    ofs.open("output.txt");
    ofs << "Состояние исходного контейнера после сортировки: " << endl;
    ofs << bvk;

    ofs << "\nКонтейнер deque, после копирования в него исходного контейнера: " << endl;
    for (const auto& item : dq) {
        ofs << item << endl;
    }

    ofs << "\nКонтейнер set (сортировка по названию): " << endl;
    for (const auto& item : bank_set) {
        ofs << item << endl;
    }

    ofs << "\nКонтейнер unordered_set: " << endl;
    for (const auto& item : bank_unordered_set) {
        ofs << item << endl;
    }

    return 0;
}
