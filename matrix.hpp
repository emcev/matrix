#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class Matrix{
public:
        typedef int type;
        Matrix();
        Matrix(initializer_list<int> list);
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
        template <typename T2>
        friend ostream& operator<<(ostream&, Matrix&);
        template <typename T3>
        friend istream& operator>>(istream&, Matrix&);
        ~Matrix();
	size_t n;
	size_t m;
        type** ptr;
};

template <typename T>
Matrix<T>::Matrix() {
        ptr = nullptr;
        n = m = 0;
}

template <typename T>
Matrix<T>::Matrix(initializer_list<int> list) {
	n = m = 3;
        ptr = new int*[3];
    	for (int i = 0; i < 3; i++)
		ptr[i] = new int[3];
    	for (int i = 0; i < 3; i++) {
      		for (int j = 0; j < 3; j++)
        		ptr[i][j] = 0 + rand()%10;
    	}
}

template <typename T>
Matrix<T>::Matrix(const Matrix& m_matrix) {
        ptr = new int *[m_matrix.n];
        for (int i = 0; i < m_matrix.n; ++i){
            ptr[i] = new int[m_matrix.m];
            for (int j = 0; j < m_matrix.m; ++j)
                ptr[i][j] = m_matrix.ptr[i][j];
        }
        n = m_matrix.n;
        m = m_matrix.m;
}

template <typename T>
auto Matrix<T>::empty() -> bool {
        if (ptr == nullptr)
                return true;
        else
                return false;
}

template <typename T>
auto Matrix<T>::columns() -> size_t {
        return m;
}

template <typename T>
auto Matrix<T>::rows() -> size_t {
        return n;
}

template <typename T>
auto Matrix<T>::operator[](size_t index) -> int* {
        return ptr[index];
}

template <typename T>
auto Matrix<T>::operator-(const Matrix& m_matrix) -> Matrix& {
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

template <typename T>
auto Matrix<T>::operator+(const Matrix& m_matrix) -> Matrix& {
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

template <typename T>
bool Matrix<T>::operator==(const Matrix& m_matrix) {
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

template <typename T>
ostream& operator<<(ostream& os, Matrix<T>& m_matrix) {
        os << m_matrix.n << " " << m_matrix.m << endl;
        for (int i = 0; i < m_matrix.n; i++){
            for (int j = 0; j < m_matrix.m; j++)
                os << m_matrix.ptr[i][j]<<"  ";
            os << endl;
        }
        return os;
}

template <typename T>
istream& operator>>(istream& is, Matrix<T>& m_matrix) {
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

template <typename T>
auto Matrix<T>::m_swap(Matrix& m_matrix) -> void {
        swap(ptr, m_matrix.ptr);
        swap(n, m_matrix.n);
        swap(m, m_matrix.m);
}

template <typename T>
auto Matrix<T>::operator=(const Matrix& m_matrix) -> Matrix& {
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

template <typename T>
Matrix<T>::~Matrix() {
        for (int i = 0; i < n; i++)
                delete[] ptr[i];
        delete [] ptr;
}
