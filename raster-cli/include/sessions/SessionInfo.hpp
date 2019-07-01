#pragma once

#include <utils/Types.hpp>

#include <vector>
#include <string>

class SessionInfo {
  public:
    SessionInfo(uint64_t id) : _id(id) {}
    SessionInfo(uint64_t id, const std::vector<std::string>& images,
                const std::vector<TransformationID>& op_info);

    uint64_t get_id_info() const;

    const std::vector<std::string>& get_images_info() const;

    const std::vector<TransformationID>& get_transformations_info() const;

    void add_transformation(TransformationID id);

    void remove_last_transformation_info();

	void remove_transformations_info();

  private:
    uint64_t _id;
    std::vector<std::string> _images;
    std::vector<TransformationID> _trans_info;
};
