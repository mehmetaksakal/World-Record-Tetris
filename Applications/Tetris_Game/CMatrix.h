// ---------------------------------------------------------------------------

#ifndef CMatrixH
#define CMatrixH
// ---------------------------------------------------------------------------

#include <vector>

template<typename T>
class CMatrix {
private:
	std::vector<std::vector<T> >mat;

	unsigned rows;
	unsigned cols;

public:
	CMatrix(unsigned _rows, unsigned _cols, const T& _initial);
	CMatrix(const CMatrix<T>& rhs);
	virtual ~CMatrix();

	// Operator overloading, for "standard" mathematical matrix operations
	CMatrix<T>&operator = (const CMatrix<T>&rhs);

	// Matrix mathematical operations
	CMatrix<T>operator +(const CMatrix<T>& rhs);
	CMatrix<T>& operator += (const CMatrix<T>& rhs);
	CMatrix<T>operator -(const CMatrix<T>& rhs);
	CMatrix<T>& operator -= (const CMatrix<T>& rhs);
	CMatrix<T>operator*(const CMatrix<T>& rhs);
	CMatrix<T>& operator *= (const CMatrix<T>& rhs);
	CMatrix<T>transpose(bool inv);

	// Matrix/scalar operations
	CMatrix<T>operator +(const T& rhs);
	CMatrix<T>operator -(const T& rhs);
	CMatrix<T>operator*(const T& rhs);
	CMatrix<T>operator / (const T& rhs);

	// Matrix/vector operations
	std::vector<T>operator*(const std::vector<T>& rhs);
	std::vector<T>diag_vec();

	// Access the individual elements
	T& operator()(const unsigned& row, const unsigned& col);
	const T& operator()(const unsigned& row, const unsigned& col) const ;


	// Access the row and column sizes
	unsigned get_rows() const ;
	unsigned get_cols() const ;

	// Insert one matrix intro another
	bool insert(CMatrix<T> &_A, unsigned int _x, unsigned int _y);
	bool insert(unsigned int _x, unsigned int _y, const T &rhs);
};

#endif
