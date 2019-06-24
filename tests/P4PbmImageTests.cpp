#include <P4PbmImage.hpp>

#include <boost/test/unit_test.hpp>

#include <fstream>
#include <iostream>

BOOST_AUTO_TEST_SUITE(P4PbmImageTests)

BOOST_AUTO_TEST_CASE(ReadWriteTest) {
  P4PbmImage image("../../../tests/P4Sample.pbm");

  {
    std::ifstream in(image._file_path, std::ifstream::binary);
    BOOST_REQUIRE(in.is_open());
    image.read(in);
  }

  {
    std::ofstream out("../../../tests/testData/P4SampleTestOutput.pbm");
    BOOST_REQUIRE(out);
    image.write(out);
  }

  { 
	std::ifstream in_original(image._file_path, std::ifstream::binary);
    BOOST_REQUIRE(in_original.is_open());

	std::ifstream in_copy("../../../tests/testData/temp/P4SampleTestOutput.pbm", std::ifstream::binary);
    BOOST_REQUIRE(in_copy.is_open());

	const std::string content_original((std::istreambuf_iterator<char>(in_original)),
                        (std::istreambuf_iterator<char>()));

	const std::string content_copy((std::istreambuf_iterator<char>(in_copy)),
                                           (std::istreambuf_iterator<char>()));

	BOOST_CHECK_EQUAL(content_original, content_copy);
  }
}

BOOST_AUTO_TEST_SUITE_END()
