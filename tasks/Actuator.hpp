/* Generated from orogen/lib/orogen/templates/tasks/Task.hpp */

#ifndef INTERFACES_ACTUATOR_TASK_HPP
#define INTERFACES_ACTUATOR_TASK_HPP

#include "interfaces/ActuatorBase.hpp"
#include "OrocosStateAggregator.hpp"

namespace interfaces {

    /*! \class Actuator 
     * \brief The task context provides and requires services. It uses an ExecutionEngine to perform its functions.
     * Essential interfaces are operations, data flow ports and properties. These interfaces have been defined using the oroGen specification.
     * In order to modify the interfaces you should (re)use oroGen and rely on the associated workflow.
     * 
     * \details
     * The name of a TaskContext is primarily defined via:
     \verbatim
     deployment 'deployment_name'
         task('custom_task_name','interfaces::Actuator')
     end
     \endverbatim
     *  It can be dynamically adapted when the deployment is called with a prefix argument. 
     */
    class Actuator : public ActuatorBase
    {
	friend class ActuatorBase;
    protected:
	std::vector<OrocosCommandDispatcher *> cmdDispatches;
	std::vector<StateAggregator *> stateDispatches;
	std::vector<int> actuatorToDispatchMap;

	///The nominal time between two status updates of an actuator
	base::Time statusInterval;
	
	virtual void statusDispatchAdded(int dispatchId, std::vector<int> actuatorIds) = 0;
	void setNewActuatorStatus(int actuatorId, const base::Time stateTime, const base::actuators::MotorState &state);

	virtual void setCommand(int32_t actuatorId, base::actuators::DRIVE_MODE mode, double value) = 0;
	
	/**
	 * Pull all data from the dispatch ports
	 * */
	void processDispatched();

	/* Handler for the dispatch operation
         */
        virtual bool dispatch(::std::string const & name, ::std::vector< boost::int32_t > const & actuatorMap);

    public:
        /** TaskContext constructor for Actuator
         * \param name Name of the task. This name needs to be unique to make it identifiable via nameservices.
         * \param initial_state The initial TaskState of the TaskContext. Default is Stopped state.
         */
        Actuator(std::string const& name = "interfaces::Actuator");

        /** TaskContext constructor for Actuator 
         * \param name Name of the task. This name needs to be unique to make it identifiable for nameservices. 
         * \param engine The RTT Execution engine to be used for this task, which serialises the execution of all commands, programs, state machines and incoming events for a task. 
         * 
         */
        Actuator(std::string const& name, RTT::ExecutionEngine* engine);

        /** Default deconstructor of Actuator
         */
	~Actuator();

        /** This hook is called by Orocos when the state machine transitions
         * from Stopped to PreOperational, requiring the call to configureHook()
         * before calling start() again.
         */
        void cleanupHook();
    };
}

#endif

