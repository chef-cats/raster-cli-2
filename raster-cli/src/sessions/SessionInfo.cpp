#include <sessions/SessionInfo.hpp>

SessionInfo::SessionInfo(uint64_t id, const std::vector<std::string>& images,
                         const std::vector<TransformationID>& op_info)
    : _id(id), _images(images), _trans_info(op_info) {}

uint64_t SessionInfo::get_id_info() const {
    return _id;
}

const std::vector<std::string>& SessionInfo::get_images_info() const {
    return _images;
}

const std::vector<TransformationID>& SessionInfo::get_transformations_info() const {
    return _trans_info;
}

void SessionInfo::add_transformation(TransformationID id) {
    _trans_info.emplace_back(id);
}

void SessionInfo::remove_last_transformation_info() {
    _trans_info.pop_back();
}

void SessionInfo::remove_transformations_info() {
    _trans_info.clear();
}
