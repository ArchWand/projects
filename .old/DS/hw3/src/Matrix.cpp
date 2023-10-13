#include "Matrix.h"

// Normal constructor
Matrix::Matrix(uint rows, uint cols, double value): rows(rows), cols(cols) {
	data = new double*[rows];
	for (uint i = 0; i < rows; ++i) {
		data[i] = new double[cols];
		for (uint j = 0; j < cols; ++j) {
			data[i][j] = value;
		}
	}
}

// Assignment operator
Matrix& Matrix::operator=(const Matrix& that) {
	if (this != &that) {
		destroy();
		copy(that);
	}
	return *this;
}

// Equality operator
bool operator==(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.rows != rhs.rows || lhs.cols != rhs.cols)
	{ return false; }
	for (uint i = 0; i < lhs.rows; ++i) {
		for (uint j = 0; j < lhs.cols; ++j) {
			if (lhs.data[i][j] != rhs.data[i][j])
			{ return false; }
		}
	}
	return true;
}

// Inequality operator
bool operator!=(const Matrix& lhs, const Matrix& rhs) {
	return !(lhs == rhs);
}

// Memory helper: copy
void Matrix::copy(const Matrix& that) {
	rows = that.rows;
	cols = that.cols;
	data = new double*[rows];
	for (uint i = 0; i < rows; ++i) {
		data[i] = new double[cols];
		for (uint j = 0; j < cols; ++j) {
			data[i][j] = that.data[i][j];
		}
	}
}

// Memory helper: destroy
void Matrix::destroy() {
	for (uint i = 0; i < rows; ++i) {
		delete[] data[i];
	}
	delete[] data;
}

// Clear a matrix
void Matrix::clear() {
	destroy();
	rows = 0;
	cols = 0;
}

// Safe getter
bool Matrix::get(uint row, uint col, double &x) const {
	if (row >= rows || col >= cols) { return false; }
	x = data[row][col];
	return true;
}

// Setter
bool Matrix::set(uint row, uint col, double x) {
	if (row >= rows || col >= cols) { return false; }
	data[row][col] = x;
	return true;
}

// Ostream operator
std::ostream& operator<<(std::ostream& os, const Matrix& m) {
	os << std::endl << m.num_rows() << " x " << m.num_cols() << " matrix:" << std::endl;
	os << "[" << std::endl;
	for (uint i = 0; i < m.num_rows(); ++i) {
		for (uint j = 0; j < m.num_cols(); ++j) {
			double x;
			m.get(i, j, x);
			os << x << " ";
		}
		os << std::endl;
	}
	os << "]" << std::endl;
	return os;
}

// Multiply by coefficient
void Matrix::multiply_by_coefficient(double n) {
	for (uint i = 0; i < rows; ++i) {
		for (uint j = 0; j < cols; ++j) {
			data[i][j] *= n;
		}
	}
}

// Swap rows
void Matrix::swap_row(uint row1, uint row2) {
	if (row1 >= rows || row2 >= rows) { return; }
	double* temp = data[row1];
	data[row1] = data[row2];
	data[row2] = temp;
}

// Transpose
void Matrix::transpose() {
	double** new_data = new double*[cols];
	for (uint i = 0; i < cols; ++i) {
		new_data[i] = new double[rows];
		for (uint j = 0; j < rows; ++j) {
			new_data[i][j] = data[j][i];
		}
	}
	destroy();
	data = new_data;
	uint temp = rows;
	rows = cols;
	cols = temp;
}

// Addition
bool Matrix::add(const Matrix& that) {
	if (rows != that.rows || cols != that.cols) { return false; }
	for (uint i = 0; i < rows; ++i) {
		for (uint j = 0; j < cols; ++j) {
			data[i][j] += that.data[i][j];
		}
	}
	return true;
}

// Subtraction
bool Matrix::subtract(const Matrix& that) {
	if (rows != that.rows || cols != that.cols) { return false; }
	for (uint i = 0; i < rows; ++i) {
		for (uint j = 0; j < cols; ++j) {
			data[i][j] -= that.data[i][j];
		}
	}
	return true;
}

// Get row
double* Matrix::get_row(uint row) const {
	if (row >= rows) { return nullptr; }
	return data[row];
}

// Get column
double* Matrix::get_col(uint col) const {
	if (col >= cols) { return nullptr; }
	double* result = new double[rows];
	for (uint i = 0; i < rows; ++i) {
		result[i] = data[i][col];
	}
	return result;
}

// Quarter
Matrix* Matrix::quarter() {
	uint r = (rows+1) / 2, c = (cols+1) / 2;
	Matrix* out = new Matrix[4];
	// allocate on heap
	for (uint i = 0; i < 4; ++i) {
		out[i].rows = r;
		out[i].cols = c;
		out[i].data = new double*[r];
		for (uint j = 0; j < r; ++j) {
			out[i].data[j] = new double[c];
		}
	}

	for (uint i = 0; i < r; ++i) {
		for (uint j = 0; j < c; ++j) {
			out[0].data[i][j] = data[i][j];
		}
	}
	for (uint i = 0; i < r; ++i) {
		for (uint j = cols-c; j < cols; ++j) {
			out[1].data[i][j-cols+c] = data[i][j];
		}
	}
	for (uint i = rows-r; i < rows; ++i) {
		for (uint j = 0; j < c; ++j) {
			out[2].data[i-rows+r][j] = data[i][j];
		}
	}
	for (uint i = rows-r; i < rows; ++i) {
		for (uint j = cols-c; j < cols; ++j) {
			out[3].data[i-rows+r][j-cols+c] = data[i][j];
		}
	}

	return out;
}

