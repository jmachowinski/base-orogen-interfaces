/* Generated from orogen/lib/orogen/templates/tasks/Task.hpp */

#ifndef INTERFACES_ACTUATORSENSORREADER_TASK_HPP
#define INTERFACES_ACTUATORSENSORREADER_TASK_HPP

#include "interfaces/ActuatorSensorReaderBase.hpp"
#include "StateAggregator.hpp"

#ifndef RTT_COMPONENT
#define VIRTUAL = 0
#else
#define VIRTUAL { throw("COULD NOT USE AN ABSTRACT CLASS"); }
#endif

namespace interfaces {

    class OrocosStateAggregator;
    
    /*! \class ActuatorSensorReader 
     * \brief The task context provides and requires services. It uses an ExecutionEngine to perform its functions.
     * Essential interfaces are operations, data flow ports and properties. These interfaces have been defined using the oroGen specification.
     * In order to modify the interfaces you should (re)use oroGen and rely on the associated workflow.
     * 
     * \details
     * The name of a TaskContext is primarily defined via:
     \verbatim
     deployment 'deployment_name'
         task('custom_task_name','interfaces::ActuatorSensorReader')
     end
     \endverbatim
     *  It can be dynamically adapted when the deployment is called with a prefix argument. 
     */
    class ActuatorSensorReader : public ActuatorSensorReaderBase
    {
	friend class ActuatorSensorReaderBase;
    protected:
	std::vector<StateAggregator *> stateDispatches;
	std::vector<int> actuatorToDispatchMap;

	///The nominal time between two status updates of an actuator
	base::Time statusInterval;
	
	virtual void statusDispatchAdded(int dispatchId, std::vector<int> actuatorIds) VIRTUAL;
	void setNewActuatorStatus(int actuatorId, const base::Time stateTime, const base::JointState &state);
	
        /* Handler for the dispatch operation
         */
        virtual bool dispatch(::std::string const & name, ::std::vector< boost::int32_t > const & actuatorMap);

    public:
        /** TaskContext constructor for ActuatorSensorReader
         * \param name Name of the task. This name needs to be unique to make it identifiable via nameservices.
         * \param initial_state The initial TaskState of the TaskContext. Default is Stopped state.
         */
        ActuatorSensorReader(std::string const& name = "interfaces::ActuatorSensorReader");

        /** TaskContext constructor for ActuatorSensorReader 
         * \param name Name of the task. This name needs to be unique to make it identifiable for nameservices. 
         * \param engine The RTT Execution engine to be used for this task, which serialises the execution of all commands, programs, state machines and incoming events for a task. 
         * 
         */
        ActuatorSensorReader(std::string const& name, RTT::ExecutionEngine* engine);

        /** Default deconstructor of ActuatorSensorReader
         */
	virtual ~ActuatorSensorReader();

        /** This hook is called by Orocos when the state machine transitions
         * from Stopped to PreOperational, requiring the call to configureHook()
         * before calling start() again.
         */
        void cleanupHook();
    };
}

#endif

