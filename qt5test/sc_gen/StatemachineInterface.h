
#ifndef STATEMACHINEINTERFACE_H_
#define STATEMACHINEINTERFACE_H_

/*
 * Basic interface for statemachines.
 */
class StatemachineInterface {
	public:
	
		virtual ~StatemachineInterface() = 0;
		
		/*
		* Initializes the statemachine. Use to init internal variables etc.
		*/
		virtual void init() = 0;
	
		/*
		* Enters the statemachine. Sets the statemachine in a defined state.
		*/
		virtual void enter() = 0;
	
		/*
		* Exits the statemachine. Leaves the statemachine with a defined state.
		*/
		virtual void exit() = 0;
	
		/*
		* Start a run-to-completion cycle.
		*/
		virtual void runCycle() = 0;
		
		/*
		* Checks if the statemachine is active. 
	 	* A statemachine is active if it was entered. It is inactive if it has not been entered at all or if it was exited.
	 	*/	
		virtual	sc_boolean isActive() = 0;
		
		/*
		* Checks if all active states are final. 
	 	* If there are no active states then the statemachine is considered as inactive and this method returns false.
	 	*/
		virtual sc_boolean isFinal() = 0;
};

inline StatemachineInterface::~StatemachineInterface() {}

#endif /* STATEMACHINEINTERFACE_H_ */
