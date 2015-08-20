#include "WPILib.h"

class Robot: public SampleRobot
{
	CANJaguar j_right_front; 		// robot drive system motor	// normal
	CANJaguar j_right_rear; 		// robot drive system motor	// normal
	CANJaguar j_left_front; 		// robot drive system motor	// inverted
	CANJaguar j_left_rear; 			// robot drive system motor	// inverted

	Joystick s_drive; 				// drive controller, program considers this to be a joy-stick
	Joystick s_buttons; 			// button controller, program considers this to be a joy-stick
	Joystick s_override;			// override controller for kid mode, program considers this
									// to be a joy-stick

	CANJaguar j_intake;				// in-take motor			// positive numbers bring in		// normal
	CANJaguar j_turret_aim;			// turret aim motor			// positive numbers rotate right	// normal
	CANJaguar j_turret_flywheel;	// turret fly-wheel motor	// positive numbers shoot ball		// normal

	Solenoid s_shifter;				// drive train shifter solenoid
	Solenoid s_shooter;				// solenoid that lifts the ball into the fly-wheel
	Solenoid s_turret;				// solenoid that lifts turret

	AnalogPotentiometer a_turret;	// potentiometer // TODO may need to be replaced by AnalogInput
	// XXX: DigitalInput d_turret; 	// photo sensor	 // TODO may need to be replaced by PhotoSensor

public:
	Robot(): // Basic initialization, should not contain complex calculations

		j_right_front(0), 		// set CAN number
		j_right_rear(1),		// set CAN number
		j_left_front(2),		// set CAN number
		j_left_rear(3),			// set CAN number

		s_drive(0),				// set USB port number, doesn't correspond to actual USB port, just the ordering in the driver station
		s_buttons(1),			// set USB port number, doesn't correspond to actual USB port, just the ordering in the driver station
		s_override(2),			// set USB port number, doesn't correspond to actual USB port, just the ordering in the driver station

		j_intake(4),			// set CAN number
		j_turret_aim(5),		// set CAN number
		j_turret_flywheel(6),	// set CAN number

		s_shifter(1, 0),		// set CAN number for PCM and set solenoid number
		s_shooter(1, 1),		// set CAN number for PCM and set solenoid number
		s_turret(1, 2),			// set CAN number for PCM and set solenoid number

		a_turret(0, 360, -180)	// set Analog Input number, the range of the sensor (arbitrary unit), and the minimum value that should be read
		//d_turret(0);			// set Digital Input number
	{

	}

	/**
	 * Runs the motors with arcade steering.
	 */
	void RobotMain()
	{

		// Initialization code goes here, more complex calculations can be done here

		int shooting = 0;
		bool shifted = true;
		bool turret = false;;

		double turret_angle = 0;  	// -180 to 180

		double left_speed = 0;  	// -1 to 1
		double right_speed = 0;  	// -1 to 1

		const double KID_DRIVE_SPEED = 0.2;
		const double KID_SHOOT_SPEED = 0.6;

		const double SHOOT_SPEED = 1;

		const int LEFT = -1;
		const int RIGHT = 1;

		bool disabled_run = false;

		bool drive_override;
		bool buttons_override;

		while (true) // main loop
		{
			if (IsDisabled())
			{
				if (!disabled_run)
				{
					j_right_front.Set(0);
					j_right_rear.Set(0);
					j_left_front.Set(0);
					j_left_rear.Set(0);

					j_intake.Set(0);
					j_turret_aim.Set(0);
					j_turret_flywheel.Set(0);

					s_shifter.Set(false);
					s_shooter.Set(false);
					s_turret.Set(false);
					disabled_run = true;
				}
			}
			else
			{
				if (IsNewDataAvailable())
				{
					drive_override = s_override.GetRawButton(4);	// if this button is depressed and
																	// the robot is in kid mode, the user
																	// of the override controller will be the
																	// sole operator of the drive
					buttons_override = s_override.GetRawButton(4);	// if this button is depressed and
																	// the robot is in kid mode, the user
																	// of the override controller will be the
																	// sole operator of the shooting and
																	// in-take mechanisms
				}
				if (IsAutonomous()) // kid mode
				{
					if (drive_override) {

					}
				}
				else if (IsOperatorControl()) // normal mode
				{

				}
			}
			Wait(0.005);
		}
	}
private:
	double limit(double speed) {
		return (speed > 1) ? 1 : ((speed < -1) ? -1 : speed); 	// if less than -1, -1
																// else if greater than 1, 1
																// else return unchanged value
	}
	double limit_kid(double speed) {
		return (speed > 0.3) ? 0.3 : ((speed < -0.3) ? -0.3 : speed); 	// if less than -0.3, -0.3
																		// else if greater than 0.3, 0.3
																		// else return unchanged value
	}
};

START_ROBOT_CLASS(Robot);

/*
        moveValue = limit(moveValue);
        rotateValue = limit(rotateValue);

        if (squaredInputs) {
            // square the inputs (while preserving the sign) to increase fine control while permitting full power
            if (moveValue >= 0.0) {
                moveValue = (moveValue * moveValue);
            } else {
                moveValue = -(moveValue * moveValue);
            }
            if (rotateValue >= 0.0) {
                rotateValue = (rotateValue * rotateValue);
            } else {
                rotateValue = -(rotateValue * rotateValue);
            }
        }

        if (moveValue > 0.0) {
            if (rotateValue > 0.0) {
                leftMotorSpeed = moveValue - rotateValue;
                rightMotorSpeed = Math.max(moveValue, rotateValue);
            } else {
                leftMotorSpeed = Math.max(moveValue, -rotateValue);
                rightMotorSpeed = moveValue + rotateValue;
            }
        } else {
            if (rotateValue > 0.0) {
                leftMotorSpeed = -Math.max(-moveValue, rotateValue);
                rightMotorSpeed = moveValue + rotateValue;
            } else {
                leftMotorSpeed = moveValue - rotateValue;
                rightMotorSpeed = -Math.max(-moveValue, -rotateValue);
            }
        }*/
