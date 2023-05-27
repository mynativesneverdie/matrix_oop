#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(mutatorsTests, SetCols1) {
  S21Matrix matrix(3, 3);
  matrix.setCols(2);
  EXPECT_EQ(2, matrix.getCols());
}

TEST(mutatorsTests, SetCols2) {
  S21Matrix matrix(3, 3);
  matrix.setCols(4);
  EXPECT_EQ(4, matrix.getCols());
}

TEST(mutatorsTests, SetCols3) {
  S21Matrix matrix(3, 3);
  matrix.setCols(3);
  EXPECT_EQ(3, matrix.getCols());
}

TEST(mutatorsTests, SetRows1) {
  S21Matrix matrix(3, 3);
  matrix.setRows(2);
  EXPECT_EQ(2, matrix.getRows());
}

TEST(mutatorsTests, SetRows2) {
  S21Matrix matrix(3, 3);
  matrix.setRows(4);
  EXPECT_EQ(4, matrix.getRows());
}

TEST(mutatorsTests, SetRows3) {
  S21Matrix matrix(3, 3);
  matrix.setRows(3);
  EXPECT_EQ(3, matrix.getRows());
}

TEST(constructorsTests, InitMatrixByDefaultConstructor1) {
  S21Matrix matrix;
  EXPECT_EQ(0, matrix.getCols());
  EXPECT_EQ(0, matrix.getRows());
}

TEST(constructorsTests, InitMatrixByParametrizedConstructor1) {
  S21Matrix matrix(2, 2);
  EXPECT_EQ(2, matrix.getCols());
  EXPECT_EQ(2, matrix.getRows());
}

TEST(constructorsTests, InitMatrixByParametrizedConstructor2) {
  S21Matrix matrix(10, 10);
  EXPECT_EQ(10, matrix.getCols());
  EXPECT_EQ(10, matrix.getRows());
}

TEST(constructorsTests, InitMatrixByParametrizedConstructorThrow) {
  EXPECT_ANY_THROW(S21Matrix exception(0, -2));
}

TEST(constructorsTests, CopyConstructor1) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(matrix_a);
  EXPECT_EQ(3, matrix_b.getCols());
  EXPECT_EQ(3, matrix_b.getRows());
}

TEST(constructorsTests, CopyConstructor2) {
  S21Matrix matrix_a(15, 15);
  S21Matrix matrix_b(matrix_a);
  EXPECT_EQ(15, matrix_b.getCols());
  EXPECT_EQ(15, matrix_b.getRows());
}

TEST(constructorsTests, MoveConstructor1) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(std::move(matrix_a));
  EXPECT_EQ(3, matrix_b.getCols());
  EXPECT_EQ(3, matrix_b.getRows());
  EXPECT_EQ(0, matrix_a.getCols());
  EXPECT_EQ(0, matrix_a.getRows());
}

TEST(constructorsTests, MoveConstructor2) {
  S21Matrix matrix_a(12, 12);
  S21Matrix matrix_b(std::move(matrix_a));
  EXPECT_EQ(12, matrix_b.getCols());
  EXPECT_EQ(12, matrix_b.getRows());
  EXPECT_EQ(0, matrix_a.getCols());
  EXPECT_EQ(0, matrix_a.getRows());
}

TEST(operationsWithMatrixTests, eqMatrix1) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  EXPECT_EQ(1, matrix_a.EqMatrix(matrix_b));
}

TEST(operationsWithMatrixTests, eqMatrix2) {
  S21Matrix matrix_a;
  S21Matrix matrix_b;
  EXPECT_EQ(1, matrix_a.EqMatrix(matrix_b));
}

TEST(operationsWithMatrixTests, eqMatrix3) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  matrix_a.setElement(2, 2, 0.01);
  matrix_b.setElement(2, 2, 0.01);
  EXPECT_EQ(1, matrix_a.EqMatrix(matrix_b));
}

