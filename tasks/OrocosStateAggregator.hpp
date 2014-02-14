#ifndef OROCOS_COMMAND_DISPATCHER_HPP
#define OROCOS_COMMAND_DISPATCHER_HPP

#include "StateAggregator.hpp"
#include <rtt/TaskContext.hpp>
#include <rtt/Port.hpp>

class OrocsStateAggregator: public StateAggregator
{
private:
    RTT::OutputPort< base::samples::Joints > *outputPort;
    RTT::TaskContext &task;
public:
    OrocsStateAggregator(RTT::TaskContext &task, ::std::string const & name, const std::vector< int32_t >& statusMap, base::Time statusInterval);
    
    ~OrocsStateAggregator();
    
    virtual void writeStatus(const base::samples::Joints& status);
};


class OrocosCommandDispatcher: public CommandDispatcher
{
    RTT::InputPort< base::commands::Joints > *port;
    RTT::TaskContext &task;

    base::commands::Joints inputSample;
public:
    OrocosCommandDispatcher(RTT::TaskContext &task, boost::function<void (int32_t actuatorId, base::JointState::MODE mode, double value)> setCommandCallback, ::std::string const & name, ::std::vector< boost::int32_t > const & actuatorMap);
    
    ~OrocosCommandDispatcher();
    
    void process();
};

#endif
