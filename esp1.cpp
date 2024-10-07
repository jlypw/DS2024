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

    // 重载 < 运算符，用于排序
    bool operator<(const Complex& other) const {
        if (this->modulus() == other.modulus()) {
            return this->real < other.real;
        }
        return this->modulus() < other.modulus();
    }

    // 重载 > 运算符，用于冒泡排序
    bool operator>(const Complex& other) const {
        if (this->modulus() == other.modulus()) {
            return this->real > other.real;
        }
        return this->modulus() > other.modulus();
    }

    // 重载 == 运算符，用于查找时的比较
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

// 随机生成复数向量
vector<Complex> generateRandomVector(int n) {
    vector<Complex> vec;
    for (int i = 0; i < n; ++i) {
        double real = rand() % 100 / 10.0; // 实部随机数
        double imag = rand() % 100 / 10.0; // 虚部随机数
        vec.push_back(Complex(real, imag));
    }
    return vec;
}

// 查找复数
int findComplex(const vector<Complex>& vec, const Complex& target) {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == target)
            return i;
    }
    return -1; // 未找到
}

// 插入复数
void insertComplex(vector<Complex>& vec, const Complex& c) {
    vec.push_back(c);
}

// 删除复数
void deleteComplex(vector<Complex>& vec, const Complex& c) {
    vec.erase(remove(vec.begin(), vec.end(), c), vec.end());
}

// 去除重复项
void uniqueComplex(vector<Complex>& vec) {
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
}

// 冒泡排序
void bubbleSort(vector<Complex>& vec) {
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        for (size_t j = 0; j < vec.size() - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                swap(vec[j], vec[j + 1]);
            }
        }
    }
}

// 归并排序辅助函数
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

// 归并排序
void mergeSort(vector<Complex>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

// 区间查找，返回模介于[m1, m2)的所有元素
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

    // 随机生成无序复数向量
    vector<Complex> vec = generateRandomVector(10);
    cout << "原始向量：" << endl;
    printVector(vec);

    // 插入操作
    Complex newComplex(2.5, 3.5);
    insertComplex(vec, newComplex);
    cout << "插入后：" << endl;
    printVector(vec);

    // 查找操作
    int index = findComplex(vec, newComplex);
    if (index != -1)
        cout << "找到复数在索引: " << index << endl;
    else
        cout << "未找到复数" << endl;

    // 删除操作
    deleteComplex(vec, newComplex);
    cout << "删除后：" << endl;
    printVector(vec);

    // 去除重复项
    uniqueComplex(vec);
    cout << "唯一化后：" << endl;
    printVector(vec);

    // 冒泡排序和归并排序比较
    vector<Complex> vecCopy = vec;

    // 冒泡排序计时
    clock_t start = clock();
    bubbleSort(vec);
    clock_t end = clock();
    cout << "冒泡排序后：" << endl;
    printVector(vec);
    cout << "冒泡排序耗时: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << endl;

    // 归并排序计时
    start = clock();
    mergeSort(vecCopy, 0, vecCopy.size() - 1);
    end = clock();
    cout << "归并排序后：" << endl;
    printVector(vecCopy);
    cout << "归并排序耗时: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << endl;

    // 区间查找
    double m1 = 2.0, m2 = 5.0;
    vector<Complex> rangeVec = findInModulusRange(vec, m1, m2);
    cout << "模介于 [" << m1 << ", " << m2 << ") 的复数：" << endl;
    printVector(rangeVec);

    return 0;
}
