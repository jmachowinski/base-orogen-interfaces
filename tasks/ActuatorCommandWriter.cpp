/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "ActuatorCommandWriter.hpp"
#include "OrocosStateAggregator.hpp"

using namespace interfaces;

ActuatorCommandWriter::ActuatorCommandWriter(std::string const& name)
    : ActuatorCommandWriterBase(name)
{
}

ActuatorCommandWriter::ActuatorCommandWriter(std::string const& name, RTT::ExecutionEngine* engine)
    : ActuatorCommandWriterBase(name, engine)
{
}

ActuatorCommandWriter::~ActuatorCommandWriter()
{
}


bool ActuatorCommandWriter::dispatch(::std::string const & name, ::std::vector< boost::int32_t > const & actuatorMap)
{
    OrocosCommandDispatcher *disp;
    try {
	disp = new OrocosCommandDispatcher(*this, boost::bind(&ActuatorCommandWriter::setCommand, this, _1 , _2, _3), name, actuatorMap);
    } catch (std::runtime_error e)
    {
	std::cout << e.what() << std::endl;
	return false;
    }
    cmdDispatches.push_back(disp);
    return true;
}

void ActuatorCommandWriter::processDispatched()
{
    for(std::vector<OrocosCommandDispatcher *>::iterator it = cmdDispatches.begin(); it != cmdDispatches.end(); it++)
    {
	(*it)->process();
    }
}


void ActuatorCommandWriter::cleanupHook()
{
    RTT::TaskContext::cleanupHook();
    
    for(unsigned int i = 0; i < cmdDispatches.size(); i++)
    {
	delete cmdDispatches[i];
    }

    cmdDispatches.clear();
}

