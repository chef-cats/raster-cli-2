#pragma once

#include <utils/Types.hpp>
#include <images/ImageFactory.hpp>
#include <operations/Operation.hpp>

#include <memory>
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
    Session(uint64_t id, const std::vector<std::string>& images);

    void all_to_grayscale();

    void all_to_monochrome();

    void all_to_negative();

    void rotate_all(Direction direction);

    void undo_last_operation();

    void add_image(const std::string& image);

    void remove_image();

    void save_all();

    class Info;
    Info get_info() const;

  private:
    class OperationsRecord;

	std::vector<OperationsRecord> _records;
};

class Session::OperationsRecord {
  public:
    OperationsRecord(const std::string& image);

    void add_operation();

    void remove_last_operation();

    void execute_operations();

  private:
    std::unique_ptr<Image> _image;
    std::vector<std::unique_ptr<Operation>> _operations;
};

class Session::Info {
  public:
    class OperationInfo;

    uint64_t get_id() const;

    const std::vector<std::string>& get_images() const;

    const std::vector<OperationInfo>& get_operations_info() const;
};

class Session::Info::OperationInfo {
  public:
    size_t get_count() const;

    OperationID get_id() const;
};
