#pragma once
#include <Eigen/Eigen>
#include <assert.h>
#include <map>
#include <vector>
#include <geometry_msgs/Pose.h>
#include "lcm_gen/Pose_t.hpp"
#include <tf/transform_broadcaster.h>

using namespace Eigen;

namespace Eigen {
    typedef Matrix<double, 6, 6> Matrix6d;
    typedef Matrix<double, 6, 1> Vector6d;
};

inline Vector3d quat2eulers(const Quaterniond &quat) {
    Vector3d rpy;
    rpy.x() = atan2(2 * (quat.w() * quat.x() + quat.y() * quat.z()),
                    1 - 2 * (quat.x() * quat.x() + quat.y() * quat.y()));
    rpy.y() = asin(2 * (quat.w() * quat.y() - quat.z() * quat.x()));
    rpy.z() = atan2(2 * (quat.w() * quat.z() + quat.x() * quat.y()),
                    1 - 2 * (quat.y() * quat.y() + quat.z() * quat.z()));
    return rpy;
}

//rpy2quat
inline Quaterniond eulers2quat(const Vector3d eul) {
    return Eigen::AngleAxisd(eul.z(), Eigen::Vector3d::UnitZ())
        * Eigen::AngleAxisd(eul.y(), Eigen::Vector3d::UnitY())
        * Eigen::AngleAxisd(eul.x(), Eigen::Vector3d::UnitX());
}


inline Matrix3d skewSymmetric(Vector3d w) {
  Matrix3d ret;
  ret << 0.0, -w.z(), +w.y(), +w.z(), 0.0, -w.x(), -w.y(), +w.x(), 0.0;
  return ret;
}


inline Vector3d Logmap(const Quaterniond& q) {
    using std::acos;
    using std::sqrt;

    // define these compile time constants to avoid std::abs:
    static const double twoPi = 2.0 * M_PI, NearlyOne = 1.0 - 1e-10,
    NearlyNegativeOne = -1.0 + 1e-10;

    Vector3d omega;

    const double qw = q.w();
    // See Quaternion-Logmap.nb in doc for Taylor expansions
    if (qw > NearlyOne) {
      // Taylor expansion of (angle / s) at 1
      // (2 + 2 * (1-qw) / 3) * q.vec();
      omega = ( 8. / 3. - 2. / 3. * qw) * q.vec();
    } else if (qw < NearlyNegativeOne) {
      // Taylor expansion of (angle / s) at -1
      // (-2 - 2 * (1 + qw) / 3) * q.vec();
      omega = (-8. / 3. - 2. / 3. * qw) * q.vec();
    } else {
      // Normal, away from zero case
      double angle = 2 * acos(qw), s = sqrt(1 - qw * qw);
      // Important:  convert to [-pi,pi] to keep error continuous
      if (angle > M_PI)
      angle -= twoPi;
      else if (angle < -M_PI)
      angle += twoPi;
      omega = (angle / s) * q.vec();
    }
    return omega;
  }

template <typename T>
T wrap_angle(T angle) {
    while (angle > M_PI) {
        angle = angle - 2 * M_PI;
    }

    while (angle < -M_PI) {
        angle = angle + 2 * M_PI;
    }
    return angle;
}
namespace Swarm {

template <typename Derived>
Quaternion<Derived> averageQuaterions(std::vector<Quaternion<Derived>> quats) {
    Matrix<Derived, 4, 4> M = Matrix4d::Zero();
    if (quats.size() == 1) {
        return quats[0];
    }
    for (auto & q : quats) {
       Vector4d v = q.coeffs(); 
       M += v*v.transpose();
    }
    SelfAdjointEigenSolver<Matrix<Derived, 4, 4>> solver;
    solver.compute(M);
    Matrix<Derived, 4, 1> eigenvector = solver.eigenvectors().rightCols(1);
    Quaternion<Derived> q(eigenvector(3), eigenvector(0), eigenvector(1), eigenvector(2));
    return q;
}

template <typename Derived>
Eigen::Quaternion<typename Derived::Scalar> deltaQ(const Eigen::MatrixBase<Derived> &theta)
{
    typedef typename Derived::Scalar Scalar_t;

    Eigen::Quaternion<Scalar_t> dq;
    Eigen::Matrix<Scalar_t, 3, 1> half_theta = theta;
    half_theta /= static_cast<Scalar_t>(2.0);
    dq.w() = static_cast<Scalar_t>(1.0);
    dq.x() = half_theta.x();
    dq.y() = half_theta.y();
    dq.z() = half_theta.z();
    return dq;
}

class Pose {

