#ifndef PID_H
#define PID_H
#include <vector>
#include <iostream>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  double old_cte;
  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;
  
  /*
  * twiddle 
  */
  int step;
  int target_steps = 400;

  double twiddle_error;
  double best_error;

  std::vector<double> dp;

  bool twd_init = false;


  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  /*
  * control the accelartion.
   */
  double acceleration(double cte, double speed, double angle);

  void twiddle();
};

#endif /* PID_H */
