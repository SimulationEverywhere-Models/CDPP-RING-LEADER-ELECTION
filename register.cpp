/*******************************************************************
*
*  Auto Generated File
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  This registration file is used to describe the atomic models that can be used to compose coupled models.
*
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "RingNode.h"        // class RingNode

void MainSimulator::registerNewAtomics()
{
	// Register Built-in models

	// Register custom models
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<RingNode>(), "RingNode" ) ;
}
