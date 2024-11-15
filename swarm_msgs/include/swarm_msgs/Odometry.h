#pragma once
#include <swarm_msgs/Pose.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>
#include "lcm_gen/Odometry_t.hpp"
#include <swarm_msgs/swarm_lcm_converter.hpp>

namespace Swarm {
class Odometry {
protected:
    Vector3d velocity;
    Vector3d angular_velocity;
    Pose pose_;
public:
    double stamp;
    Odometry():
        stamp(0.0), velocity(0., 0., 0.), angular_velocity(0., 0., 0.)
    {}

    Odometry(double t):
        stamp(t), velocity(0., 0., 0.), angular_velocity(0., 0., 0.)
    {}

    Odometry(const nav_msgs::Odometry & odom):
        stamp(odom.header.stamp.toSec()),
        pose_(odom.pose.pose),
        velocity(odom.twist.twist.linear.x, odom.twist.twist.linear.y, odom.twist.twist.linear.z),
        angular_velocity(odom.twist.twist.angular.x, odom.twist.twist.angular.y, odom.twist.twist.angular.z)
    {}

    Odometry(double t, const Swarm::Pose & _pose, const Vector3d & vel, const Vector3d & ang_vel):
        stamp(t), pose_(_pose), velocity(vel), angular_velocity(ang_vel)
    {}
    
    Odometry(double t, const Swarm::Pose & _pose, const Vector3d & vel):
        stamp(t), pose_(_pose), velocity(vel), angular_velocity(0., 0., 0.)
    {}

    Odometry(double t, const Swarm::Pose & _pose):
        stamp(t), pose_(_pose), velocity(0., 0., 0.), angular_velocity(0., 0., 0.)
    {}

    Odometry(const Swarm::Pose & _pose, const Vector3d & vel):
        stamp(0.), pose_(_pose), velocity(vel), angular_velocity(0., 0., 0.)
    {}

    Odometry(const Odometry_t & odom):
        stamp(toROSTime(odom.stamp).toSec()),
        pose_(odom.pose),
        velocity(odom.velocity[0], odom.velocity[1], odom.velocity[2]),
        angular_velocity(odom.angular_velocity[0], odom.angular_velocity[1], odom.angular_velocity[2])
    {}

    std::string toStr() const {
        char buf[256] = {0};
        sprintf(buf, "Pose %s Vel %.2f %.2f %.2f", pose_.toStr().c_str(), velocity.x(), velocity.y(), velocity.z());
        return std::string(buf);
    }

    nav_msgs::Odometry toRos() const {
        nav_msgs::Odometry odom;
        odom.header.stamp = ros::Time(stamp);
        odom.header.frame_id = "world";
        odom.pose.pose = pose_.toROS();
        odom.twist.twist.linear.x = velocity.x();
        odom.twist.twist.linear.y = velocity.y();
        odom.twist.twist.linear.z = velocity.z();

        odom.twist.twist.angular.x = angular_velocity.x();
        odom.twist.twist.angular.y = angular_velocity.y();
        odom.twist.twist.angular.z = angular_velocity.z();
        return odom;
    }

    tf::Transform toTF() const {
        tf::Transform tf;
        tf.setOrigin(tf::Vector3(pos().x(), pos().y(), pos().z()));
        tf.setRotation(tf::Quaternion(att().x(), att().y(), att().z(), att().w()));
        return tf;
    }

    Odometry_t toLCM() const {
        Odometry_t odom;
        ros::Time t(stamp);
        odom.stamp = toLCMTime(t);
        odom.pose = pose_.toLCM();
        odom.velocity[0] = velocity.x();
        odom.velocity[1] = velocity.y();
        odom.velocity[2] = velocity.z();
        odom.angular_velocity[0] = angular_velocity.x();
        odom.angular_velocity[1] = angular_velocity.y();
        odom.angular_velocity[2] = angular_velocity.z();
        return odom;
    }

    Quaterniond & att() {
        return pose_.att();
    }

    Vector3d & pos() {
        return pose_.pos();
    }

    Vector3d & vel() {
        return velocity;
    }

    Vector3d & ang_vel() {
        return angular_velocity;
    }

    Swarm::Pose & pose () {
        return pose_;
    }

    Quaterniond att() const {
        return pose_.att();
    }

    Vector3d pos() const {
        return pose_.pos();
    }

    Matrix3d R() const {
        return pose_.R();
    }

    Vector3d vel() const {
        return velocity;
    }

    Vector3d ang_vel() const {
        return angular_velocity;
    }

    Swarm::Pose pose () const {
        return pose_;
    }

    Swarm::Odometry copy() const {
        Pose pose = pose_.copy();
        Vector3d vel = velocity;
        Vector3d ang_vel = angular_velocity;
        return Odometry(stamp, pose, vel, ang_vel);
    }

    void rotate(double angle, Vector3d axis) {
        pose_.rotate(angle, axis);
        velocity = AngleAxisd(angle, axis) * velocity;
        angular_velocity = AngleAxisd(angle, axis) * angular_velocity;
    }

    void moveByPose(const Pose & delta_pose) {
        pose_ = delta_pose * pose_;
        velocity = delta_pose.att() * velocity;
        angular_velocity = delta_pose.att() * angular_velocity;
    }

    void addTransByPose(const Pose & delta_pose) {
        pose_ = pose_ * delta_pose;
    }

    friend Odometry operator*(Pose a, Odometry odom) {
        Odometry ret;
        ret.stamp = odom.stamp;
        ret.pose_ = a * odom.pose_;
        ret.velocity = a.att() * odom.velocity;
        ret.angular_velocity = a.att() * odom.angular_velocity;
        return ret;
    }
};
}