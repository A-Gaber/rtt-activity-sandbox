/** 
 * Author: Dennis Leroy Wigand
 * Date:   10 Jul 2018
 *
 */

#include "Master.hpp"
#include <rtt/Component.hpp> // needed for the macro at the end of this file

#include <stdio.h>
#include <rtt/extras/SlaveActivity.hpp>

Master::Master(std::string const &name) : RTT::TaskContext(name), portsArePrepared(false), in_A_var(false), in_B_var(
																												false),
										  out_nAB_var(false)
{
	startTime = 0.0;
}

bool Master::configureHook()
{
	std::vector<std::string> peerList = this->getPeerList();
	for (auto peerName : peerList)
	{
		RTT::TaskContext *new_block = this->getPeer(peerName);
		if (new_block)
		{
			RTT::log(RTT::Warning) << this->getName() << " set SLAVE activity for " << peerName << RTT::endlog();
			new_block->setActivity(
				new RTT::extras::SlaveActivity(
					this->getActivity(),
					new_block->engine()));
			tcList.push_back(new_block);
		}
	}
	R = this->getPeer("R");
	S = this->getPeer("S");
	return true;
}

bool Master::startHook()
{
	startTime = this->getSimulationTime();
	RTT::log(RTT::Warning) << this->getName() << "started" << RTT::endlog();
	return true;
}

void Master::updateHook()
{

	RTT::log(RTT::Warning) << this->getName() << "update start" << RTT::endlog();

	// out_nAB_port.write(!(in_A_var && in_B_var));
	// for (RTT::TaskContext *tc : tcList)
	// {
	// 	tc->update();
	// }
	if (S)
	{
		// TODO seems like update() is blocking...!
		S->update();

		// With own Activities and this line below we can have a non-blocking parallel execution
		// S->trigger();
		// S->getActivity()->start();

		// With own Activities and this line below we can have a sequential execution
		// S->engine()->activate();
	}
	if (R)
	{
		R->update();

		// With own Activities and this line below we can have a non-blocking parallel execution
		// R->trigger();
		// R->getActivity()->start();

		// With own Activities and this line below we can have a sequential execution
	}
	// // In this case it also works if connections are lost!
	// in_A_flow = in_A_port.read(in_A_var);
	// in_B_flow = in_B_port.read(in_B_var);

	// if (in_A_flow == RTT::NoData)
	// {
	// 	in_A_var = false;
	// }

	// if (in_B_flow == RTT::NoData)
	// {
	// 	in_B_var = false;
	// }
	RTT::log(RTT::Warning) << this->getName() << "update end" << RTT::endlog();
}

void Master::stopHook()
{
}

void Master::cleanupHook()
{
}

void Master::preparePorts()
{
	in_A_port.setName("in_A_port");
	in_A_port.doc("Input port A");
	ports()->addPort(in_A_port);
	in_A_flow = RTT::NoData;

	in_B_port.setName("in_B_port");
	in_B_port.doc("Input port B");
	ports()->addPort(in_B_port);
	in_B_flow = RTT::NoData;

	out_nAB_var = false;
	out_nAB_port.setName("out_nAB_port");
	out_nAB_port.doc("Output port Q");
	out_nAB_port.setDataSample(!false);
	ports()->addPort(out_nAB_port);

	portsArePrepared = true;
}

double Master::getSimulationTime()
{
	return 1E-9 * RTT::os::TimeService::ticks2nsecs(
					  RTT::os::TimeService::Instance()->getTicks());
}

//this macro should appear only once per library
ORO_CREATE_COMPONENT_LIBRARY()
// This macro, as you can see, creates the component. Every component should have this!
ORO_LIST_COMPONENT_TYPE(Master)
