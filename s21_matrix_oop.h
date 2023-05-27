#ifndef CPP1_S21_MATRIXPLUS_0_S21_MATRIX_OOP_H
#define CPP1_S21_MATRIXPLUS_0_S21_MATRIX_OOP_H

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <stdexcept>

class S21Matrix {
 private:
  int _rows, _cols;  // Rows and columns
  double** _matrix;  // Pointer to the memory where the matrix is allocated

 public:
  // Constructors
  S21Matrix();                        // Default constructor
  S21Matrix(int rows, int cols);      // Parametrized constructor
  S21Matrix(const S21Matrix& other);  // Copy constructor
  S21Matrix(S21Matrix&& other);       // Move constructor
  ~S21Matrix();                       // Destructor

  // Operations with matrix
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // Operators
  double& operator()(int row, int col);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  friend S21Matrix operator*(const S21Matrix& thisMatrix, double num);
  S21Matrix& operator*=(const double num);

  // Accessors
  int getCols();
  int getRows();

  // Mutators
  void setCols(int newCols);
  void setRows(int newRows);
  void setElement(int row, int col, double value);

  // Helpful methods
  int TwoDet();
  int OneDet();
  S21Matrix HandleMatrix(int ex_i, int ex_j);
  void defaultMatrix();
  void outputMatrix();
};

class CustomException : public std::exception {
  // Custom exception class
 private:
  char const* message_;

 public:
  // Constructor simply copies the message given to it to a field of a class
  explicit CustomException(char const* msg) { message_ = msg; }
  // What is default exception function that returns an explanatory string
  char const* what() { return message_; }
};

#endif  // CPP1_S21_MATRIXPLUS_0_S21_MATRIX_OOP_H
