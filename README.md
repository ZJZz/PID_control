# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

After implemented the PID control equation, we limit the steer angle between -1 to 1, the car should move. And then we only need to change the Kp, Ki, Kd variable to the right value to keep the car in the lane.
Kp is the reaction with the CTE, if Kp is bigger, it reacts faster to the changing of CTE
Ki is the correction for bias of the system (car), that the center of the road to calcuate CTE maybe off.
Kd is smoothing for the over oscillation of the car. The bigger Kd, oscillation smooth better.
```c

double PID::TotalError() {

 double steer = -Kp * p_error - Ki * i_error - Kd * d_error;
 if (steer > 1.0) {steer = 1;}
 if (steer < -1.0){steer = -1;}
 return steer; 
}
```
since one of the requirement for this project is keep the car with in the road.
so, before jump into the tuning those three variable, I choose to look at the throttle_value which is similar to acceleration of the car. After I play with this value few time. I relized as long as I keep the throttle_value around 0.1, with small number for Kp, Ki and Kd. The car can slowly drive through the whole round. But this is not what we looking for. 
we want to see the car driving, not slowly roll over the whole circle. And this gives me the idea for controlling the acceleration.
```c
double PID::acceleration(double cte, double speed, double angle){
	double acc;
	cout << "cte: " << cte << "  | angle : " << angle << "   | speed : " << speed << endl;
	acc = - ((fabs(cte)) / 3 ) - ((fabs(angle)) / 100) - ((speed - 80) / 100) + 0.2;
	return acc;
}

```
This idea is to let the car slow down when it need to turn or off the center too much, this gives the car more time to react and do not run out of the road for most of the time. 
After manually change the variable i choose kp = 0.22; ki = 0.0004; kd = 4.5; the average speed increasing from 20mph to 40mph. The idea behind choose the variable is adjusting Kp value so that the car react to change of CTE, but not too much. if Kp is too big, it will keep oscillate every time, CTE changed little. Also to reduce the oscillation, I increased Kd.
if Kp is too small, it will not turn on time and it will miss the turn, but since i have the acceleration formula. it will reduce the acceleration to negative and stop before it runs out of the road. For Ki, i just choose a small number because Udacity simulator do not have much system bias. 

To improve this PID control, i can increase the speed limit in the acceleration formula and using twiddle to choose the variable for Kp, Ki, Kd . it will better than choosing manually. When choosing manually, most likely choosing the round number. twiddle can give a better variable to improve the control.


---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./
