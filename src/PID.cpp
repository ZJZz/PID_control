#include "PID.h"
#include <math.h>
#include <iostream>
using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	this -> Kp = Kp;
	this -> Ki = Ki;
	this -> Kd = Kd;

	p_error = 0;
	i_error = 0;
	d_error = 0;
}

void PID::UpdateError(double cte) {
	p_error = cte;
	i_error += cte;
	d_error = cte - old_cte;
	old_cte = cte;
}

double PID::TotalError() {
	double steer = -Kp * p_error - Ki * i_error - Kd * d_error;
	if (steer > 1.0) {steer = 1;}
	if (steer < -1.0){steer = -1;}

	return steer;
}

double PID::acceleration(double cte, double speed, double angle){
	double acc;
	cout << "cte: " << cte << "  | angle : " << angle << "   | speed : " << speed << endl;
	acc = - ((fabs(cte)) / 3 ) - ((fabs(angle)) / 100) - ((speed - 70) / 100) + 0.2;
	return acc;
}
