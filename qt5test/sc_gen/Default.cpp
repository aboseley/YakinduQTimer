
#include "Default.h"
#include <string.h>
/*! \file Implementation of the state machine 'default'
*/

Default::Default() {
	
	
	stateConfVectorPosition = 0;
	
	timer = NULL;
}

Default::~Default() {
}


void Default::init()
{
	for (int i = 0; i < maxOrthogonalStates; ++i)
		stateConfVector[i] = Default_last_state;
	
	stateConfVectorPosition = 0;

	clearInEvents();
	clearOutEvents();
	
	/* Default init sequence for statechart default */
	iface.counter = 0;

}

void Default::enter()
{
	/* Default enter sequence for statechart default */
	enact();
	enseq_main_region_default();
}

void Default::exit()
{
	/* Default exit sequence for statechart default */
	exseq_main_region();
	exact();
}

sc_boolean Default::isActive() {
	return stateConfVector[0] != Default_last_state;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean Default::isFinal(){
   return false;}

void Default::runCycle() {
	
	clearOutEvents();
	
	for (stateConfVectorPosition = 0;
		stateConfVectorPosition < maxOrthogonalStates;
		stateConfVectorPosition++) {
			
		switch (stateConfVector[stateConfVectorPosition]) {
		case main_region_waiting : {
			react_main_region_waiting();
			break;
		}
		case main_region_done : {
			react_main_region_done();
			break;
		}
		default:
			break;
		}
	}
	
	clearInEvents();
}

void Default::clearInEvents() {
	timeEvents[0] = false; 
	timeEvents[1] = false; 
	timeEvents[2] = false; 
}

void Default::clearOutEvents() {
	iface.heartbeat_raised = false;
	iface.fingertap_raised = false;
	iface.footstomp_raised = false;
	iface.done_raised = false;
}


void Default::setTimer(TimerInterface* timer){
	this->timer = timer;
}

TimerInterface* Default::getTimer(){
	return timer;
}

void Default::raiseTimeEvent(sc_eventid evid) {
	if ((evid >= &timeEvents) && (evid < &timeEvents + sizeof(timeEvents))) {
		*(sc_boolean*)evid = true;
	}
}

sc_boolean Default::isStateActive(DefaultStates state) {
	switch (state) {
		case main_region_waiting : 
			return (sc_boolean) (stateConfVector[0] == main_region_waiting
			);
		case main_region_done : 
			return (sc_boolean) (stateConfVector[0] == main_region_done
			);
		default: return false;
	}
}

Default::DefaultSCI* Default::getDefaultSCI() {
	return &iface;
}

sc_boolean Default::DefaultSCI::isRaised_heartbeat() {
	return heartbeat_raised;
}

sc_boolean Default::isRaised_heartbeat() {
	return iface.isRaised_heartbeat();
}

sc_boolean Default::DefaultSCI::isRaised_fingertap() {
	return fingertap_raised;
}

sc_boolean Default::isRaised_fingertap() {
	return iface.isRaised_fingertap();
}

sc_boolean Default::DefaultSCI::isRaised_footstomp() {
	return footstomp_raised;
}

sc_boolean Default::isRaised_footstomp() {
	return iface.isRaised_footstomp();
}

sc_boolean Default::DefaultSCI::isRaised_done() {
	return done_raised;
}

sc_boolean Default::isRaised_done() {
	return iface.isRaised_done();
}


sc_integer Default::DefaultSCI::get_counter() {
	return counter;
}

sc_integer Default::get_counter() {
	return iface.counter;
}

void Default::DefaultSCI::set_counter(sc_integer value) {
	counter = value;
}

void Default::set_counter(sc_integer value) {
	iface.counter = value;
}


// implementations of all internal functions

sc_boolean Default::check_main_region_waiting_tr0_tr0() {
	return iface.counter > 10;
}

sc_boolean Default::check_main_region_waiting_lr0_lr0() {
	return timeEvents[0];
}

sc_boolean Default::check_main_region_waiting_lr1_lr1() {
	return timeEvents[1];
}

sc_boolean Default::check_main_region_waiting_lr2_lr2() {
	return timeEvents[2];
}

void Default::effect_main_region_waiting_tr0() {
	exseq_main_region_waiting();
	enseq_main_region_done_default();
}

void Default::effect_main_region_waiting_lr0_lr0() {
	iface.counter += 1;
	iface.heartbeat_raised = true;
}

void Default::effect_main_region_waiting_lr1_lr1() {
	iface.fingertap_raised = true;
}

void Default::effect_main_region_waiting_lr2_lr2() {
	iface.footstomp_raised = true;
}

/* Entry action for statechart 'default'. */
void Default::enact() {
}

/* Entry action for state 'waiting'. */
void Default::enact_main_region_waiting() {
	/* Entry action for state 'waiting'. */
	timer->setTimer(this, &timeEvents[0], 1 * 1000, true);
	timer->setTimer(this, &timeEvents[1], 215, true);
	timer->setTimer(this, &timeEvents[2], 300, true);
}

/* Entry action for state 'done'. */
void Default::enact_main_region_done() {
	/* Entry action for state 'done'. */
	iface.done_raised = true;
}

/* Exit action for state 'default'. */
void Default::exact() {
}

/* Exit action for state 'waiting'. */
void Default::exact_main_region_waiting() {
	/* Exit action for state 'waiting'. */
	timer->unsetTimer(this, &timeEvents[0]);
	timer->unsetTimer(this, &timeEvents[1]);
	timer->unsetTimer(this, &timeEvents[2]);
}

/* 'default' enter sequence for state waiting */
void Default::enseq_main_region_waiting_default() {
	/* 'default' enter sequence for state waiting */
	enact_main_region_waiting();
	stateConfVector[0] = main_region_waiting;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state done */
void Default::enseq_main_region_done_default() {
	/* 'default' enter sequence for state done */
	enact_main_region_done();
	stateConfVector[0] = main_region_done;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
void Default::enseq_main_region_default() {
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default();
}

/* Default exit sequence for state waiting */
void Default::exseq_main_region_waiting() {
	/* Default exit sequence for state waiting */
	stateConfVector[0] = Default_last_state;
	stateConfVectorPosition = 0;
	exact_main_region_waiting();
}

/* Default exit sequence for state done */
void Default::exseq_main_region_done() {
	/* Default exit sequence for state done */
	stateConfVector[0] = Default_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for region main region */
void Default::exseq_main_region() {
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of default.main_region) at position 0... */
	switch(stateConfVector[ 0 ]) {
		case main_region_waiting : {
			exseq_main_region_waiting();
			break;
		}
		case main_region_done : {
			exseq_main_region_done();
			break;
		}
		default: break;
	}
}

/* The reactions of state waiting. */
void Default::react_main_region_waiting() {
	/* The reactions of state waiting. */
	if (check_main_region_waiting_tr0_tr0()) { 
		effect_main_region_waiting_tr0();
	}  else {
		if (check_main_region_waiting_lr0_lr0()) { 
			effect_main_region_waiting_lr0_lr0();
		} 
		if (check_main_region_waiting_lr1_lr1()) { 
			effect_main_region_waiting_lr1_lr1();
		} 
		if (check_main_region_waiting_lr2_lr2()) { 
			effect_main_region_waiting_lr2_lr2();
		} 
	}
}

/* The reactions of state done. */
void Default::react_main_region_done() {
	/* The reactions of state done. */
}

/* Default react sequence for initial entry  */
void Default::react_main_region__entry_Default() {
	/* Default react sequence for initial entry  */
	enseq_main_region_waiting_default();
}


