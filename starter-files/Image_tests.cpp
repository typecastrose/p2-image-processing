#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

// Tests full image suite
TEST(test_image_basic) {
  Pixel red = {255, 0, 0};
  Pixel green = {0, 255, 0};
  Image img;
  Image_init(&img, 3, 4);

  ASSERT_EQUAL(Image_width(&img), 3);
  ASSERT_EQUAL(Image_height(&img), 4);

  Image_fill(&img, red);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 2, 2), red));

  Image_set_pixel(&img, 0, 0, green);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 0), green));
}

// Test streaming invalid pixels
// (Test to avoid crash)
TEST(test_image_stream_invalid_pixel_values) {
  Image img;
  
  // A very poorly behaved input PPM, that has incorrect range
  string invalid_pixels = "P3 2 2\t255 255 0 0\n0\300 0 \n0 0 300 255 255 255 \n";
  std::istringstream ss(invalid_pixels);

  Image_init(&img, ss);
  
}

// Tests reading and printing from string
TEST(test_image_from_and_to_stream) {
  Image img;

  // A very poorly behaved input PPM.
  string input = "P3 2 2\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n";
  std::istringstream ss_input(input);
  Image_init(&img, ss_input);

  // Should be well behaved when you print it though!
  string output_correct = "P3\n2 2\n255\n255 0 0 0 255 0 \n0 0 255 255 255 255 \n";
  std::ostringstream ss_output;
  Image_print(&img, ss_output);
  string actual = ss_output.str();
  std::cout << actual << std::endl;
  ASSERT_EQUAL(actual, output_correct);
}

TEST(test_image_min_dimensions) {
  Image img;
  Image_init(&img, 1, 1);
  ASSERT_EQUAL(Image_width(&img), 1);
  ASSERT_EQUAL(Image_height(&img), 1);
}

TEST_MAIN() // Do NOT put a semicolon here
