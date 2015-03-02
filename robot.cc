#include "robot.h"
#include "timing.h"
#include "dev/ports.h"

/*
Port mappings:

Port 0
    Reserved for sensor test rig

Port 1 - line and egg sensors
    0  LSL  Line Sensor Left
    1  LSC  Line Sensor Centre
    2  LSR  Line Sensor Right
    3  LSA  Line Sensor Arm

    4  ELR    Egg LED Red
    5  ELG  Egg LED Green
    6  ELB  Egg LED Blue
    7  ELO  Egg LDR sensor output

Port 2 - arm

    0  APL  Arm Pivot Lowered
    1  APR  Arm Pivot Raised
    2  AGE  Arm Grab Extended
    3  AGR  Arm Grab Retracted
    4  DR  delivery raised
    5  BSF  Box Switch Front
    6  APA  Arm Pivot Actuator
    7  AGA  Arm Grab Actuator
   

Port 3 - courier indicator LEDs & Lightgate

    0  C1W  Courier bottom - White egg indicator LED
    1  C1R  Courier bottom - Red egg indicator LED
    2  C2W  Courier Middle - white egg indicator LED
    3  C2R  Courier middle - Red egg indicator LED
    4  C3W  Courier top - white egg indicator LED
    5  C3R  Courier top - Red egg indicator LED

    6  LGO Lightgate Output
    7  LGI light gate indicator
*/
Robot::Robot(RLink& rlink) :
	drive(rlink, {
		radius: 0.05,
		spacing: 0.28,
		rpm: 20
	}),
	arm(rlink, port::P3),
	ls(rlink, port::P1),
	detector(rlink, port::P2) { }

const LineSensors::Reading& CachingRobot::ls() {
	if (_lsUpdated < ticks()) {
		_lsReading = Robot::ls.read();
	}

	return( _lsReading );
}


const EggSensor::Reading& CachingRobot::eld() {
	if (_esUpdated < ticks()) {
		_esReading = detector.read();
	}

	return( _esReading );
}
