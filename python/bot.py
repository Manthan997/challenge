from dataclasses import dataclass
from enum import Enum
import math

# Constants
X_LIM = 100
Y_LIM = 100

'''
ENUM FOR DIRECTION. REFER THE PROBLEM STATEMENT DOC FOR MORE INFO
'''
class Dir(Enum):
    A = math.radians(0)
    B = math.radians(60)
    C = math.radians(120)
    D = math.radians(180)
    E = math.radians(240)
    F = math.radians(300)

'''
dataclass (struct) for storing the position of the bot
'''
@dataclass
class Pose:
    Facing: Dir
    x_cord: int
    y_cord: int

# # Create an instance
# person = Person(name='Alice', age=30)


'''
TODO: In Python, you can use type hints to indicate the expected type of a parameter, but type hints themselves do not enforce type checking at runtime. To enforce the type check, you still need to use isinstance or another method to validate the type.
sometimes, int and float can be interchanged
'''

class Bot:
    def __init__(self, name, pose: Pose, dist: float) -> None:
        
        self.__name = name
        self.__pose = pose 
        self.__distance = dist
        self.__command_log = []

    @classmethod
    def with_default_pose(cls, name):
        # bot is at position (0,0) facing direction A at spawn
        return cls(name, Pose(Dir.A, 0, 0), 0.0) 

    @classmethod
    def with_custom_pose(cls, name, pose, dist):
        return cls(name, pose, dist)   

    def greet(self):
        # greet the user
        print(f"Hello! I am {self.__name}.")

    # list of required functions
    ''' current position
        move commands[turn and walk] walk has a distance as input in float only positive floats allowed
        predict(input: start pos, move commands)-> final position and distance covered
        function to read the total distance covered by the bot
        func to record and dump the commands
    '''
    def current_position(self):
        # print the current position of the bot
        print(f"Current position of {self.__name} : ({self.__pose.x_cord}, {self.__pose.y_cord}) facing {self.__pose.Facing.name}")
        return self.__pose

    def __rec_cmd(self, command):
        self.__command_log.append(str(command))

    def walk(self, distance: float):

        # Check if the distance is positive
        if distance <= 0:
            raise ValueError("Distance must be a positive value")
        
        # update the position of the bot based on the distance AND direction it is facing
        # another check for bot leaving the playground limits
        new_x = int(self.__pose.x_cord + distance * math.sin(self.__pose.Facing.value))
        if -X_LIM <= new_x <= X_LIM:
            self.__pose.x_cord = new_x
        else:
            raise ValueError("Bot is out of the playground limits")
        
        new_y = int(self.__pose.y_cord + distance * math.cos(self.__pose.Facing.value))
        if -Y_LIM <= new_y <= Y_LIM:
            self.__pose.y_cord = new_y
        else:
            raise ValueError("Bot is out of the playground limits")
        
        # update the distance covered by the bot
        self.__distance += distance

        # record the command
        self.__rec_cmd("walk " + str(distance))

        return self.__pose
    
    def turn(self, direction: Dir):
        # update the direction the bot is facing
        self.__pose.Facing = direction

        # record the command
        self.__rec_cmd("turn " + direction.name)

        return self.__pose

    def predict(self, start_pos: Pose, move_commands: list, dist:float =0.0):
        # CREATE A TEMP bot based on the start position
        t_bot = Bot.with_custom_pose("TEMP", start_pos, dist)
        # follow the list of commands
        for i in range(len(move_commands)):
            # check if the command is to walk
            if isinstance(move_commands[i], (float, int)):
                t_bot.walk(move_commands[i])
            # check if the command is to turn
            elif isinstance(move_commands[i], Dir):
                t_bot.turn(move_commands[i])
            else:
                raise ValueError("Invalid command")
        # return the TEMP position of the bot and the distance covered
        return [ t_bot.current_position(), t_bot.total_distance() ]
    
    def total_distance(self):
        print(f"Total distance covered by {self.__name}: {self.__distance}")
        return self.__distance
    
    def dump_commands(self):
        # print the list of commands executed by the bot
        print(f"Commands executed by {self.__name}: {self.__command_log}")
        return self.__command_log

# main code
if __name__ == "__main__":
    bot = Bot.with_default_pose("Bandu_test-case")
    bot.greet()
    bot.current_position()
    bot.walk(10.43)
    bot.walk(15)
    bot.turn(Dir.B)
    bot.walk(10)
    bot.current_position()

    bot.predict(Pose(Dir.A, 10, 3), [Dir.A, 10, Dir.C, 12.4, Dir.F, 5.6, 10])

    bot.dump_commands()
