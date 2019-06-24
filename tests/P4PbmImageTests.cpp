#include <P4PbmImage.hpp>

#include <boost/test/unit_test.hpp>

#include <fstream>
#include <iostream>

BOOST_AUTO_TEST_SUITE(P4PbmImageTests)

BOOST_AUTO_TEST_CASE(ReadWriteTest) {
  const std::string read_file = "../../../tests/testData/P4Sample.pbm";
  const std::string write_file = "../../../tests/testData/temp/P4SampleTestOutput.pbm";

  P4PbmImage image(read_file);

  {
    std::ifstream in(image._file_path);
    BOOST_REQUIRE(in.is_open());
    image.read(in);
  }

  {
    std::ofstream out(write_file);
    BOOST_REQUIRE(out.is_open());
    image.write(out);
  }

  {
    std::ifstream in_original(image._file_path);
    BOOST_REQUIRE(in_original.is_open());

    std::ifstream in_copy(write_file);
    BOOST_REQUIRE(in_copy.is_open());

    const std::string content_original((std::istreambuf_iterator<char>(in_original)),
                                       (std::istreambuf_iterator<char>()));

    const std::string content_copy((std::istreambuf_iterator<char>(in_copy)),
                                   (std::istreambuf_iterator<char>()));

    BOOST_CHECK_EQUAL(content_original, content_copy);
  }
}

BOOST_AUTO_TEST_SUITE_END()
