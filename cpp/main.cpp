#include <iostream>
#include <vector>
#include <variant>
#include "bot.h"

int main() {
    Bot bot = Bot::with_default_pose("Bandu_test-case");
    bot.greet();
    bot.current_position();
    bot.walk(10.43);
    bot.walk(15);
    bot.turn(Dir::B);
    bot.walk(10);
    bot.current_position();

    Pose start_pos = { Dir::A, 0, 0 };
    std::vector<std::variant<Dir, float>> commands = { Dir::A, 10.0f, Dir::B, 10.0f, Dir::C, 10.0f, Dir::D, 10.0f, Dir::E, 10.0f, Dir::F, 10.0f };
    bot.predict(start_pos, commands);

    bot.dump_commands();

    return 0;
}