    Vector3d position = Vector3d(0, 0, 0);
    Quaterniond attitude = Quaterniond(1, 0, 0, 0);
    Quaterniond attitude_yaw_only = Quaterniond(1, 0, 0, 0);
    double _yaw = 0;

public:

    Pose copy() const {
        Vector3d pos = position;
        Quaterniond att = attitude;
        return Pose(pos, att);
    }

    void rotate(double angle, Vector3d axis) {
        // attitude = AngleAxisd(angle, axis) * attitude;
        // rotate at local frame
        attitude = attitude * AngleAxisd(angle, axis);
        attitude.normalize();
        update_yaw();
    }

    void update_yaw() {
        _yaw = wrap_angle(this->rpy().z());
        attitude_yaw_only = (Quaterniond)AngleAxisd(_yaw, Vector3d::UnitZ());
    }

    static Pose Identity() {
        return Pose();
    }

    template <typename T>
    void to_vector(T ret[]) const {
        ret[3] = T(attitude.x());
        ret[4] = T(attitude.y());
        ret[5] = T(attitude.z());
        ret[6] = T(attitude.w());

        ret[0] = T(position.x());
        ret[1] = T(position.y());
        ret[2] = T(position.z());
    }

    template <typename T>
    void from_vector(const T v[], bool xyzyaw = false) {
        if (xyzyaw) {
            this->attitude = AngleAxisd(v[3], Vector3d::UnitZ());
        } else {
            attitude.x() = v[3];
            attitude.y() = v[4];
            attitude.z() = v[5];
            attitude.w() = v[6];
        }
        position.x() = v[0];
        position.y() = v[1];
        position.z() = v[2];
        attitude.normalize();
        update_yaw();
    }

    template <typename T>
    void to_vector_xyzyaw(T ret[]) const {
        ret[0] = T(position.x());
        ret[1] = T(position.y());
        ret[2] = T(position.z());
        ret[3] = T(_yaw);
    }

    template <typename T>
    void to_vector_xy(T ret[]) const {
        ret[0] = T(position.x());
        ret[1] = T(position.y());
    }

    Vector3d apply_pose_to(Vector3d point) const {
        return attitude * point + position;
    }

    Vector3d apply_inv_pose_to(Vector3d point) const {
        return attitude.inverse() * (point - position);
    }


    Vector3d rpy() const {
        return quat2eulers(attitude);
    }

    Pose(Isometry3d trans) {
        position = trans.translation();
        attitude = trans.rotation();

        update_yaw();
    }


    Pose(geometry_msgs::Point pos, double yaw) {
        this->attitude = AngleAxisd(yaw, Vector3d::UnitZ());
        position.x() = pos.x;
        position.y() = pos.y;
        position.z() = pos.z;
        attitude.normalize();

        update_yaw();
    }

    Pose(geometry_msgs::Point pos, geometry_msgs::Quaternion orientation) {
        position.x() = pos.x;
        position.y() = pos.y;
        position.z() = pos.z;

        attitude.w() = orientation.w;
        attitude.x() = orientation.x;
        attitude.y() = orientation.y;
        attitude.z() = orientation.z;
        attitude.normalize();

        update_yaw();
    }

    Pose(Vector3d pos, double yaw) {
        this->attitude = AngleAxisd(yaw, Vector3d::UnitZ());
        position = pos;
        attitude.normalize();

        update_yaw();
    }

    Pose(Vector3d pos, Quaterniond att) {
        this->attitude = att;
        position = pos;
        attitude.normalize();

        update_yaw();
    }

    Pose(const geometry_msgs::Pose &p) {
        attitude.w() = p.orientation.w;
        attitude.x() = p.orientation.x;
        attitude.y() = p.orientation.y;
        attitude.z() = p.orientation.z;

        position.x() = p.position.x;
        position.y() = p.position.y;
        position.z() = p.position.z;
        update_yaw();
    }

    Pose(const Matrix3d & R, const Vector3d & T) {
        attitude = R;
        attitude.normalize();
        position = T;
        update_yaw();
    }


    Pose(const Quaterniond & Q, const Vector3d &T) {
        attitude = Q;
        attitude.normalize();
        position = T;
        update_yaw();
    }

    Pose(const double v[], bool xyzyaw = false) {
        if (xyzyaw) {
            this->attitude = AngleAxisd(v[3], Vector3d::UnitZ());
        } else {
            attitude.x() = v[3];
            attitude.y() = v[4];
            attitude.z() = v[5];
            attitude.w() = v[6];
        }
        position.x() = v[0];
        position.y() = v[1];
        position.z() = v[2];
        attitude.normalize();
        update_yaw();
    }

