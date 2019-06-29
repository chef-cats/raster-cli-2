#include <utils/FileOperations.hpp>
#include <fstream>

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>

namespace fop = file::operations;
const char special_symbol = '#';
const std::string path_to_files = "..\\..\\..\\tests\\TestInput\\FileOperations\\";

BOOST_AUTO_TEST_SUITE(FileOperationsUnitTests) 

BOOST_AUTO_TEST_SUITE(PositiveTests)

BOOST_AUTO_TEST_SUITE(SkipTests)

BOOST_AUTO_TEST_CASE(SkipOneLine) {
  std::string file_name = path_to_files + "SkipOneLine.txt";
  std::ifstream file(file_name);
  if (!file) {
    BOOST_FAIL("Can't open file");
  }
  
  fop::skip_lines(file, file_name, special_symbol);
  BOOST_CHECK_EQUAL(file.peek(), EOF);
}

BOOST_AUTO_TEST_CASE(SkipSeqOfLines) {
  std::string file_name = path_to_files + "SkipSeqOfLines.txt";
  std::ifstream file(file_name);
  if (!file) {
    BOOST_FAIL("Can't open file");
  }

  fop::skip_lines(file, file_name, special_symbol);
  BOOST_CHECK_EQUAL(file.peek(), EOF);
}

BOOST_AUTO_TEST_CASE(SkipAndReadOneLine) {
  std::string file_name = path_to_files + "SkipAndReadOneLine.txt";
  std::ifstream file(file_name);
  if (!file) {
    BOOST_FAIL("Can't open file");
  }

  fop::skip_lines(file, file_name, special_symbol);
  BOOST_CHECK_NE(file.peek(), EOF);
  std::string buffer;
  fop::read_line(file, file_name);
  BOOST_CHECK_EQUAL(file.peek(), EOF);
}

BOOST_AUTO_TEST_CASE(OneLineBetweenComments) {
  std::string file_name = path_to_files + "OneLineBetweenComments.txt";
  std::ifstream file(file_name);
  if (!file) {
    BOOST_FAIL("Can't open file");
  }

  fop::skip_lines(file, file_name, special_symbol);
  BOOST_CHECK_NE(file.peek(), EOF);
  std::string buffer;
  fop::read_line(file, buffer);
  BOOST_CHECK_NE(file.peek(), EOF);
  fop::skip_lines(file, file_name, special_symbol);
  BOOST_CHECK_EQUAL(file.get(), EOF);
}

BOOST_AUTO_TEST_SUITE_END(/*SkipTests*/)

// ============================================================================

BOOST_AUTO_TEST_SUITE(ReadLineTests)

BOOST_AUTO_TEST_CASE(ReadOneLine) {
  std::string file_name = path_to_files + "ReadOneLine.txt";
  std::ofstream ofile(file_name);
  if (!ofile) {
    BOOST_FAIL("Can't open file");
  }

  std::string text = "some text";
  
  ofile << text;
  BOOST_CHECK_EQUAL(ofile.tellp(), text.size());
  ofile.close();

  std::ifstream ifile(file_name);
  if (!ifile) {
    BOOST_FAIL("Can't open file");
  }
  std::string buffer;
  fop::read_line(ifile, buffer);
  BOOST_CHECK_EQUAL(text, buffer);
  BOOST_CHECK_EQUAL(ifile.peek(), EOF);
}


BOOST_AUTO_TEST_CASE(ReadTwoLines) {
  std::string file_name = path_to_files + "ReadTwoLines.txt";
  std::ofstream ofile(file_name);
  if (!ofile) {
    BOOST_FAIL("Can't open file");
  }
  std::string first_line = "some text";
  std::string second_line = "another text";
  std::string text = first_line + "\n\n" + second_line;

  ofile << text;
  ofile.close();

  std::ifstream ifile(file_name);
  if (!ifile) {
    BOOST_FAIL("Can't open file");
  }
  std::string buffer;
  fop::read_line(ifile, buffer);
  BOOST_CHECK_EQUAL(first_line, buffer);
  BOOST_CHECK_NE(ifile.peek(), EOF);
  fop::read_line(ifile, buffer);
  BOOST_CHECK_EQUAL(second_line, buffer);
  BOOST_CHECK_EQUAL(ifile.peek(), EOF);
}

BOOST_AUTO_TEST_SUITE_END(/*ReadLineTests*/)

//=============================================================================

BOOST_AUTO_TEST_SUITE(ReadVector) 

BOOST_AUTO_TEST_CASE(ReadOneVector) {
  std::string file_name = path_to_files + "ReadTwoLines.txt";
  std::ofstream ofile(file_name);
  if (!ofile) {
    BOOST_FAIL("Can't open file");
  }

  std::vector<int> data = {1, 5, 3, 7, 200};
  for (auto element : data) {
    ofile << element << " ";
  }
  BOOST_CHECK_EQUAL(ofile.good(), true);
  ofile.close();

  std::ifstream ifile(file_name);
  if (!ifile) {
    BOOST_FAIL("Can't open file");
  }
  std::vector<int> result;
  int elem;
  while (ifile && ifile >> elem) {
    result.push_back(elem);
  }
  BOOST_NOEXCEPT(fop::file_healthcheck(ifile, file_name));
  BOOST_CHECK_EQUAL(data.size(), result.size());

  size_t size = result.size();
  for (int i = 0; i < size; ++i) {
    BOOST_CHECK_EQUAL(data[i], result[i]);
  }
}

BOOST_AUTO_TEST_SUITE_END(ReadVector)

//=============================================================================

BOOST_AUTO_TEST_SUITE_END(/*PositiveTests*/)

BOOST_AUTO_TEST_SUITE_END(/*FileOperationsUnitTests*/)