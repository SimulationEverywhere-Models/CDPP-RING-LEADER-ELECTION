/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __RingNode_H
#define __RingNode_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class RingNode: public Atomic
{
public:
	RingNode( const string &name = "RingNode" ) ;	 // Default constructor
	~RingNode();					// Destructor
	virtual string className() const
		{return "RingNode";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	// [(!) TODO: declare ports, distributions and other private varibles here]
	/***********      Example declarations   **********************************/
	const Port &inL;	// this is an input port named 'in'
	const Port &inR;   	// this is an output port named 'out'
	const Port &wakeUp;
	Port &outL;
	Port &outR;
	Port &outDone;
	int min;
	int id;
	enum Ports {NONE, WAKEUP, LEFT, RIGHT, INTERNAL};
	enum Status {ASLEEP, AWAKE, FOLLOWER, LEADER};
	enum
	Ports srcPort;
	Status nodeStatus;
	// Distribution *dist ;
	// Distribution &distribution()	{ return *dist; }
	/**************************************************************************/

	// [(!) declare common variables]
	// Lifetime programmed since the last state transition to the next planned internal transition.
	Time sigma;
	
	// Time elapsed since the last state transition until now
	Time elapsed;
	
	// Time remaining to complete the last programmed Lifetime
	Time timeLeft;	
};	// class RingNode


#endif   //__RingNode_H 
