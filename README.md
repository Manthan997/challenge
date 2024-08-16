*“Greetings fellow human!*
*I'm Mr. Bandu the bot. And I request your help to guide me back to my home”*

Refer doc: [click here!](https://docs.google.com/document/d/1aB7zA10enCwJgz3QGojBsun_WN2dECSGKZTJ4mmg6M0/edit?usp=sharing)

VHDL problem statement is here: [flyyy to google docs](https://docs.google.com/document/d/1cF8WSD8Pkb7U2rS1ud0kPp2D9WSB6zt1FlkkjZlO0jM/edit?usp=sharing)

### Task:
Bandu always spawns at (0,0) facing North. For every instance, you have a target location that bandu needs to reach. You can guide bandu using commands walk(<dist>) and turn(<Dir>) but the problem is bandu’s sub-system responsible for turning is broken and can only perform turns in multiples of 60 degrees. Walk command accepts a float parameter and the bot walks in the direction it is facing for the specified number Of units. Turn command accepts a single parameter that is an enum Dir. 


Possible values of <Dir> are A, B, C, D, E and F where A points straight north, B points 60 degrees from North clockwise, C being 120 degrees from North or pointing approximately South-east, D points south and so on.
Though there is no obstacle on the field, the field has boundaries from -100 to 100 units in both X and Y axis. Once the bot leaves these, he's disconnected from the system.
Your solution is expected to be conservative regarding the number Of steps and the total distance walked by the bot.
The lower the distance, the better is the solution. If the distance is the same , prefer the path with least stops/turns.


_You will find the instructions for running the code in the respective directory. Message me for any doubts. Only code in the solution file, bot code file is the implementation of bot._
_Preferably fork the repo and implement the solution. Later you can share the link to your repo._

### Public functions and custom data types of the bot:

Data Types:
	Enum Dir{possible values -> A, B, C, D, E, F}
	
	Pose {
		Front facing : type = enum Dir
		X coordinate: type = int
		Y coordinate: type = int
}
Functions:
Refer the bot file for implementation doubts for language specific syntax
Calling syntax
Example input output is there in solution code file for each command 

    Bot_instance = Bot with_default_pose(name: type string); 	-> creates a bot from bot class(implemented in bot code file)


    bot_instance.greet()	-> prints hello world message 🥰


    bot_instance.current_position()  	-> prints current position and returns pose data type


    bot_instance.walk(distance: type float) 		-> walks the bot for given direction. Returns nothin


    bot_instance.turn(Dir direction)  		-> turns the bot in given direction


    bot_instance.predict(start_pos: type pose,  move_commands: type List(either Dir or Float), <dist> : type float [this is an optional parameter ])		->returns list [pose, distance: type float]. Can be used to predict how much is the distance travelled by the bot after following the commands given in the list. Also no need to type the whole command; only float value for distance and dir value for turning will do. Refer the example code in solution code file


    bot_instance.total_distance() 	-> returns float which is total travelled dist


	
### Expected output:
I wanted to make Test bench but i’m short of time now so the code will be manually tested

Write a function that takes only a single Pose data type as input named as target. This pose is where the bot has to reach.
The function should make an instance of the bot with default pose 
Find the optimum path  to target
Traverse till the target
The final state of this function must take the bot to the target pose
Leave some space for me to write test code here
After completing this function, write a loop that takes a list of pose and calls above function multiple times
Share your repo link after solving.

### Testing params:
Accuracy
Efficiency
Innovation for creative solutions


### Bonus : use feedback loop to correct bot’s position. You can read the accurate bot position from current_positon() function.
