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
	// TODO get Peers and set SlaveActivity for them!

	// RTT::TaskContext *new_block = this->getPeer(block_name);
	// // Set the block's activity to be a slave to the scheme's
	// new_block->setActivity(
	// 	new RTT::extras::SlaveActivity(
	// 		this->getActivity(),
	// 		new_block->engine()));

	return true;
}

bool Master::startHook()
{
	startTime = this->getSimulationTime();
	return true;
}

void Master::updateHook()
{

	RTT::log(RTT::Error) << this->getName() << " >> in_A_var: " << in_A_var << ", in_B_var: " << in_B_var << RTT::endlog();

	out_nAB_port.write(!(in_A_var && in_B_var));

	// In this case it also works if connections are lost!
	in_A_flow = in_A_port.read(in_A_var);
	in_B_flow = in_B_port.read(in_B_var);

	if (in_A_flow == RTT::NoData)
	{
		in_A_var = false;
	}

	if (in_B_flow == RTT::NoData)
	{
		in_B_var = false;
	}
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
