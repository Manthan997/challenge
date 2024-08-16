from bot import Bot, Pose, Dir

bot = Bot.with_default_pose("Bandu")

bot.greet()
bot.current_position()
bot.walk(10.43)
bot.turn(Dir.B)
bot.walk(10)
bot.current_position()
bot.predict(Pose(Dir.A, 0, 0), [Dir.A, 10, Dir.B, 10])
bot.dump_commands()