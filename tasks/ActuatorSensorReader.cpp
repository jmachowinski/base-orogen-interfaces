/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "ActuatorSensorReader.hpp"
#include "OrocosStateAggregator.hpp"

using namespace interfaces;

ActuatorSensorReader::ActuatorSensorReader(std::string const& name)
    : ActuatorSensorReaderBase(name)
{
}

ActuatorSensorReader::ActuatorSensorReader(std::string const& name, RTT::ExecutionEngine* engine)
    : ActuatorSensorReaderBase(name, engine)
{
}

ActuatorSensorReader::~ActuatorSensorReader()
{
}

bool ActuatorSensorReader::dispatch(::std::string const & name, ::std::vector< boost::int32_t > const & actuatorMap)
{
    OrocsStateAggregator *agg;
    try {
	agg = new OrocsStateAggregator(*this, name, actuatorMap, statusInterval);
    } catch (std::runtime_error e)
    {
	std::cout << e.what() << std::endl;
	return false;
    } 
    
    int dispId = stateDispatches.size();
    stateDispatches.push_back(agg);
    
    //setup mapping from actuator ids to dispatch
    const std::vector<int32_t> ids = agg->getActuatorIds();
    for(std::vector<int32_t>::const_iterator it = ids.begin(); it != ids.end();it++)
    {
	if(actuatorToDispatchMap.size() < (uint32_t) *it)
	    actuatorToDispatchMap.resize(*it);
	
	actuatorToDispatchMap[*it] = dispId;
    }

    //inform the driver implementation about the
    //added dispatch
    statusDispatchAdded(dispId, ids);

    return true;
}


void ActuatorSensorReader::setNewActuatorStatus(int actuatorId, const base::Time stateTime, const base::actuators::MotorState& state)
{
    const int dispId = actuatorToDispatchMap[actuatorId];
    stateDispatches[dispId]->setNewStatus(actuatorId, stateTime, state);
}

void ActuatorSensorReader::cleanupHook()
{
    
    RTT::TaskContext::cleanupHook();
    
    for(unsigned int i = 0; i < stateDispatches.size(); i++)
    {
	delete stateDispatches[i];
    }

    stateDispatches.clear();
}

