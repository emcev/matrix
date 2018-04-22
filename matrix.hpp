#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <fstream>

using namespace std;

template <typename type, size_t N, size_t M>
class Matrix {
public:
    Matrix();
    Matrix(initializer_list<type> il);
    Matrix(const Matrix&);
    auto m_swap(Matrix&) -> void;
    auto operator=(const Matrix& q) -> Matrix&;
    auto empty() -> bool;
    auto columns() -> size_t;
    auto rows() -> size_t;
    auto operator-(const Matrix&) -> Matrix&;
    auto operator+(const Matrix&) -> Matrix&;
    auto operator[](size_t index) -> type*;
    bool operator==(const Matrix&);
    template <typename T2, size_t N2, size_t M2>
    friend ostream& operator<<(ostream&, Matrix<T2, N2, M2>&);
    template <typename T3, size_t N3, size_t M3>
    friend istream& operator>>(istream&, Matrix<T3, N3, M3>&);
    ~Matrix();
    size_t n = N;
    size_t m = M;
private:
    type** ptr;
};

template <typename type, size_t N, size_t M>
Matrix<T, N, M>::Matrix() : ptr(nullptr), n(N), m(M) {
    n = m = 0;
}

template <typename type, size_t N, size_t M>
Matrix<T, N, M>::Matrix(initializer_list<int> il) {
    ptr = new int*[n];
    auto p = il.begin();
    for (int i = 0; i < n; i++)
        ptr[i] = new int[m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++, p++)
            ptr[i][j] = *p;
    }
}

template <typename type, size_t N, size_t M>
Matrix<type, N, M>::Matrix(const Matrix& m_matrix) {
    ptr = new int *[m_matrix.n];
    for (int i = 0; i < m_matrix.n; i++){
        ptr[i] = new int[m_matrix.m];
        for (int j = 0; j < m_matrix.m; j++)
            ptr[i][j] = m_matrix.ptr[i][j];
    }
}

template <typename type, size_t N, size_t M>
auto Matrix<type, N, M>::empty() -> bool {
    if (ptr == nullptr)
        return true;
    else
        return false;
}

template <typename type, size_t N, size_t M>
auto Matrix<type, N, M>::columns() -> size_t {
    return m;
}

template <typename type, size_t N, size_t M>
auto Matrix<type, N, M>::rows() -> size_t {
    return n;
}

template <typename type, size_t N, size_t M>
auto Matrix<type, N, M>::operator[](size_t index) -> int* {
    return ptr[index];
}

template <typename type, size_t N, size_t M>
auto Matrix<type, N, M>::operator-(const Matrix& m_matrix) -> Matrix& {
    if (n == m_matrix.n && m == m_matrix.m){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++)
                ptr[i][j] = ptr[i][j] - m_matrix.ptr[i][j];
        }
        return *this;
    }
    else
        cout << "Error" << endl;
}

template <typename type, size_t N, size_t M>
auto Matrix<type, N, M>::operator+(const Matrix& m_matrix) -> Matrix& {
    if (n == m_matrix.n && m == m_matrix.m){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++)
                ptr[i][j] = ptr[i][j] + m_matrix.ptr[i][j];
        }
        return *this;
    }
    else
        cout << "Error" << endl;
}

template <typename type, size_t N, size_t M>
bool Matrix<type, N, M>::operator==(const Matrix& m_matrix) {
    if (n == m_matrix.n && m == m_matrix.m){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if (ptr[i][j] != m_matrix.ptr[i][j])
                    return false;
            }
        }
        return true;
    }
    return false;
}

template <typename type, size_t N, size_t M>
ostream& operator<<(ostream& os, Matrix<type, N, M>& m_matrix) {
    os << m_matrix.n << " " << m_matrix.m << endl;
    for (int i = 0; i < m_matrix.n; i++){
        for (int j = 0; j < m_matrix.m; j++)
            os << m_matrix.ptr[i][j]<<"  ";
        os << endl;
    }
    return os;
}

template <typename type, size_t N, size_t M>
istream& operator>>(istream& is, Matrix<type, N, M>& m_matrix) {
    if(is) {
        is >> m_matrix.n >> m_matrix.m;
        m_matrix.ptr=new int*[m_matrix.n];
        for(int i=0; i < m_matrix.n; i++)
            m_matrix.ptr[i]=new int[m_matrix.m];
        for (int i = 0; i < m_matrix.n; i++) {
            for (int j = 0; j < m_matrix.m; j++)
                is >> m_matrix.ptr[i][j];
        }
    }
    return is;
}

template <typename type, size_t N, size_t M>
auto Matrix<type, N, M>::m_swap(Matrix& m_matrix) -> void {
    swap(ptr, m_matrix.ptr);
    swap(n, m_matrix.n);
    swap(m, m_matrix.m);
}

template <typename type, size_t N, size_t M>
auto Matrix<type, N, M>::operator=(const Matrix& m_matrix) -> Matrix& {
    if (ptr != nullptr) {
        for (int i = 0; i < n; i++)
            delete[] ptr[i];
        delete [] ptr;
        return *this;
    }
    n = m_matrix.n;
    m = m_matrix.m;
    ptr = new int*[n];
    for (int i = 0; i < n; i++)
        ptr[i] = new int[m];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            ptr[i][j] = m_matrix.ptr[i][j];
        }
    }
    return *this;
}

template <typename type, size_t N, size_t M>
Matrix<type, N, M>::~Matrix() {
    for (int i = 0; i < n; i++)
        delete[] ptr[i];
    delete [] ptr;
}
