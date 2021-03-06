#pragma once
#include "device.h"
#include <cmath>
#include "../util/timeout.h"

/**
    Interface to the two-wheeled drive system
*/
class Drive : public Device {
public:
    /**
    struct indicating maximum speeds, built from a Configuration
    */
    struct Speeds {
        float linear; //< maximum forward/reversing speed in m/s
        float rotary; //< maximum rotational speed in degrees/s
    };

    /**
    Describes the physical configuration of the robot
    */
    struct Configuration {
        float radius;  ///< wheel radius, in m
        float spacing; ///< distance between centers of wheels, in m
        float rpm;     ///< motor speed, in rpm
        operator Speeds();
    };

private:
    static const Configuration _defConfig;

public:
    /**
    Initialize a drive over a connection.

    @param r  the link to the robot
    @param c  the drive geometry and speeds, used to populate Drive::maxSpeeds
    */
    Drive(RLink& r, Configuration c = Drive::_defConfig);
    ~Drive();

    struct move_args {
        float forward;
        float steer;
    };
    /**
    @param args.forward  non-dimensional linear speed: 1 is full speed
                         forwards, -1 is full speed backwards

    @param args.steer    non-dimensional rotational speed: 1 is full speed
                         CCW

    Should ensure that abs(args.forward) + abs(args.steer) <= 1
    */
    void move(move_args args);


    /// Move in a straight line, and return a timeout indicating expected completion
    Timeout straight(float dist, float speed = 1);
    Timeout::duration_type timeForStraight(float dist, float speed = 1);

    /// Turn an angle on the spot, and return a timeout indicating expected completion
    Timeout turn(float angle, float speed = 1);
    Timeout::duration_type timeForTurn(float angle, float speed = 1);

    /// low-level motor access. Speeds should be between 1 and -1
    void setWheelSpeeds(float left, float right);

    /// shorthand for no motion
    void stop() { setWheelSpeeds(0, 0); }

    /// convert floating point speed to sign/magnitude
    static uint8_t convertSpeed(float s);

    /// The maximum speeds the robot is able to acheive
    Speeds maxSpeeds;
};


