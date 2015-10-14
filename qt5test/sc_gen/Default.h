
#ifndef DEFAULT_H_
#define DEFAULT_H_

#include "sc_types.h"
#include "StatemachineInterface.h"
#include "TimedStatemachineInterface.h"

/*! \file Header of the state machine 'default'.
*/

class Default : public TimedStatemachineInterface, public StatemachineInterface {
	
	public:
		
		Default();
		
		~Default();
		
		//! enumeration of all states 
		typedef enum {
			main_region_waiting,
			main_region_done,
			Default_last_state
		} DefaultStates;
		
		//! Inner class for default interface scope.
		class DefaultSCI {
			
			public:
				/*! Checks if the out event 'heartbeat' that is defined in the default interface scope has been raised. */ 
				sc_boolean isRaised_heartbeat();
				
				/*! Checks if the out event 'fingertap' that is defined in the default interface scope has been raised. */ 
				sc_boolean isRaised_fingertap();
				
				/*! Checks if the out event 'footstomp' that is defined in the default interface scope has been raised. */ 
				sc_boolean isRaised_footstomp();
				
				/*! Checks if the out event 'done' that is defined in the default interface scope has been raised. */ 
				sc_boolean isRaised_done();
				
				/*! Gets the value of the variable 'counter' that is defined in the default interface scope. */ 
				sc_integer get_counter();
				
				/*! Sets the value of the variable 'counter' that is defined in the default interface scope. */ 
				void set_counter(sc_integer value);
				
				
			private:
				friend class Default;
				sc_boolean heartbeat_raised;
				sc_boolean fingertap_raised;
				sc_boolean footstomp_raised;
				sc_boolean done_raised;
				sc_integer counter;
		};
				
		
		/*! Returns an instance of the interface class 'DefaultSCI'. */
		DefaultSCI* getDefaultSCI();
		
		/*! Checks if the out event 'heartbeat' that is defined in the default interface scope has been raised. */ 
		sc_boolean isRaised_heartbeat();
		
		/*! Checks if the out event 'fingertap' that is defined in the default interface scope has been raised. */ 
		sc_boolean isRaised_fingertap();
		
		/*! Checks if the out event 'footstomp' that is defined in the default interface scope has been raised. */ 
		sc_boolean isRaised_footstomp();
		
		/*! Checks if the out event 'done' that is defined in the default interface scope has been raised. */ 
		sc_boolean isRaised_done();
		
		/*! Gets the value of the variable 'counter' that is defined in the default interface scope. */ 
		sc_integer get_counter();
		
		/*! Sets the value of the variable 'counter' that is defined in the default interface scope. */ 
		void set_counter(sc_integer value);
		
		
		void init();
		
		void enter();
		
		void exit();
		
		void runCycle();
		
		/*!
		* Checks if the statemachine is active (until 2.4.1 this method was used for states).
		* A statemachine is active if it was entered. It is inactive if it has not been entered at all or if it was exited.
		*/
		sc_boolean isActive();
		
		
		/*!
		* Checks if all active states are final. 
		* If there are no active states then the statemachine is considered as inactive and this method returns false.
		*/
		sc_boolean isFinal();
		
		void setTimer(TimerInterface* timer);
		
		TimerInterface* getTimer();
		
		void raiseTimeEvent(sc_eventid event);
		
		/*! Checks if the specified state is active (until 2.4.1 the used method for states was calles isActive()). */
		sc_boolean isStateActive(DefaultStates state);
	
	private:
	
	
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc_integer maxOrthogonalStates = 1;
		
		TimerInterface* timer;
		sc_boolean timeEvents[3];
		
		DefaultStates stateConfVector[maxOrthogonalStates];
		
		sc_ushort stateConfVectorPosition;
		
		DefaultSCI iface;
		
		// prototypes of all internal functions
		
		sc_boolean check_main_region_waiting_tr0_tr0();
		sc_boolean check_main_region_waiting_lr0_lr0();
		sc_boolean check_main_region_waiting_lr1_lr1();
		sc_boolean check_main_region_waiting_lr2_lr2();
		void effect_main_region_waiting_tr0();
		void effect_main_region_waiting_lr0_lr0();
		void effect_main_region_waiting_lr1_lr1();
		void effect_main_region_waiting_lr2_lr2();
		void enact();
		void enact_main_region_waiting();
		void enact_main_region_done();
		void exact();
		void exact_main_region_waiting();
		void enseq_main_region_waiting_default();
		void enseq_main_region_done_default();
		void enseq_main_region_default();
		void exseq_main_region_waiting();
		void exseq_main_region_done();
		void exseq_main_region();
		void react_main_region_waiting();
		void react_main_region_done();
		void react_main_region__entry_Default();
		void clearInEvents();
		void clearOutEvents();
		
};
#endif /* DEFAULT_H_ */
