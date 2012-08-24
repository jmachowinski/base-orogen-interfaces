/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "LaserRangeFinder.hpp"

using namespace interfaces;

LaserRangeFinder::LaserRangeFinder(std::string const& name)
    : LaserRangeFinderBase(name)
{
}

LaserRangeFinder::LaserRangeFinder(std::string const& name, RTT::ExecutionEngine* engine)
    : LaserRangeFinderBase(name, engine)
{
}

LaserRangeFinder::~LaserRangeFinder()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See LaserRangeFinder.hpp for more detailed
// documentation about them.

// bool LaserRangeFinder::configureHook()
// {
//     if (! LaserRangeFinderBase::configureHook())
//         return false;
//     return true;
// }
// bool LaserRangeFinder::startHook()
// {
//     if (! LaserRangeFinderBase::startHook())
//         return false;
//     return true;
// }
// void LaserRangeFinder::updateHook()
// {
//     LaserRangeFinderBase::updateHook();
// }
// void LaserRangeFinder::errorHook()
// {
//     LaserRangeFinderBase::errorHook();
// }
// void LaserRangeFinder::stopHook()
// {
//     LaserRangeFinderBase::stopHook();
// }
// void LaserRangeFinder::cleanupHook()
// {
//     LaserRangeFinderBase::cleanupHook();
// }

