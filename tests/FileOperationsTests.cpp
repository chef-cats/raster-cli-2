#include <fstream>
#include <utils/FileOperations.hpp>

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
    std::string file_name = path_to_files + "temp\\ReadOneLine.txt";
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
    std::string file_name = path_to_files + "temp\\ReadTwoLines.txt";
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

BOOST_AUTO_TEST_CASE(ReadVectorTxt) {
    std::string file_name = path_to_files + "temp\\ReadVectorTxt.txt";
    std::ofstream ofile(file_name);
    if (!ofile) {
        BOOST_FAIL("Can't open file");
    }

    std::vector<int> data = {1, 5, 3, 7, 200};
    uint64_t elem_cnt = data.size();

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
    uint64_t read_elem;

    read_elem = fop::read_from_text_file(ifile, elem_cnt, result);
    
    BOOST_NOEXCEPT(fop::file_healthcheck(ifile, file_name));
    BOOST_CHECK_EQUAL(read_elem, elem_cnt);

    size_t size = result.size();
    for (int i = 0; i < size; ++i) {
        BOOST_CHECK_EQUAL(data[i], result[i]);
    }
}

BOOST_AUTO_TEST_CASE(WriteVectorTxt) {
    std::string file_name = path_to_files + "temp\\WriteVectorTxt.txt";
    std::ofstream ofile(file_name);
    if (!ofile) {
        BOOST_FAIL("Can't open file");
    }

    std::vector<int> data = {1, 5, 3, 7, 200};
    size_t elem_cnt = data.size();
    size_t written_elem;

    written_elem = fop::write_to_text_file(ofile, elem_cnt, data);
    
    BOOST_CHECK_EQUAL(ofile.good(), true);
    BOOST_CHECK_EQUAL(written_elem, elem_cnt);

    ofile.close();

    std::ifstream ifile(file_name);
    if (!ifile) {
        BOOST_FAIL("Can't open file");
    }
    std::vector<int> result;
    result.resize(elem_cnt);
    for (size_t i = 0; i < elem_cnt; ++i) {
        ifile >> result[i];
        BOOST_NOEXCEPT(fop::file_healthcheck(ifile, file_name));
        BOOST_CHECK_EQUAL(data[i], result[i]);
    }
    BOOST_CHECK_EQUAL(ifile.peek(), EOF);
}

BOOST_AUTO_TEST_CASE(ReadVectorBinary) {
    using type = int;

    std::string file_name = path_to_files + "temp\\ReadVectorBinary.txt";
    std::ofstream ofile(file_name);
    if (!ofile) {
        BOOST_FAIL("Can't open file");
    }

    std::vector<type> container = {1, 5, 3, 7, 200};
    size_t size = container.size();
    size_t input_bytes = size * sizeof(type);

    ofile.write((const char*)container.data(), input_bytes);
    BOOST_CHECK_EQUAL(ofile.good(), true);
    ofile.close();

    std::ifstream ifile(file_name);
    if (!ifile) {
        BOOST_FAIL("Can't open file");
    }

    std::vector<int> result(size);
    uint64_t read_bytes;
    read_bytes = fop::read_from_binary_file(ifile, input_bytes, result);


    BOOST_NOEXCEPT(fop::file_healthcheck(ifile, file_name));

    for (int i = 0; i < size; ++i) {
        BOOST_CHECK_EQUAL(container[i], result[i]);
    }
}

BOOST_AUTO_TEST_CASE(WriteVectorBinary) {
   using type = int;
    std::string file_name = path_to_files + "temp\\WriteVectorBinary.txt";
    std::ofstream ofile(file_name);
    if (!ofile) {
        BOOST_FAIL("Can't open file");
    }

    std::vector<int> container = {1, 5, 3, 7, 200};
    uint64_t size = container.size();
    uint64_t input_bytes = size * sizeof(type);
    uint64_t written_bytes;

    written_bytes = fop::write_to_binary_file(ofile, input_bytes, container);
    
    BOOST_CHECK_EQUAL(ofile.good(), true);
    BOOST_CHECK_EQUAL(written_bytes, input_bytes);
    ofile.close();

    std::ifstream ifile(file_name);
    if (!ifile) {
        BOOST_FAIL("Can't open file");
    }

    std::vector<int> result;
    result.resize(size);
    ifile.read((char*)result.data(), input_bytes);

    BOOST_NOEXCEPT(fop::file_healthcheck(ifile, file_name));
    BOOST_CHECK_EQUAL(ifile.peek(), EOF);
    
    for (size_t i = 0; i < size; ++i) {
        BOOST_CHECK_EQUAL(container[i], result[i]);
    }
}

//=============================================================================

BOOST_AUTO_TEST_SUITE_END(/*PositiveTests*/)

BOOST_AUTO_TEST_SUITE_END(/*FileOperationsUnitTests*/)