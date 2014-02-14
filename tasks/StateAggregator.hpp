#ifndef STATEAGGREGATOR_HPP
#define STATEAGGREGATOR_HPP
#include <vector>
#include <map>
#include <base/time.h>
#include <base/commands/Joints.hpp>
#include <boost/function.hpp>

class StateAggregator
{
    class StateInfo
    {
    public:
	int stateId;
	int outputPosition;
	bool isReverse;
	bool updated;
	base::Time updateTime;
    };
    
    ///amount of dispatched actuators
    int actuatorCnt;
    
    ///conter for arrived state updates
    int updateCnt;
    
    base::commands::Joints status;
    std::vector<StateInfo *> stateIdToInfo;
    
    std::map<int, StateInfo> stateMap;

    ///The nominal time between two state updates
    base::Time statusInterval;
    
    void reset();

protected:
    const base::commands::Joints &getStatus() const 
    {
	return status;
    };
    
public:
    
    const std::vector<int32_t> getActuatorIds() const;
    
    StateAggregator(const std::vector<int32_t>& statusMap, base::Time statusInterval);
    virtual ~StateAggregator() {};
    
    void setNewStatus(int stateId, const base::Time stateTime, const base::JointState& state);

    virtual void writeStatus(const base::commands::Joints &status) = 0;	
};

class CommandDispatcher
{
    class InputMapping
    {
    public:
	int actuatorId;
	int inputId;
	bool isReverse;
    };    
    
    ///map from positions in the base::actuator::command to the driver ids
    std::vector<InputMapping> inputMap;
    
    boost::function<void (int32_t actuatorId, base::JointState::MODE mode, double value)> setCommandCallback;
    
public:
    const std::vector<int32_t> getActuatorIds() const;
    
    CommandDispatcher(std::vector< boost::int32_t > const & actuatorMap, boost::function<void (int32_t actuatorId, base::JointState::MODE mode, double value)> setCommandCallback);
    virtual ~CommandDispatcher() {};
    
    void processCommand(base::commands::Joints cmd);    
};



#endif // STATEAGGREGATOR_HPP