TEST(operationsWithMatrixTests, eqMatrix4) {
  S21Matrix matrix_a(10, 10);
  S21Matrix matrix_b(10, 10);
  matrix_a.setElement(4, 5, 0.001);
  matrix_b.setElement(4, 5, 0.001);
  EXPECT_EQ(1, matrix_a.EqMatrix(matrix_b));
}

TEST(operationsWithMatrixTests, operatorEqMatrix1) {
  S21Matrix matrix_a(10, 10);
  S21Matrix matrix_b(10, 10);
  matrix_a.setElement(4, 5, 0.001);
  matrix_b.setElement(4, 5, 0.001);
  EXPECT_TRUE(matrix_a == matrix_b);
}

TEST(operationsWithMatrixTests, notEqMatrix1) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(2, 2);
  EXPECT_EQ(0, matrix_a.EqMatrix(matrix_b));
}

TEST(operationsWithMatrixTests, notEqMatrix2) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(4, 4);
  EXPECT_EQ(0, matrix_a.EqMatrix(matrix_b));
}

TEST(operationsWithMatrixTests, notEqMatrix3) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  matrix_a.setElement(2, 1, 0.001);
  matrix_b.setElement(1, 2, 0.001);
  EXPECT_EQ(0, matrix_a.EqMatrix(matrix_b));
}

TEST(operationsWithMatrixTests, operatorEqMatrix2) {
  S21Matrix matrix_a(10, 10);
  S21Matrix matrix_b(10, 10);
  matrix_a.setElement(4, 5, 0.002);
  matrix_b.setElement(4, 5, 0.001);
  EXPECT_FALSE(matrix_a == matrix_b);
}

TEST(operationsWithMatrixTests, sumMatrixThrow1) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(4, 4);
  EXPECT_ANY_THROW(matrix_a.SumMatrix(matrix_b));
}

TEST(operationsWithMatrixTests, sumMatrixThrow2) {
  S21Matrix matrix_a(4, 4);
  S21Matrix matrix_b(3, 3);
  EXPECT_ANY_THROW(matrix_a.SumMatrix(matrix_b));
}

TEST(operationsWithMatrixTests, sumMatrix1) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  int digit = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      digit += 1;
      matrix_b.setElement(i, j, digit);
    }
  }
  matrix_a.SumMatrix(matrix_b);
  EXPECT_EQ(1, matrix_a.EqMatrix(matrix_b));
}

TEST(operationsWithMatrixTests, sumMatrix2) {
  S21Matrix matrix_a(5, 5);
  S21Matrix matrix_b(5, 5);
  int digit = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      digit += 1;
      matrix_a.setElement(i, j, digit);
      matrix_b.setElement(i, j, digit);
    }
  }
  matrix_a.SumMatrix(matrix_b);
  digit = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      digit += 1;
      EXPECT_EQ(digit * 2, matrix_a(i, j));
    }
  }
}

TEST(operationsWithMatrixTests, operatorSumMatrix) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  S21Matrix matrix_c;
  int digit = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      digit += 1;
      matrix_b.setElement(i, j, digit);
    }
  }
  matrix_c = matrix_a + matrix_b;
  EXPECT_EQ(1, matrix_c.EqMatrix(matrix_b));
}

TEST(operationsWithMatrixTests, subMatrixThrow1) {
  S21Matrix matrix_a(4, 4);
  S21Matrix matrix_b(3, 3);
  EXPECT_ANY_THROW(matrix_a.SubMatrix(matrix_b));
}

TEST(operationsWithMatrixTests, subMatrixThrow2) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(4, 4);
  EXPECT_ANY_THROW(matrix_a.SubMatrix(matrix_b));
}

TEST(operationsWithMatrixTests, subMatrix1) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  int digit = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      digit += 1;
      matrix_a.setElement(i, j, digit);
    }
  }
  matrix_a.SubMatrix(matrix_b);
  digit = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      digit += 1;
      EXPECT_EQ(digit, matrix_a(i, j));
    }
  }
}

