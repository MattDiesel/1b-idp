#pragma once
#include "device.h"
#include <cmath>

/**
Intended usage:

    Drive d(robot);

    // forward, steer with center of curvature on left
    d.move({.forward=0.9, .steer=0.1});

*/
class Drive : public Device {
public:
    /// struct parameterizing drive configuration
    struct Configuration {
        float radius;  // m
        float spacing; // m
        float rpm;     // rpm
    };

    /// struct indicating maximum speeds, built from a geometry
    struct Speeds {
        const float linear; // m/s
        const float rotary; // deg/s
        Speeds(Configuration g);
    };

private:
    static const Configuration _defConfig;

public:
    Drive(RLink& r, Configuration c = Drive::_defConfig);
    ~Drive();

    /**
    @param args.forward  non-dimensional linear speed: 1 is full speed
                         forwards, -1 is full speed backwards

    @param args.steer    non-dimensional rotational speed: 1 is full speed
                         CCW

    Should ensure that abs(args.forward) + abs(args.steer) <= 1
    */
    struct move_args {
        float forward;
        float steer;
    };
    void move(move_args args);

    /// low-level motor access
    void setWheelSpeeds(float left, float right);

    /// shorthand for no motion
    void stop() { setWheelSpeeds(0, 0); }

    /// convert floating point speed to sign/magnitude
    static uint8_t convertSpeed(float s);

    const Speeds maxSpeeds;
};


