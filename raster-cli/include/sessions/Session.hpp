#pragma once

#include <images/ImageFactory.hpp>
#include <operations/Operation.hpp>
#include <utils/Types.hpp>
#include <sessions/SessionInfo.hpp>

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

    void apply_transformation(TransformationID id);

    void undo_last_operation();

    void add_image(const std::string& image);

    void save_all();

    SessionInfo get_info() const;

  private:
    void add_transformation_to_all_images(std::unique_ptr<const Operation> operation);

    uint64_t _id;

    class PendingImageTransformations;
    std::vector<PendingImageTransformations> _pending_image_transformations;

    SessionInfo _session_info;
};

class Session::PendingImageTransformations {
  public:
    PendingImageTransformations(const std::string& image);

    void add_transformation(std::unique_ptr<const Operation> operation);

    void cancel_last_transformation();

    void execute_transformations();

    const Image& get_image() const;

  private:
    std::unique_ptr<Image> _image;
    std::vector<std::unique_ptr<const Operation>> _operations;
};
