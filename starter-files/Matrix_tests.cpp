#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}

// Tests initialization
TEST(test_init_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  Matrix_init(&mat, 3, 5);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), 0);
    }
  }
  ASSERT_EQUAL(Matrix_width(&mat), 3);
  ASSERT_EQUAL(Matrix_height(&mat), 5);
}

// Tests the fill border basic
TEST(test_fill_border) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, 0);
  Matrix_fill_border(&mat, 1);

  

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      if((c == 0) || (r == 0) || (c == width-1) || (r == height - 1)) {
        ASSERT_TRUE(*Matrix_at(&mat, r, c))
      } else {
        ASSERT_FALSE(*Matrix_at(&mat, r, c));
      }
    }
  }
}

// Tests the max function basic
TEST(test_max_basic) {
  Matrix mat;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, 0);
  int max = 100;
  *Matrix_at(&mat, 1, 2) = max;

  

  ASSERT_EQUAL(Matrix_max(&mat), max)
}

// Tests max function when multiple maximums present
TEST(test_max_multi) {
  Matrix mat;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, 0);
  int max = 100;
  Matrix_fill_border(&mat, max);

  ASSERT_EQUAL(Matrix_max(&mat), max)
}

// Tests nax function wiht negative nums and multiple max
TEST(test_max_negative_multi) {
  Matrix mat;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, -100);
  int max = 0;
  Matrix_fill_border(&mat, max);

  ASSERT_EQUAL(Matrix_max(&mat), max)
}

// Tests basic print
TEST(test_print_basic) {
    Matrix mat;
    const int width = 3;
    const int height = 5;
    const int value = 42;
    
    Matrix_init(&mat, width, height);
    Matrix_fill(&mat, value);
    
    stringstream output;
    Matrix_print(&mat, output);
    
    string printed = output.str();
    
    // Create the expected output
    stringstream expected_stream;
    expected_stream << width << " " << height << endl;
    
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            expected_stream << value << " ";
        }
        expected_stream << endl;
    }
    
    string expected = expected_stream.str();
    ASSERT_EQUAL(printed, expected);
}

// Tests basic column of min value
// Checking against other mins out of
// row bounds and in the same column
TEST(test_column_of_min_value_in_row) {
    Matrix mat;
    const int width = 3;
    const int height = 3;
    const int value = 0;
    

    
    Matrix_init(&mat, width, height);
    Matrix_fill(&mat, value);

    *Matrix_at(&mat, 0, 0) = 0;
    *Matrix_at(&mat, 0, 1) = -100;
    *Matrix_at(&mat, 0, 2) = -200;
    
    *Matrix_at(&mat, 1, 0) = -300;
    *Matrix_at(&mat, 1, 1) = -200;
    *Matrix_at(&mat, 1, 2) = 0;
    
    *Matrix_at(&mat, 2, 0) = 0;
    *Matrix_at(&mat, 2, 1) = -400;
    *Matrix_at(&mat, 2, 2) = -600;
    
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 0, 2), 1);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 1, 0, 2), 0);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 2, 0, 2), 1);
}

// Tests basic min value in row
// Checking against other mins out of
// row bounds and in the same column
TEST(test_min_value_in_row) {
    Matrix mat;
    const int width = 3;
    const int height = 3;
    const int value = 0;
    

    
    Matrix_init(&mat, width, height);
    Matrix_fill(&mat, value);

    *Matrix_at(&mat, 0, 0) = 0;
    *Matrix_at(&mat, 0, 1) = -100;
    *Matrix_at(&mat, 0, 2) = -200;
    
    *Matrix_at(&mat, 1, 0) = -300;
    *Matrix_at(&mat, 1, 1) = -200;
    *Matrix_at(&mat, 1, 2) = 0;
    
    *Matrix_at(&mat, 2, 0) = 0;
    *Matrix_at(&mat, 2, 1) = -400;
    *Matrix_at(&mat, 2, 2) = -600;
    
    ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 0, 2), -100);
    ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 0, 2), -300);
    ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 2, 0, 2), -400);
}


// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

TEST_MAIN() // Do NOT put a semicolon here
