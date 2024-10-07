#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
using namespace std;

class Complex {
public:
    double real;
    double imag;

    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    double modulus() const {
        return sqrt(real * real + imag * imag);
    }

    // ���� < ���������������
    bool operator<(const Complex& other) const {
        if (this->modulus() == other.modulus()) {
            return this->real < other.real;
        }
        return this->modulus() < other.modulus();
    }

    // ���� > �����������ð������
    bool operator>(const Complex& other) const {
        if (this->modulus() == other.modulus()) {
            return this->real > other.real;
        }
        return this->modulus() > other.modulus();
    }

    // ���� == ����������ڲ���ʱ�ıȽ�
    bool operator==(const Complex& other) const {
        return (this->real == other.real) && (this->imag == other.imag);
    }

    void print() const {
        cout << real << " + " << imag << "i";
    }
};


void printVector(const vector<Complex>& vec) {
    for (const auto& c : vec) {
        c.print();
        cout << " ";
    }
    cout << endl;
}

// ������ɸ�������
vector<Complex> generateRandomVector(int n) {
    vector<Complex> vec;
    for (int i = 0; i < n; ++i) {
        double real = rand() % 100 / 10.0; // ʵ�������
        double imag = rand() % 100 / 10.0; // �鲿�����
        vec.push_back(Complex(real, imag));
    }
    return vec;
}

// ���Ҹ���
int findComplex(const vector<Complex>& vec, const Complex& target) {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == target)
            return i;
    }
    return -1; // δ�ҵ�
}

// ���븴��
void insertComplex(vector<Complex>& vec, const Complex& c) {
    vec.push_back(c);
}

// ɾ������
void deleteComplex(vector<Complex>& vec, const Complex& c) {
    vec.erase(remove(vec.begin(), vec.end(), c), vec.end());
}

// ȥ���ظ���
void uniqueComplex(vector<Complex>& vec) {
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
}

// ð������
void bubbleSort(vector<Complex>& vec) {
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        for (size_t j = 0; j < vec.size() - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                swap(vec[j], vec[j + 1]);
            }
        }
    }
}

// �鲢����������
void merge(vector<Complex>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Complex> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = vec[left + i];
    for (int i = 0; i < n2; i++) R[i] = vec[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] < R[j]) vec[k++] = L[i++];
        else vec[k++] = R[j++];
    }
    while (i < n1) vec[k++] = L[i++];
    while (j < n2) vec[k++] = R[j++];
}

// �鲢����
void mergeSort(vector<Complex>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

// ������ң�����ģ����[m1, m2)������Ԫ��
vector<Complex> findInModulusRange(const vector<Complex>& vec, double m1, double m2) {
    vector<Complex> result;
    for (const auto& c : vec) {
        if (c.modulus() >= m1 && c.modulus() < m2) {
            result.push_back(c);
        }
    }
    return result;
}

int main() {
    srand(time(0));

    // �����������������
    vector<Complex> vec = generateRandomVector(10);
    cout << "ԭʼ������" << endl;
    printVector(vec);

    // �������
    Complex newComplex(2.5, 3.5);
    insertComplex(vec, newComplex);
    cout << "�����" << endl;
    printVector(vec);

    // ���Ҳ���
    int index = findComplex(vec, newComplex);
    if (index != -1)
        cout << "�ҵ�����������: " << index << endl;
    else
        cout << "δ�ҵ�����" << endl;

    // ɾ������
    deleteComplex(vec, newComplex);
    cout << "ɾ����" << endl;
    printVector(vec);

    // ȥ���ظ���
    uniqueComplex(vec);
    cout << "Ψһ����" << endl;
    printVector(vec);

    // ð������͹鲢����Ƚ�
    vector<Complex> vecCopy = vec;

    // ð�������ʱ
    clock_t start = clock();
    bubbleSort(vec);
    clock_t end = clock();
    cout << "ð�������" << endl;
    printVector(vec);
    cout << "ð�������ʱ: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << endl;

    // �鲢�����ʱ
    start = clock();
    mergeSort(vecCopy, 0, vecCopy.size() - 1);
    end = clock();
    cout << "�鲢�����" << endl;
    printVector(vecCopy);
    cout << "�鲢�����ʱ: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << endl;

    // �������
    double m1 = 2.0, m2 = 5.0;
    vector<Complex> rangeVec = findInModulusRange(vec, m1, m2);
    cout << "ģ���� [" << m1 << ", " << m2 << ") �ĸ�����" << endl;
    printVector(rangeVec);

    return 0;
}
