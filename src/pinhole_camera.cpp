#include "pinhole_camera.hpp"
#include <iostream>

PinholeCamera::PinholeCamera(Eigen::Matrix3d intrinsic_matrix, const cv::Size& image_size)
    : intrinsic_matrix_(std::move(intrinsic_matrix)),
      image_size_(image_size)
{}

std::optional<cv::Point2i> PinholeCamera::projectToPixel(const Eigen::Vector3d& point) const
{
    if (point.z() <= 0)
    {
        return std::nullopt;
    }
    Eigen::Vector3d pixel_homogeneous = intrinsic_matrix_ * point;
    const double pixel_u = pixel_homogeneous.x() / pixel_homogeneous.z();
    const double pixel_v = pixel_homogeneous.y() / pixel_homogeneous.z();

    if (pixel_u < 0 || pixel_u >= image_size_.width || pixel_v < 0 || pixel_v >= image_size_.height)
    {
        return std::nullopt;
    }
    return cv::Point2i(static_cast<int>(pixel_u), static_cast<int>(pixel_v));
}

std::optional<Eigen::Vector3d> PinholeCamera::backProjectToGround(const cv::Point2i& image_point, double camera_distance) const
{
    // Check if image point is inside the image
    if (!image_point.inside(cv::Rect(0, 0, image_size_.width, image_size_.height)))
    {
        return std::nullopt;
    }
    Eigen::Vector3d point_3d;
    point_3d = intrinsic_matrix_.inverse() * Eigen::Vector3d(static_cast<double>(image_point.x), static_cast<double>(image_point.y), 1.0);
    point_3d *= camera_distance;
    return point_3d;
}