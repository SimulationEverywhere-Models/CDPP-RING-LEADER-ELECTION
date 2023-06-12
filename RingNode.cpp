/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "RingNode.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator
#include <stdio.h>


/*******************************************************************
* Function Name: RingNode
* Description: constructor
********************************************************************/
RingNode::RingNode( const string &name )
: Atomic( name )
	, inL(addInputPort("inL"))
	, inR(addInputPort("inR"))
	, wakeUp(addInputPort("wakeUp"))
	, outL(addOutputPort("outL"))
	, outR(addOutputPort("outR"))
	, outDone(addOutputPort("outDone"))
	, min(INT_MAX)
	, srcPort(NONE)
	, nodeStatus(ASLEEP)
// TODO: add ports here if needed (Remember to add them to the .h file also). Each in a new line.
{
	try	{	// grab this instance's id from the coupled model definition
		string id2 = MainSimulator::Instance().getParameter( description(), "id" );
		MASSERT( id2!="" );
		id = str2Int(id2);
	}
	catch( MException &e ) {
		e.addText("\r\n************************ PARAMETER MISSING!!!! ************************ \n"
				  ">>>  ERROR: Add a unique 'id : #' parameter to the model \"" + description() + "\". \t<<<\n"
				  "***********************************************************************\n\n") ;
		e.print(cerr);
		MTHROW( e ) ;
	}
	//printf ("ID: %d \n", id2);
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &RingNode::initFunction()
{
	// [(!) Initialize common variables]
	this->elapsed = Time::Zero;
 	this->timeLeft = Time::Inf;
 	//this->sigma = Time::Inf; // stays in active state until an external event occurs;
 	this->sigma = Time::Zero;

 	min = id;	// start with my id as the minimum
 	this->passivate();	// node is passive by default

 	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &RingNode::externalFunction( const ExternalMessage &msg )
{
	//[(!) update common variables]	
	this->sigma = nextChange();	
	this->elapsed = msg.time()-lastChange();	
 	this->timeLeft = this->sigma - this->elapsed; 
	
	//TODO: implement the external function here.
 	// Remember you can use the msg object (mgs.port(), msg.value()) and you should set the next TA (you might use the holdIn method).
 	// EJ:
 	// if( msg.port() == in )
	//{
	//	// Do something
	//	holdIn( active, this->timeLeft );
	// }
 	// input value:
 	int x = static_cast < int > (msg.value());

 	if(msg.port() == wakeUp){
  		if (nodeStatus == ASLEEP){
  			nodeStatus = AWAKE;
  			srcPort = WAKEUP;
			holdIn( active, Time(0,0,1,0)  ) ;
  		}
 	}else{
		if(nodeStatus != LEADER){ 	// if I'm still a follower or candidate
			if (x==id){			// I received my own id; I now know I'm the leader.
				min = id;
				nodeStatus = LEADER;
				holdIn(active,  Time(0,0,1,0));
			}
			else if (x<min){
				min = x;
				nodeStatus = FOLLOWER;	//I've received a smaller id; I now know I'm a follower.
				srcPort = NONE;
				if(msg.port() == inL ) srcPort = LEFT;
				else if(msg.port() == inR) srcPort = RIGHT;
				holdIn(active,  Time(0,0,1,0));
			}
			else if(x>min){
				nodeStatus = AWAKE;
				min = id;
				if(msg.port() == inL ) srcPort = LEFT;
				else if(msg.port() == inR) srcPort = RIGHT;
				holdIn(active,  Time(0,0,1,0));
			}
		}
 	}
	
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &RingNode::internalFunction( const InternalMessage & )
{
	//TODO: implement the internal function here
	srcPort = NONE;	// clear any port records

	this->sigma = Time::Inf; // stays in passive state until an external event occurs;
	holdIn( passive, this->sigma  );
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &RingNode::outputFunction( const InternalMessage &msg )
{
	//TODO: implement the output function here
	// remember you can use sendOutput(time, outputPort, value) function.
	if(nodeStatus == LEADER)
		sendOutput(msg.time(), outDone, id);
	else{
		if (srcPort == WAKEUP)	// Initiate by sending to the right
			sendOutput(msg.time(), outR, id);
		else if(srcPort == LEFT)	// If received from left; pass on to right
			sendOutput( msg.time(), outR, min);
		else if(srcPort == RIGHT)	// If received from right; pass on to left
			sendOutput( msg.time(), outL, min);
	}
	return *this;
}

RingNode::~RingNode()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
