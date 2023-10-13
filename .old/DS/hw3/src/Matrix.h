#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

typedef unsigned int uint;

class Matrix {
public:
	// Constructors
	Matrix(): rows(0), cols(0), data(0) {}
	Matrix(uint rows, uint cols, double value = 0.0);

	// Copy constructor, assignment operator and destructor
	Matrix(const Matrix& that) { copy(that); };
	~Matrix() { destroy(); };
	Matrix& operator=(const Matrix& that);

	// Equality and inequality operators
	friend bool operator==(const Matrix& lhs, const Matrix& rhs);
	friend bool operator!=(const Matrix& lhs, const Matrix& rhs);

	// Getter
	uint num_rows() const { return rows; }
	uint num_cols() const { return cols; }

	// Empty a matrix
	void clear();

	// Safe getter
	bool get(uint row, uint col, double &x) const;
	// Setter
	bool set(uint row, uint col, double x);

	// Operations
	// Multiply by coefficient
	void multiply_by_coefficient(double n);
	// Swap rows
	void swap_row(uint row1, uint row2);
	// Transpose
	void transpose();

	// Binary Matrix Operations
	// Addition
	bool add(const Matrix& that);
	// Subtraction
	bool subtract(const Matrix& that);

	// Strong getters
	// Get row
	double* get_row(uint row) const;
	// Get column
	double* get_col(uint col) const;

	// Quarter
	Matrix* quarter();

private:
	// Representation
	uint rows;
	uint cols;
	double** data;

	// Memory helpers
	void copy(const Matrix& that);
	void destroy();
};

bool operator==(const Matrix& lhs, const Matrix& rhs);
bool operator!=(const Matrix& lhs, const Matrix& rhs);

// Ostream operator
std::ostream& operator<<(std::ostream& os, const Matrix& m);

#endif
