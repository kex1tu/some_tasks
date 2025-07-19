#include <iostream>
#include <fstream>
#include <cmath>

double** create_matrix(int rows,
					int cols) {
	double** arr = new double* [rows];
	for (int idx = 0; idx < rows; ++idx) {
		arr[idx] = new double[cols];
	}
	return arr;
}

void print_matrix_to_console(double** arr,
	int rows,
	int cols
) {
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			std::cout << arr[r][c] << '\t';
		}
		std::cout << '\n';
	}
}

double** create_ones_matrix(int rows,
	int cols) {
	double** arr = new double* [rows];
	for (int idx = 0; idx < rows; ++idx) {
		arr[idx] = new double[cols];
	}
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			arr[i][j] = 0;
			if (i == j) {
				arr[i][j] = 1;
			}
		}
	}
	return arr;
}

double** merge_matrix_right (double** arr1, double** arr2,
							 int rows1, int cols1, int rows2, int cols2
)
{

	double** merged_arr = new double* [rows1];
	
	for (int i = 0; i < rows1; ++i) {
		merged_arr[i] = new double[cols1 + cols2];
	}
	cols1 += cols2;
	for (int r = 0; r < rows1; ++r) {
		for (int c = 0; c < cols1; ++c) {
			
			if (c < cols1 - cols2) {
				merged_arr[r][c] = arr1[r][c];
			}
			else {
				merged_arr[r][c] = arr2[r][c - (cols1-cols2)];
			}
		}
	}
	
	return merged_arr;
}

void delete_matrix(double** arr, int rows) {
	for (int idx = 0; idx < rows; ++idx) {
		delete[] arr[idx];
	}
	delete[] arr;
}

double** read_matrix_from_file(const char* file_name,
							  int& rows,
							  int& cols
) {
	std::ifstream in(file_name);
	

	in >> rows >> cols;
	double** arr = create_matrix(rows, cols);
	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < cols; ++c) {
			in >> arr[r][c];
		}
	}
	return arr;
}

void print_matrix_to_file(const char* file_name,
						  double** arr,
						  int &rows,
						  int &cols
) {
	std::ofstream out(file_name);

	out << rows << ' ' << cols << '\n';
	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < cols; ++c)
		{
			out << arr[r][c] << '\t';
		}

		out << '\n';
	}
	out.close();

}

void forward_gauss(double** m, int& rows, int& cols, int& sign_of_det) {
	int k;
	
	for (int c = 0; c < rows; ++c) {//вообще до cols
		k = c;
		for (int r = c + 1; r < rows; ++r) {
			if (std::abs(m[r][c]) > std::abs(m[k][c])) {
				k = r;
			}
		}
		if (std::abs(m[k][c]) == 0.0) {
			sign_of_det = 0;
			return;
		}
		if (k != c) {
			std::swap(m[k], m[c]);
			sign_of_det *= -1;
		}
		for (int r = c + 1; r < rows; ++r) {
			const double tmp = (m[r][c]) / (m[c][c]);
			for (int i = c; i < cols; ++i) {
				m[r][i] -= (m[c][i]) * tmp;
			}

		}
	}
}

double det_of_matrix(double** m, int& rows, int& cols, int& sign_of_det) {
	
	forward_gauss(m, rows, cols, sign_of_det);
	double det = sign_of_det;
	if (std::abs(det) == 0.0) {
		return det;
	}
	for (int i = 0; i < rows; ++i) {
		det *= m[i][i];
	}
	return det;
}

void backward_gauss(double** m, int& rows, int& cols) {
	for (int c = cols/2 - 1; c >= 0; --c) {
		for (int r = c - 1; r >=0; --r) {
			const double tmp = (m[r][c]) / (m[c][c]);
			for (int i = cols-1; i >= 0; --i) {
				m[r][i] -= (m[c][i]) * tmp;
			}
		}
	}
}

void make_ones_from(double** m, int& rows, int& cols) {
	for (int i = 0; i < rows; ++i) {
		double k = m[i][i];
		for (int j = i; j < cols; ++j) {
			m[i][j] /= k;
		}
	}
}

double** unmerge_matrix_right(double** m, int& rows, int& cols) {
	double** right_matrix = create_matrix(rows, cols / 2);
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols/2; ++j) {
			right_matrix[i][j] = m[i][j + cols / 2];
		}
	}
	return right_matrix;
}

double** inv_matrix(double** m, int& rows, int& cols) {
	double** one;
	one = create_ones_matrix(rows, cols);
	double** mm;
	mm = merge_matrix_right(m, one, rows, cols, rows, cols);
	double** res;
	delete_matrix(one, rows);

	int nrows = rows;
	int ncols = cols * 2;
	double tmp = 1;
	int sign = 1;

	

	tmp = det_of_matrix(mm, nrows, ncols, sign);
	if (tmp == 0) {
		delete_matrix(mm, rows);
		rows = 0;
		cols = 0;
		return 0;
	}
	backward_gauss(mm, nrows, ncols);


	make_ones_from(mm, nrows, ncols);

	res = unmerge_matrix_right(mm, nrows, ncols);
	delete_matrix(mm, nrows);
	return res;
}

int main(int argc, char* argv[])
{
	int rows;
	int cols;
	double det = 4;
	double** matrix = read_matrix_from_file(argv[2], rows, cols);
	int sign = 1;
	char ch = argv[1][1];
	if (ch == 'd') {
		if (rows == cols) {
			det = det_of_matrix(matrix, rows, cols, sign);
			std::ofstream out(argv[3]);
			out << det;
			out.close();
		}
		else {
			std::ofstream out(argv[3]);
			out << "error";
			out.close();
		}
	}
	else {
		if (rows == cols) {
			double** inv;
			inv = inv_matrix(matrix, rows, cols);
			if (rows == cols && rows == 0) {
				std::ofstream out(argv[3]);
				out << "singular";
				out.close();
			}
			else {
				print_matrix_to_file(argv[3], inv, rows, cols);
			}
			delete_matrix(inv, rows);
		}
		else {
			std::ofstream out(argv[3]);
			out << "error";
			out.close();
		}
	}
	delete_matrix(matrix, rows);
	
	return 0;
}
