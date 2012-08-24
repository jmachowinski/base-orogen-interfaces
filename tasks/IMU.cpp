/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "IMU.hpp"

using namespace interfaces;

IMU::IMU(std::string const& name)
    : IMUBase(name)
{
}

IMU::IMU(std::string const& name, RTT::ExecutionEngine* engine)
    : IMUBase(name, engine)
{
}

IMU::~IMU()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See IMU.hpp for more detailed
// documentation about them.

// bool IMU::configureHook()
// {
//     if (! IMUBase::configureHook())
//         return false;
//     return true;
// }
// bool IMU::startHook()
// {
//     if (! IMUBase::startHook())
//         return false;
//     return true;
// }
// void IMU::updateHook()
// {
//     IMUBase::updateHook();
// }
// void IMU::errorHook()
// {
//     IMUBase::errorHook();
// }
// void IMU::stopHook()
// {
//     IMUBase::stopHook();
// }
// void IMU::cleanupHook()
// {
//     IMUBase::cleanupHook();
// }

