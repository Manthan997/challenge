#define _USE_MATH_DEFINES

#include "bot.h"

Bot::Bot(const std::string& name, const Pose& pose, float dist)
    : name(name), pose(pose), distance(dist) {}

Bot Bot::with_default_pose(const std::string& name) {
    return Bot(name, { Dir::A, 0.0, 0.0 }, 0.0);
}

Bot Bot::with_custom_pose(const std::string& name, const Pose& pose, float dist) {
    return Bot(name, pose, dist);
}

void Bot::greet() const {
    std::cout << "Hello! I am " << name << "." << std::endl;
}

Pose Bot::current_position() const {
    std::cout << "Current position of " << name << " : (" << pose.x_cord << ", " << pose.y_cord << ") facing " << static_cast<int>(pose.Facing) << std::endl;
    return pose;
}

void Bot::walk(float distance) {
    if (distance <= 0) {
        throw std::invalid_argument("Distance must be a positive value");
    }

    float new_x = pose.x_cord + distance * std::sin(static_cast<int>(pose.Facing) * M_PI / 180.0);
    if (-X_LIM <= new_x && new_x <= X_LIM) {
        pose.x_cord = static_cast<int>(new_x);
    } else {
        throw std::out_of_range("Bot is out of the playground limits");
    }

    float new_y = pose.y_cord + distance * std::cos(static_cast<int>(pose.Facing) * M_PI / 180.0);
    if (-Y_LIM <= new_y && new_y <= Y_LIM) {
        pose.y_cord = static_cast<int>(new_y);
    } else {
        throw std::out_of_range("Bot is out of the playground limits");
    }

    this->distance += distance;
    rec_cmd("walk " + std::to_string(distance));
}

void Bot::turn(Dir direction) {
    pose.Facing = direction;
    rec_cmd("turn " + std::to_string(static_cast<int>(direction)));
}

std::pair<Pose, float> Bot::predict(const Pose& start_pos, const std::vector<std::variant<Dir, float>>& move_commands, float dist) {
    Bot t_bot = Bot::with_custom_pose("TEMP", start_pos, dist);

    for (const auto& command : move_commands) {
        if (std::holds_alternative<float>(command)) {
            t_bot.walk(std::get<float>(command));
        } else if (std::holds_alternative<Dir>(command)) {
            t_bot.turn(std::get<Dir>(command));
        } else {
            throw std::invalid_argument("Invalid command");
        }
    }

    return { t_bot.current_position(), t_bot.total_distance() };
}

float Bot::total_distance() const {
    std::cout << "Total distance covered by " << name << ": " << distance << std::endl;
    return distance;
}

std::vector<std::string> Bot::dump_commands() const {
    std::cout << "Commands executed by " << name << ": ";
    for (const auto& cmd : command_log) {
        std::cout << cmd << " ";
    }
    std::cout << std::endl;
    return command_log;
}

void Bot::rec_cmd(const std::string& command) {
    command_log.push_back(command);
}

// int main() {
//     Bot bot = Bot::with_default_pose("Bandu_test-case");
//     bot.greet();
//     bot.current_position();
//     bot.walk(10.43);
//     bot.walk(15);
//     bot.turn(Dir::B);
//     bot.walk(10);
//     bot.current_position();

//     Pose start_pos = { Dir::A, 10, 3 };
//     std::vector<std::variant<Dir, float>> commands = { Dir::A, 10.0f, Dir::C, 12.4f};
//     bot.predict(start_pos, commands);

//     bot.dump_commands();

//     return 0;
// }