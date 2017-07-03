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

	if(step < target_steps && step > 100){
		twiddle_error += cte * cte;
	}
	step++;
}

double PID::TotalError() {
	double steer = -Kp * p_error - Ki * i_error - Kd * d_error;
	if (steer > 1.0) {steer = 1;}
	if (steer < -1.0){steer = -1;}

	return steer;
}

double PID::acceleration(double cte, double speed, double angle){
	double acc;
	// if (fabs(cte) > 0.5 && fabs(angle) > 6.0 && speed > 40){
	// 	acc = -0.8;
	// }

	cout << "cte: " << cte << "  | angle : " << angle << "   | speed : " << speed << endl;
	acc = - ((fabs(cte)) / 3 ) - ((fabs(angle)) / 100) - ((speed - 80) / 100) + 0.2;
	return acc;
}

void PID::twiddle(){
	double err = twiddle_error / target_steps;

	if(!twd_init){
		best_error = err;
		dp = {Kp/4, Ki/4, 0.1};
		twiddle_error = 0;
		step = 0;
		twd_init = true;
		cout << "finish init" << endl;
		cout << "KP, Ki, Kd: "<<"(" << Kp << ", " << Ki << ", " << Kd << ")" << "  error: " << best_error << endl;
	}
	if(step < target_steps) {
		for (int i =0; i < 3; i++)
			switch(i){
				case 0:
					Kp += dp[i];
					break;
				case 1:
					Ki += dp[i];
					break;
				case 2:
					Kd += dp[i];
			if (err < best_error){
				best_error = err;
				dp[i] *= 1.1;
				cout << "better: " << endl;
				cout << "KP, Ki, Kd: "<<"(" << Kp << ", " << Ki << ", " << Kd << ")" << "  error: " << best_error << endl;
			}else{
				switch(i){
					case 0:
						Kp -= 2 * dp[i];
						break;
					case 1:
						Ki -= 2 * dp[i];
						break;
					case 2:
						Kd -= 2 * dp[i];
				}
				dp[i] *=0.9;
			}

		}
	cout << "step: " << step << endl;
	cout << "KP, Ki, Kd: "<<"(" << Kp << ", " << Ki << ", " << Kd << ")" << "  error: " << best_error << endl;

	}
}

	



























