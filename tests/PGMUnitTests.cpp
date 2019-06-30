#include <images/BinaryPGM.hpp>
#include <fstream>
#include <iterator>

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

const std::string path = "..\\..\\..\\tests\\TestInput\\BinaryPGM\\";



BOOST_AUTO_TEST_SUITE(PGMUnitTests)

BOOST_AUTO_TEST_SUITE(BinaryPGMTests) 

BOOST_AUTO_TEST_CASE(ReadOneSymbolImage) {
    std::string file_path = path + "OneSymbolImage.pgm";
    std::string file_format = "P5";
    size_t height = 1;
    size_t width = 1;
    size_t max_value = 255;
    char content = 'I';

    BinaryPGM image(file_path);

    image.load();

    BOOST_CHECK_EQUAL(image.get_format_id(), file_format);
    BOOST_CHECK_EQUAL(image.get_height(), height);
    BOOST_CHECK_EQUAL(image.get_width(), width);
    BOOST_CHECK_EQUAL(image.get_max_value(), max_value);
    BOOST_CHECK_EQUAL(image.get_pixel(0, 0), content);
}


BOOST_AUTO_TEST_CASE(LoadImage) {
    std::string file_name = "coins.pgm";
    std::string input_file = path + file_name;
    std::string result_file = path + "temp\\" + file_name;

     BinaryPGM image(result_file);

     image.load();
}

BOOST_AUTO_TEST_SUITE_END(/*BinaryPGMTests*/)

BOOST_AUTO_TEST_SUITE_END(/*PGMUnitTests*/)