TEST(operationsWithMatrixTests, subMatrix2) {
  S21Matrix matrix_a(5, 5);
  S21Matrix matrix_b(5, 5);
  int digit = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      digit += 1;
      matrix_a.setElement(i, j, digit);
      matrix_b.setElement(i, j, digit);
    }
  }
  matrix_a.SubMatrix(matrix_b);
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++) EXPECT_EQ(0, matrix_a(i, j));
}

TEST(operationsWithMatrixTests, operatorSubMatrix) {
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_b(3, 3);
  S21Matrix matrix_c;
  int digit = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      digit += 1;
      matrix_a.setElement(i, j, digit);
    }
  }
  matrix_c = matrix_a - matrix_b;
  EXPECT_EQ(1, matrix_c.EqMatrix(matrix_a));
}

TEST(operationsWithMatrixTests, mulNumber) {
  S21Matrix matrix(3, 3);
  int digit = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      digit += 1;
      matrix.setElement(i, j, digit);
    }
  }
  const double num = 2;
  digit = 0;
  matrix.MulNumber(num);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      digit += 1;
      EXPECT_EQ(digit * num, matrix(i, j));
    }
  }
}

TEST(operationsWithMatrixTests, operatorMulNumber) {
  S21Matrix matrix(3, 3);
  int digit = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      digit += 1;
      matrix.setElement(i, j, digit);
    }
  }

  const double num = 2;
  digit = 0;
  matrix = matrix * num;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      digit += 1;
      EXPECT_EQ(digit * num, matrix(i, j));
    }
  }
}

TEST(operationsWithMatrixTests, mulMatrixThrow1) {
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(3, 3);
  EXPECT_ANY_THROW(matrix_a.MulMatrix(matrix_b));
}

TEST(operationsWithMatrixTests, mulMatrix1) {
  S21Matrix matrix_a(2, 3);
  matrix_a.setElement(0, 0, 1);
  matrix_a.setElement(0, 1, 2);
  matrix_a.setElement(0, 2, 1);
  matrix_a.setElement(1, 0, 0);
  matrix_a.setElement(1, 1, 1);
  matrix_a.setElement(1, 2, 2);

  S21Matrix matrix_b(3, 2);
  matrix_b.setElement(0, 0, 1);
  matrix_b.setElement(0, 1, 0);
  matrix_b.setElement(1, 0, 0);
  matrix_b.setElement(1, 1, 1);
  matrix_b.setElement(2, 0, 1);
  matrix_b.setElement(2, 1, 1);

  S21Matrix matrix_res(2, 2);
  matrix_res.setElement(0, 0, 2);
  matrix_res.setElement(0, 1, 3);
  matrix_res.setElement(1, 0, 2);
  matrix_res.setElement(1, 1, 3);

  matrix_a.MulMatrix(matrix_b);

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      EXPECT_EQ(matrix_res(i, j), matrix_a(i, j));
}

TEST(operationsWithMatrixTests, mulMatrix2) {
  S21Matrix matrix_a(3, 2);
  matrix_a.setElement(0, 0, 1);
  matrix_a.setElement(0, 1, 0);
  matrix_a.setElement(1, 0, 0);
  matrix_a.setElement(1, 1, 1);
  matrix_a.setElement(2, 0, 1);
  matrix_a.setElement(2, 1, 1);

  S21Matrix matrix_b(2, 3);
  matrix_b.setElement(0, 0, 1);
  matrix_b.setElement(0, 1, 2);
  matrix_b.setElement(0, 2, 1);
  matrix_b.setElement(1, 0, 0);
  matrix_b.setElement(1, 1, 1);
  matrix_b.setElement(1, 2, 2);

  S21Matrix matrix_res(3, 3);
  matrix_res.setElement(0, 0, 1);
  matrix_res.setElement(0, 1, 2);
  matrix_res.setElement(0, 2, 1);
  matrix_res.setElement(1, 0, 0);
  matrix_res.setElement(1, 1, 1);
  matrix_res.setElement(1, 2, 2);
  matrix_res.setElement(2, 0, 1);
  matrix_res.setElement(2, 1, 3);
  matrix_res.setElement(2, 2, 3);

  matrix_a.MulMatrix(matrix_b);

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      EXPECT_EQ(matrix_res(i, j), matrix_a(i, j));
}

