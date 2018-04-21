#include <matrix.hpp>

int main() {
	Matrix <int> m1{3,5};
    	Matrix <int> m2{1, 2, 3, 4, 5, 6};
    	Matrix <int> m3{m2};

    	cout << m1 << endl;
    	cout << m2 << endl;
    	cout << m3 << endl;

    	Matrix <int> m4;
    	m4 = m3;
    	cout << m4 << endl;

    	m4[0][0] = 8;
    	cout << m4 << endl;

    	cout << boolalpha  << (m2 == m3) << (m3 == m4) << endl;

    	cout << m1.rows() << m1.columns() << endl;

    	Matrix <int> m5{0, 2, 4, 6, 8, 10};
    	cout << m3 + m5 << endl;
    	cout << m3 - m5 << endl;

    	Matrix <int> m6{};
    	cout << m6.empty() << endl;

    	ofstream out{"matrix.bin"};
    	out << m3;

    	ifstream in{"matrix.bin"};
    	in >> m6;

    	m3.m_swap(m6);

    	cout << m3 << endl;
}