    Pose(const VectorXd & state) {
        if (state.size() == 4 ) {
            this->from_vector(state.data(), true);
        } else if (state.size() == 7) {
            this->from_vector(state.data(), false);
        } else {
            assert(false && "Pose::Pose(VectorXd) size error");
        }
    }

    Pose(const Pose_t & pose_t) {
        attitude.x() = pose_t.orientation[0];
        attitude.y() = pose_t.orientation[1];
        attitude.z() = pose_t.orientation[2];
        attitude.w() = pose_t.orientation[3];

        position.x() = pose_t.position[0];
        position.y() = pose_t.position[1];
        position.z() = pose_t.position[2];
        update_yaw();
    }


    Isometry3d toIsometry() const {
        Isometry3d a = Translation3d(position) * attitude;
        return a;
    }

    Matrix4d toMatrix() const {
        Matrix4d a = Matrix4d::Identity();
        a.block<3,3>(0,0) = attitude.toRotationMatrix();
        a.block<3,1>(0,3) = position;
        return a;
    }

    geometry_msgs::Pose toROS() const {
        geometry_msgs::Pose pose;
        pose.orientation.w = attitude.w();
        pose.orientation.x = attitude.x();
        pose.orientation.y = attitude.y();
        pose.orientation.z = attitude.z();
        pose.position.x = position.x();
        pose.position.y = position.y();
        pose.position.z = position.z();
        return pose;
    }

    tf::Transform toTF() const {
        tf::Transform tf;
        tf.setOrigin(tf::Vector3(position.x(), position.y(), position.z()));
        tf.setRotation(tf::Quaternion(attitude.x(), attitude.y(), attitude.z(), attitude.w()));
        return tf;
    }

    Pose_t toLCM() const {
        Pose_t pose;
        pose.position[0] = position.x();
        pose.position[1] = position.y();
        pose.position[2] = position.z();
        pose.orientation[0] = attitude.x();
        pose.orientation[1] = attitude.y();
        pose.orientation[2] = attitude.z();
        pose.orientation[3] = attitude.w();
        return pose;
    }

    Swarm::Pose inverse() const {
        return Swarm::Pose(attitude.inverse(), -(attitude.inverse() * position));
    }

    static double MahalanobisDistance(const Pose &a, const Pose &b, Eigen::Matrix6d cov) {
        return DeltaPose(a, b).MahalanobisNorm(cov);
    }

    double MahalanobisNorm(Eigen::Matrix6d cov_mat) const {
        auto _logmap = this->log_map();
        auto ret = _logmap.transpose() * cov_mat.inverse() * _logmap;
        return std::sqrt(ret(0, 0));
    }

    inline double & yaw() {
        return _yaw;
    }
    
    inline double yaw() const {
        return _yaw;
    }
    
    void update_attitude() {
        _yaw = wrap_angle(_yaw);
        attitude = attitude_yaw_only = (Quaterniond)AngleAxisd(_yaw, Vector3d::UnitZ());
    }

    std::string toStr(bool for_file=false) const {
        auto _rpy = rpy();
        char _ret[256] = {0};
        if (for_file) {
            sprintf(_ret, "%3.6f %3.6f %3.6f %3.6f %3.6f %3.6f %3.6f",
               position.x(), position.y(), position.z(),
               attitude.w(), attitude.x(), attitude.y(), attitude.z());

        } else {
        sprintf(_ret, "T [%+3.3f,%+3.3f,%+3.3f] YPR [%+3.1f,%+3.1f,%+3.1f]",
               position.x(), position.y(), position.z(),
               _rpy.z() * 57.3,
               _rpy.y() * 57.3,
               _rpy.x() * 57.3);
        }
        return std::string(_ret);
    }

    void print() const {
        std::cout << toStr();
    }

    Vector3d pos() const {
        return position;
    }

    Vector3d & pos() {
        return position;
    }

    Quaterniond att_yaw_only() const {
        return attitude_yaw_only;
    }

    Quaterniond att() const {
        return attitude;
    }

    Quaterniond & att() {
        return attitude;
    }

    Matrix3d R() const {
        return attitude.toRotationMatrix();
    }

    void set_att(Quaterniond att) {
        attitude = att;
        update_yaw();
    }

    void set_pos(Vector3d pos) {
        position = pos;
    }

    void set_yaw_only() {
        update_yaw();
        attitude = attitude_yaw_only;
    }

