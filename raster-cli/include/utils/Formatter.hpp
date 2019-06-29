#pragma once

#include <sstream>
#include <string>

/**
 * Formatter
 *
 * This class gives an opportunity to concatenate string value with variables values.
 * The formatter have stream behaviour and also it easy to cast it to std::string.
 * All types of data which have an operator<< can be written into this formatter.
 *
 * Usage example:
 *     Formatter() << variable << 13 << ", bar" << myClass;
 */

class Formatter {
  public:
    Formatter() = default;
    Formatter(const Formatter&) = delete;
    Formatter& operator=(Formatter&) = delete;
    ~Formatter() = default;

    template <typename Type>
    Formatter& operator<<(const Type& value) {
        _stream << value;
        return *this;
    }

    std::string str() const { return _stream.str(); }
    operator std::string() const { return _stream.str(); }

  private:
    std::stringstream _stream;
};
