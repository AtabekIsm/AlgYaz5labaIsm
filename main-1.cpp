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
#include <functional> // ��� hash

using namespace std;

class Bank_vkl
{
    string naz = "";
    double sum = 0;
    string tp = "";
    double st = 0;

public:
    // ����������� �������������
    Bank_vkl(string nzz, string tpp, double summ, double stt) : naz(nzz), sum(summ), tp(tpp), st(stt) {}

    // ����������� �����������
    Bank_vkl(const Bank_vkl& other) : naz(other.naz), sum(other.sum), tp(other.tp), st(other.st) {}

    // ����������� �����������
    Bank_vkl(Bank_vkl&& other) noexcept : naz(move(other.naz)), sum(other.sum), tp(move(other.tp)), st(other.st) {}

    // �������� ������������ � ������������
    Bank_vkl& operator=(const Bank_vkl& other)
    {
        if (this != &other) // ������ �� ����������������
        {
            naz = other.naz;
            sum = other.sum;
            tp = other.tp;
            st = other.st;
        }
        return *this;
    }

    // �������� ������������ � ������������
    Bank_vkl& operator=(Bank_vkl&& other) noexcept
    {
        if (this != &other) // ������ �� ����������������
        {
            naz = move(other.naz);
            sum = other.sum;
            tp = move(other.tp);
            st = other.st;
        }
        return *this;
    }

    // �������
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

    // ������������� ������� ��� �������� ������� � �����
    friend ostream& operator<<(ostream& os, const Bank_vkl& vkl);

    // �������� ��������� ��� set (���������� �� ��������)
    bool operator<(const Bank_vkl& other) const
    {
        return naz < other.naz; // ���������� �� ��������
    }

    // �������� ��������� ��� unordered_set
    bool operator==(const Bank_vkl& other) const
    {
        return naz == other.naz; // ��������� �� ��������
    }
};

// ���������� �������� ������� � ����� ��� Bank_vkl
ostream& operator<<(ostream& os, const Bank_vkl& vkl)
{
    os << vkl.naz << endl << vkl.sum << endl << vkl.tp << endl << vkl.st;
    return os;
}

// ������������� ������� ��� �������� ������� � ����� ��� vector<Bank_vkl>
ostream& operator<<(ostream& os, const vector<Bank_vkl>& v)
{
    for (const auto& item : v) {
        os << item << endl; // ����� ������� �������� �������
    }
    return os;
}

// ������������� hash ��� Bank_vkl
namespace std {
    template <>
    struct hash<Bank_vkl> {
        size_t operator()(const Bank_vkl& vkl) const {
            return hash<string>{}(vkl.get_naz()); // �������� �� ��������
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

     //���������� ������� �� ��������
    sort(bvk.begin(), bvk.end(), [](const Bank_vkl& a, const Bank_vkl& b) {
        return a.get_naz() < b.get_naz(); // ���������� �� ��������
    });

    // ����������� ������� � deque
    deque<Bank_vkl> dq;
    copy(bvk.begin(), bvk.end(), back_inserter(dq));

    // ���������� �������� � set (���������� �� ��������)
    set<Bank_vkl> bank_set(bvk.begin(), bvk.end());

    // ���������� �������� � unordered_set
    unordered_set<Bank_vkl> bank_unordered_set(bvk.begin(), bvk.end());

    // ����� ����������� � ����
    ofs.open("output.txt");
    ofs << "��������� ��������� ���������� ����� ����������: " << endl;
    ofs << bvk;

    ofs << "\n��������� deque, ����� ����������� � ���� ��������� ����������: " << endl;
    for (const auto& item : dq) {
        ofs << item << endl;
    }

    ofs << "\n��������� set (���������� �� ��������): " << endl;
    for (const auto& item : bank_set) {
        ofs << item << endl;
    }

    ofs << "\n��������� unordered_set: " << endl;
    for (const auto& item : bank_unordered_set) {
        ofs << item << endl;
    }

    return 0;
}
