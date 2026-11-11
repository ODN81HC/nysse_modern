#pragma once

#include <Eigen/Dense>
#include <opencv2/core.hpp>
#include <optional>
#include "location.hpp"

inline Eigen::Vector3d convertTo3d(const Interface::Location& loc)
{
    return {static_cast<double>(loc.giveX()), static_cast<double>(loc.giveY()), 0.0};
}

class PinholeCamera
{
public:
    PinholeCamera() = default;
    PinholeCamera(Eigen::Matrix3d intrinsic_matrix, const cv::Size& image_size);
    [[nodiscard]] std::optional<cv::Point2i> projectToPixel(const Eigen::Vector3d& point) const;
    [[nodiscard]] std::optional<Eigen::Vector3d> backProjectToGround(const cv::Point2i& image_point, double camera_distance) const;

private:
    Eigen::Matrix3d intrinsic_matrix_;
    cv::Size image_size_;
};