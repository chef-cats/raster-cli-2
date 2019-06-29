#pragma once

#include <utils/Types.hpp>

#include <string>
#include <vector>

/**
 * Class to manage a session.
 *
 * Provides interface for working with images.
 * @todo Currently this is only a mock-up of the real class. Implement it properly.
 */
class Session {
public:
  Session(unsigned long long id, const std::vector<std::string>& images) {}

  void all_to_grayscale() {}

  void all_to_monochrome() {}

  void all_to_negative() {}

  void rotate_all(Direction direction) {}

  void undo_last_operation() {}

  void add_image(const std::string& image) {}

  void remove_image() {}

  void save_all() {}

  class Info {
  public:
    unsigned long long get_id() const { return 0; }

    const std::vector<std::string>& get_images() const {
      return std::vector<std::string>();
    }

    class OperationInfo {
    public:
      size_t get_count() const { return 0; }

      OperationID get_id() const { return OperationID(); }
    };

    const std::vector<OperationInfo>& get_operations_info() const {
      return std::vector<OperationInfo>();
    }
  };

  Info get_info() const { return Info(); }
};