    Vector6d log_map() const {
        //T Q
        //Modified from https://github.com/borglab/gtsam/blob/develop/gtsam/geometry/Pose3.cpp
        const Vector3d w = Logmap(att());
        const Vector3d T = pos();
        const double t = w.norm();
        if (t < 1e-10) {
            Vector6d ret;
            ret.block<3, 1>(0, 0) = T;
            ret.block<3, 1>(3, 0) = w;
            return ret;
        } else {
            const Matrix3d W = skewSymmetric(w / t);
            // Formula from Agrawal06iros, equation (14)
            // simplified with Mathematica, and multiplying in T to avoid matrix math
            const double Tan = tan(0.5 * t);
            const Vector3d WT = W * T;
            const Vector3d u = T - (0.5 * t) * WT + (1 - t / (2. * Tan)) * (W * WT);
            Vector6d ret;
            ret.block<3, 1>(0, 0) = u;
            ret.block<3, 1>(3, 0) = w;
            return ret;
        }
    }

    Vector6d tangentSpace() const {
        Vector6d ret;
        ret.segment<3>(0) = pos();
        if (attitude.w() > 0) {
            ret.segment<3>(3)  =  2 * attitude.vec();
        } else {
            ret.segment<3>(3)  = - 2 * attitude.vec();
        }
        return ret;
    }

    static Pose fromTangentSpace(const Vector6d &v) {
        Pose ret;
        ret.position = v.segment<3>(0);
        ret.attitude = deltaQ(v.segment<3>(3));
        ret.attitude.normalize();
        ret.update_yaw();
        return ret;
    }

    Pose() {}
    
    friend Pose operator*(Pose a, Pose b) {
        Pose p;
        // p.position = a.attitude*(b.position+ a.position);
        p.position = a.attitude * b.position + a.position;
        p.attitude = a.attitude * b.attitude;
        p.update_yaw();

        //        printf("Res manual");
        //        p.print();
        //
        //        printf("Res eigen");
        //        p.print();
        return p;
    }

    friend Vector3d operator*(Pose a, Vector3d point) {
        return a.attitude * point + a.position;
    }

    //A^-1B
    static Pose DeltaPose(const Pose &a, const Pose &b, bool use_yaw_only = false) {
        //Check this!!!
        Pose p;
        if (!use_yaw_only) {
            p.position = a.attitude.inverse() * (b.position - a.position);
            p.attitude = a.attitude.inverse() * b.attitude;
            p.update_yaw();
        } else {
            /*
            dpose[3] = wrap_angle(poseb[3] - posea[3]);
            T tmp[3];
            tmp[0] = poseb[0] - posea[0];
            tmp[1] = poseb[1] - posea[1];
            tmp[2] = poseb[2] - posea[2];

            YawRotatePoint(-posea[3], tmp, dpose);*/
            double dyaw = wrap_angle(b.yaw() - a.yaw());
            Vector3d dp = b.position - a.position;
            p.attitude = (Quaterniond)AngleAxisd(dyaw, Vector3d::UnitZ());

            p._yaw = dyaw;
            p.attitude_yaw_only = p.attitude;

            p.position.x() = cos(-a.yaw()) * dp.x() - sin(-a.yaw()) * dp.y();
            p.position.y() = sin(-a.yaw()) * dp.x() + cos(-a.yaw()) * dp.y();
            p.position.z() = dp.z();

            // p.position = AngleAxisd(-a.yaw(), Vector3d::UnitZ()) * dp;
        }

        return p;
    }
    static Pose averagePoses(const std::vector<Pose> & poses) {
        Vector3d sum_pos = Vector3d::Zero();
        std::vector<Quaterniond> quaternions;
        for (auto & pose : poses) {
            sum_pos += pose.position;
            quaternions.emplace_back(pose.attitude);
        }
        return Pose(sum_pos / poses.size(), averageQuaterions(quaternions));
    }
};

inline std::istream& operator>>(std::istream& input, Pose & pose) {
  input >> pose.pos().x() >> pose.pos().y() >> pose.pos().z() >> pose.att().x() >> pose.att().y() >>
        pose.att().z() >> pose.att().w();
  pose.att().normalize();
  pose.update_yaw();
  return input;
}


inline std::ostream& operator<<(std::ostream& output, Pose & pose) {
    output << pose.toStr();
    return output;
}
// typedef std::pair<TsType, Pose> PoseStamped;
// typedef std::vector<PoseStamped> Path;

template <typename Vec, typename Mat>
inline double computeSquaredMahalanobisDistance(Vec logmap, Mat cov_mat) {
    auto ret = logmap.transpose() * cov_mat.inverse() * logmap;
    return std::sqrt(ret(0, 0));
}

} // namespace Swarm