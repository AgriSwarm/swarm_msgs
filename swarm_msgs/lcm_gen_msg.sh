#!/usr/bin/env bash
# lcm-gen msg/ImageDescriptor_t.lcm  -x --cpp-hpath  ./include/swarm_msgs/lcm_gen
# lcm-gen msg/ImageDescriptor_t.lcm  -p --ppath ./scripts/

# C++ヘッダーファイルの生成
lcm-gen msg/indexed_odometry.lcm -x --cpp-hpath ./include/swarm_msgs/lcm_gen
lcm-gen msg/command_tol.lcm -x --cpp-hpath ./include/swarm_msgs/lcm_gen
lcm-gen msg/position_command.lcm -x --cpp-hpath ./include/swarm_msgs/lcm_gen
lcm-gen msg/goal_set.lcm -x --cpp-hpath ./include/swarm_msgs/lcm_gen
lcm-gen msg/odometry.lcm -x --cpp-hpath ./include/swarm_msgs/lcm_gen

# Pythonバインディングの生成（必要な場合）
lcm-gen msg/indexed_odometry.lcm -p --ppath ./scripts/
lcm-gen msg/command_tol.lcm -p --ppath ./scripts/
lcm-gen msg/position_command.lcm -p --ppath ./scripts/
lcm-gen msg/goal_set.lcm -p --ppath ./scripts/
lcm-gen msg/odometry.lcm -p --ppath ./scripts/