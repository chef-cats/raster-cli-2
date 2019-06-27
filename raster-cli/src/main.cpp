#include <cstdlib>
#include <iostream>
#include <operations/Load.hpp>
#include <images/PGM.hpp>

int main() {
  Load load;
  PGM image("C:\\Users\\Yoanna\\Desktop\\TestFile.txt");
  load.apply_to(image);

  std::cout << "Format: " << image.get_format_id() << std::endl;
  std::cout << "Lines: " << image.get_height() << std::endl;
  std::cout << "Column: " << image.get_width() << std::endl;
  std::cout << "Max value: " << image.get_max_value() << std::endl;
  return EXIT_SUCCESS;
}