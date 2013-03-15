/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Servo.hpp"

using namespace interfaces;

Servo::Servo(std::string const& name)
    : ServoBase(name), 
    target_angle(0), last_angle(0)
{
    _rotation_axis.value() = base::Vector3d::UnitX();
}

Servo::Servo(std::string const& name, RTT::ExecutionEngine* engine)
    : ServoBase(name, engine),
    target_angle(0), last_angle(0)
{
    _rotation_axis.value() = base::Vector3d::UnitX();
}

Servo::~Servo()
{
}

/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Servo.hpp for more detailed
// documentation about them.

// bool Servo::configureHook()
// {
//     if (! ServoBase::configureHook())
//         return false;
//     return true;
// }
bool Servo::startHook()
{
    upper2lower.initSane();
    upper2lower.position.setZero();
    upper2lower.sourceFrame = _upper_frame.value();
    upper2lower.targetFrame = _lower_frame.value();

    if (! ServoBase::startHook())
        return false;
    return true;
}

void Servo::updateHook()
{
    double present_angle = get_angle();
    _angle.write( present_angle );
    
    //also report as transformation
    upper2lower.time = getTime();
    upper2lower.orientation = Eigen::AngleAxisd( -present_angle, _rotation_axis.value() );
    _upper2lower.write(upper2lower);

    switch(_mode.value())
    {
	case servo::POSITION:
	    //return if no angle was set and in mode 0
	    if(_cmd_angle.readNewest( target_angle ) == RTT::NoData)
	    {
		return;
	    }
	    set_angle(target_angle);

	    break;
	case servo::SWEEP:
	    if(fabs(last_angle - present_angle) < .2/180*M_PI)
	    {
		if(fabs(present_angle - _upper_sweep_angle.value()) < 4.0/180*M_PI 
		   && target_angle == _upper_sweep_angle.value())
		{
		    target_angle = _lower_sweep_angle.value();
		    set_angle(target_angle);
		}
   
		if(fabs(present_angle - _lower_sweep_angle.value()) < 4.0/180*M_PI 
		   && target_angle == _lower_sweep_angle.value())
		{
		    target_angle = _upper_sweep_angle.value();
		    set_angle(target_angle);
		}
	    }
	    
	    if(target_angle != _lower_sweep_angle.value() &&
	       target_angle != _upper_sweep_angle.value())
	    {
		target_angle = _upper_sweep_angle.value();
		set_angle(target_angle);
	    }
	    //note sending target angle over and over results in 
	    //non fluent movement of the servo in speed mode
	    break;
    }
    last_angle = present_angle;

    ServoBase::updateHook();
}
// void Servo::errorHook()
// {
//     ServoBase::errorHook();
// }
// void Servo::stopHook()
// {
//     ServoBase::stopHook();
// }
// void Servo::cleanupHook()
// {
//     ServoBase::cleanupHook();
// }

#ifndef VIRTUAL
#endif