TEST(operationsWithMatrixTests, operatorMulMatrix) {
  S21Matrix matrix_a(2, 3);
  matrix_a.setElement(0, 0, 1);
  matrix_a.setElement(0, 1, 2);
  matrix_a.setElement(0, 2, 1);
  matrix_a.setElement(1, 0, 0);
  matrix_a.setElement(1, 1, 1);
  matrix_a.setElement(1, 2, 2);

  S21Matrix matrix_b(3, 2);
  matrix_b.setElement(0, 0, 1);
  matrix_b.setElement(0, 1, 0);
  matrix_b.setElement(1, 0, 0);
  matrix_b.setElement(1, 1, 1);
  matrix_b.setElement(2, 0, 1);
  matrix_b.setElement(2, 1, 1);

  S21Matrix matrix_res(2, 2);
  matrix_res.setElement(0, 0, 2);
  matrix_res.setElement(0, 1, 3);
  matrix_res.setElement(1, 0, 2);
  matrix_res.setElement(1, 1, 3);

  S21Matrix matrix_ret = matrix_a * matrix_b;

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      EXPECT_EQ(matrix_res(i, j), matrix_ret(i, j));
}

TEST(operationsWithMatrixTests, transposeMatrix1) {
  S21Matrix matrix_a(2, 2);
  matrix_a.setElement(0, 0, 1);
  matrix_a.setElement(0, 1, 2);
  matrix_a.setElement(1, 0, 3);
  matrix_a.setElement(1, 1, 4);

  S21Matrix matrix_b = matrix_a.Transpose();

  S21Matrix matrix_res(2, 2);
  matrix_res.setElement(0, 0, 1);
  matrix_res.setElement(0, 1, 3);
  matrix_res.setElement(1, 0, 2);
  matrix_res.setElement(1, 1, 4);

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      EXPECT_EQ(matrix_res(i, j), matrix_b(i, j));
}

TEST(operationsWithMatrixTests, transposeMatrix2) {
  S21Matrix matrix_a(3, 2);
  matrix_a.setElement(0, 0, 1);
  matrix_a.setElement(0, 1, 2);
  matrix_a.setElement(1, 0, 3);
  matrix_a.setElement(1, 1, 4);
  matrix_a.setElement(2, 0, 5);
  matrix_a.setElement(2, 1, 6);

  S21Matrix matrix_b = matrix_a.Transpose();

  S21Matrix matrix_res(2, 3);
  matrix_res.setElement(0, 0, 1);
  matrix_res.setElement(0, 1, 3);
  matrix_res.setElement(0, 2, 5);
  matrix_res.setElement(1, 0, 2);
  matrix_res.setElement(1, 1, 4);
  matrix_res.setElement(1, 2, 6);

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++)
      EXPECT_EQ(matrix_res(i, j), matrix_b(i, j));
}

TEST(operationsWithMatrixTests, determinantTest1) {
    S21Matrix matrix(2, 2);

    matrix.setElement(0, 0, 1);
    matrix.setElement(0, 1, 2);
    matrix.setElement(1,0,3);
    matrix.setElement(1, 1, 4);

    EXPECT_EQ(-2, matrix.Determinant());
}

TEST(operationsWithMatrixTests, determinantThrowTest) {
    S21Matrix matrix(3, 2);
    EXPECT_ANY_THROW(matrix.Determinant());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}