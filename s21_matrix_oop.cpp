#include "s21_matrix_oop.h"

// Constructors
S21Matrix::S21Matrix() { this->defaultMatrix(); }

S21Matrix::~S21Matrix() {
  for (int i = 0; i < _rows; i++) delete[] _matrix[i];

  delete[] _matrix;
  this->defaultMatrix();
}

S21Matrix::S21Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
  if (rows < 1 || cols < 1)
    throw CustomException("Wrong value of rows/columns");

  _matrix = new double*[_rows];
  for (int i = 0; i < _rows; i++) _matrix[i] = new double[_cols];

  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++) _matrix[i][j] = 0;
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix::S21Matrix(other._rows, other._cols) {
  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++) _matrix[i][j] = other._matrix[i][j];
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  _rows = other._rows;
  _cols = other._cols;
  _matrix = other._matrix;
  other.defaultMatrix();
}

// Operations with matrix
bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool ret = true;
  if (other._rows != _rows || other._cols != _cols) {
    ret = false;
  } else {
    for (int i = 0; i < _rows; i++)
      for (int j = 0; j < _cols; j++)
        if (other._matrix[i][j] != _matrix[i][j]) ret = false;
  }
  return ret;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (other._rows != _rows || other._cols != _cols)
    throw CustomException("Matrix dimensions are different");
  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++) _matrix[i][j] += other._matrix[i][j];
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (other._rows != _rows || other._cols != _cols)
    throw CustomException("Matrix dimensions are different");
  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++) _matrix[i][j] -= other._matrix[i][j];
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++) _matrix[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (_rows != other._cols)
    throw CustomException(
        "The number of cols of the 1st matrix "
        "doesn't equal the number of rows of the 2nd matrix");

  double** newMatrix = new double*[_rows];
  for (int i = 0; i < _rows; i++) {
    newMatrix[i] = new double[other._cols];
    for (int j = 0; j < other._cols; j++) {
      double sum = 0;
      for (int k = 0; k < _cols; k++)
        sum += _matrix[i][k] * other._matrix[k][j];
      newMatrix[i][j] = sum;
    }
    delete[] _matrix[i];
  }
  delete[] _matrix;

  _cols = other._cols;
  _matrix = new double*[_rows];
  for (int i = 0; i < _rows; i++) _matrix[i] = new double[other._cols];
  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++) _matrix[i][j] = newMatrix[i][j];

  for (int i = 0; i < _rows; i++) delete[] newMatrix[i];
  delete[] newMatrix;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix ret(_cols, _rows);
  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++) ret._matrix[j][i] = _matrix[i][j];
  return ret;
}

S21Matrix S21Matrix::CalcComplements() {
  if (_rows != _cols) throw CustomException("The matrix is not square");
  if (_rows == 1) return *this;
  S21Matrix ret(_rows, _cols);
  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++) {
      S21Matrix subMatrix = this->HandleMatrix(i, j);  // subMatrix is a minor
      if (subMatrix._rows == 2) {
        ret._matrix[i][j] = ((i + j) % 2 ? -1 : 1) * subMatrix.TwoDet();
      } else if (subMatrix._rows == 1) {
        ret._matrix[i][j] = ((i + j) % 2 ? -1 : 1) * subMatrix.OneDet();
      } else {
        S21Matrix recursive =
            subMatrix.CalcComplements();  // this is a recursive algorithm
        for (int k = 0; k < subMatrix._rows; k++)
          ret._matrix[i][j] +=
              subMatrix._matrix[0][k] * recursive._matrix[0][k];
        if ((i + j) % 2) ret._matrix[i][j] *= -1;
      }
    }
  return ret;
}

double S21Matrix::Determinant() {
  if (_rows != _cols) throw CustomException("The matrix is not square");
  S21Matrix complement = this->CalcComplements();
  double ret = 0;
  for (int i = 0; i < _rows; i++)
    ret += _matrix[0][i] * complement._matrix[0][i];
  return ret;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = this->Determinant();
  if (det == 0) throw CustomException("Matrix determinant is 0");
  S21Matrix complement = this->CalcComplements();
  S21Matrix trasposed = complement.Transpose();
  trasposed.MulNumber(1 / det);
  return trasposed;
}

// Operators
double& S21Matrix::operator()(int row, int col) {
  if (row >= _rows || col >= _cols || col < 0 || row < 0)
    throw CustomException("Incorrect input, index is out of range");
  return _matrix[row][col];
}

bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this == &other) return *this;  // Protection against self assignment
  this->setCols(other._cols);
  this->setRows(other._rows);
  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++) _matrix[i][j] = other._matrix[i][j];
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix ret(*this);
  ret.SumMatrix(other);
  return ret;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix ret(*this);
  ret.SubMatrix(other);
  return ret;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix ret(*this);
  ret.MulMatrix(other);
  return ret;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

S21Matrix operator*(const S21Matrix& thisMatrix, double num) {
  S21Matrix ret(thisMatrix);
  ret.MulNumber(num);
  return ret;
}

// Accessors and mutators
int S21Matrix::getRows() { return _rows; }

int S21Matrix::getCols() { return _cols; }

void S21Matrix::setRows(int newRows) {
  if (newRows < 1) throw CustomException("Rows count should be at least 1");
  if (newRows < _rows) {
    for (int i = newRows; i < _rows; i++) delete[] _matrix[i];
  } else if (newRows > _rows) {
    double** newMatrix = new double*[newRows];
    for (int i = 0; i < newRows; i++) {
      newMatrix[i] = new double[_cols];
      if (i < _rows) {
        for (int j = 0; j < _cols; j++) newMatrix[i][j] = _matrix[i][j];
        delete[] _matrix[i];
      }
    }
    delete[] _matrix;
    _matrix = newMatrix;
  }
  _rows = newRows;
}

void S21Matrix::setCols(int newCols) {
  if (newCols < 1) throw CustomException("Columns count should be at least 1");
  if (newCols > _cols) {
    double** newMatrix = new double*[_rows];
    for (int i = 0; i < _rows; i++) {
      newMatrix[i] = new double[newCols];
      for (int j = 0; j < newCols; j++)
        if (j < _cols) newMatrix[i][j] = _matrix[i][j];
      delete[] _matrix[i];
    }
    delete[] _matrix;
    _matrix = newMatrix;
  } else if (newCols < _cols) {
    for (int i = 0; i < _rows; i++)
      for (int j = newCols; j < _cols; j++) _matrix[i][j] = 0;
  }
  _cols = newCols;
}

void S21Matrix::setElement(int row, int col, double value) {
  _matrix[row][col] = value;
}

// Helpful methods
S21Matrix S21Matrix::HandleMatrix(int ex_i, int ex_j) {
  // Little function to create a minor matrix from a given one by excluding
  // certain row and col
  S21Matrix res(_rows - 1, _cols - 1);
  for (int i = 0, i_b = 0; i < _rows; i++, i_b++) {
    if (i == ex_i) {
      --i_b;
      continue;
    }
    for (int j = 0, j_b = 0; j < _cols; j++, j_b++) {
      if (j == ex_j) {
        --j_b;
        continue;
      }
      res._matrix[i_b][j_b] = _matrix[i][j];
    }
  }
  return res;
}

int S21Matrix::TwoDet() {
  return _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
}

int S21Matrix::OneDet() { return _matrix[0][0]; }

void S21Matrix::defaultMatrix() {
  _rows = _cols = 0;
  _matrix = nullptr;
}

void S21Matrix::outputMatrix() {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) std::cout << _matrix[i][j] << "  ";
    std::cout << std::endl;
  }
}