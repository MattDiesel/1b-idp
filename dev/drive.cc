#include "drive.h"
#include "robot_instr.h"
#include <cstdint>
#include <cmath>
#include <iostream>
#include <chrono>


const Drive::Configuration Drive::_defConfig {0.0f, 0.0f, 0.0f};


Drive::Drive(RLink& r, Configuration c) : Device(r), maxSpeeds(c) {
	_r.command(RAMP_TIME, 10);
}

Drive::~Drive() {
	stop();
}

uint8_t Drive::convertSpeed(float s) {
	uint8_t res = std::min(fabs(s), 1.0) * 127;

	if(s < 0) res |= 0x80;

	return res;
}

void Drive::move(move_args args) {
	float left = args.forward - args.steer;
	float right = args.forward + args.steer;
	setWheelSpeeds(left, right);
}

Timeout Drive::turn(float angle, float speed) {
	speed = copysignf(speed, angle);
	move({forward: 0, steer: speed});
	return std::chrono::duration<float>(
		angle / (maxSpeeds.rotary * speed)
	);
}
Timeout Drive::straight(float dist, float speed) {
	speed = copysignf(speed, dist);
	move({forward: speed, steer: 0});
	return std::chrono::duration<float>(
		dist / (maxSpeeds.linear * speed)
	);
}

void Drive::setWheelSpeeds(float left, float right) {
	// apply any sign corrections here
	uint8_t left_i = convertSpeed(left);
	uint8_t right_i = convertSpeed(-right);

	if (left_i == right_i) {
		_r.command(BOTH_MOTORS_GO_SAME, left_i);
	}
	else if (left_i == -right_i) {
		// TODO: should this be right_i?
		_r.command(BOTH_MOTORS_GO_OPPOSITE, left_i);
	}
	else {
		_r.command(MOTOR_1_GO, left_i);
		_r.command(MOTOR_2_GO, right_i);
	}
}

Drive::Speeds::Speeds(Drive::Configuration c) :
    linear((2 * M_PI * c.radius) * (c.rpm/60)),
    rotary(linear / (c.spacing / 2) * (180/M_PI)) {}

