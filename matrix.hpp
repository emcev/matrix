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
//private:
        type** ptr;
//	size_t n;
//	size_t m;
//        auto operator[](size_t index) -> type*;
//        bool operator==(const Matrix&);

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
auto Matrix<T>::operator-(const Matrix& mat) -> Matrix& {
        if (n == mat.n && m == mat.m){
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++)
                    ptr[i][j] = ptr[i][j] - mat.ptr[i][j];
            }
            return *this;
        }
        else
                cout << "Error" << endl;
}

template <typename T>
auto Matrix<T>::operator+(const Matrix& mat) -> Matrix& {
        if (n == mat.n && m == mat.m){
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++)
                    ptr[i][j] = ptr[i][j] + mat.ptr[i][j];
            }
            return *this;
        }
        else
                cout << "Error" << endl;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix& mat) {
        if (n == mat.n && m == mat.m){
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    if (ptr[i][j] != mat.ptr[i][j])
                        return false;
                }
            }
            return true;
        }
        return false;
}

template <typename T>
ostream& operator<<(ostream& os, Matrix<T>& mat) {
        os << mat.n << " " << mat.m << endl;
        for (int i = 0; i < mat.n; i++){
            for (int j = 0; j < mat.m; j++)
                os << mat.ptr[i][j]<<"  ";
            os << endl;
        }
        return os;
}

template <typename T>
istream& operator>>(istream& is, Matrix<T>& mat) {
	if(is) {
        	is >> mat.n >> mat.m;
        	mat.ptr=new int*[mat.n];
        	for(int i=0; i < mat.n; i++)
            		mat.ptr[i]=new int[mat.m];
        	for (int i = 0; i < mat.n; i++) {
            		for (int j = 0; j < mat.m; j++)
                		is >> mat.ptr[i][j];
            	}
        }
        return is;
}

template <typename T>
auto Matrix<T>::m_swap(Matrix& mat) -> void {
        swap(ptr, mat.ptr);
        swap(n, mat.n);
        swap(m, mat.m);
}

template <typename T>
auto Matrix<T>::operator=(const Matrix& q) -> Matrix& {
        if (ptr != nullptr) {
            for (int i = 0; i < n; i++) delete[] ptr[i];
                delete [] ptr;
            return *this;
        }
        n = q.n;
        m = q.m;
        ptr = new int*[n];
        for (int i = 0; i < n; i++)
            ptr[i] = new int[m];
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                ptr[i][j] = q.ptr[i][j];
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
