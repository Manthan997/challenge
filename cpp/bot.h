#ifndef BOT_H
#define BOT_H

#include <iostream>
#include <cmath>
#include <vector>
#include <variant>
#include <string>
#include <stdexcept>

const int X_LIM = 100;
const int Y_LIM = 100;

enum class Dir {
    A = 0,
    B = 60,
    C = 120,
    D = 180,
    E = 240,
    F = 300
};

struct Pose {
    Dir Facing;
    float x_cord;
    float y_cord;
};

class Bot {
public:
    Bot(const std::string& name, const Pose& pose, float dist);

    static Bot with_default_pose(const std::string& name);
    static Bot with_custom_pose(const std::string& name, const Pose& pose, float dist);

    void greet() const;
    Pose current_position() ;
    void walk(float distance);
    void turn(Dir direction);
    std::pair<Pose, float> predict(const Pose& start_pos, const std::vector<std::variant<Dir, float>>& move_commands, float dist = 0.0);
    float total_distance() const;
    std::vector<std::string> dump_commands() const;

private:
    std::string name;
    Pose pose;
    float distance;
    std::vector<std::string> command_log;
    std::string dirToString(Dir dir);
    void rec_cmd(const std::string& command);
};

#endif // BOT_H