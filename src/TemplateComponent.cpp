/** 
 * Author: Dennis Leroy Wigand
 * Date:   28 Feb 2017
 *
 */

#include "TemplateComponent.hpp"
#include <rtt/Component.hpp> // needed for the macro at the end of this file


TemplateComponent::TemplateComponent(std::string const & name) : RTT::TaskContext(name) {
    //addOperation("setDOFsizeAndTransitionTime", &TemplateComponent::setDOFsizeAndTransitionTime, this).doc("set DOF size and transition time");
    startTime = 0.0;
}

bool TemplateComponent::configureHook() {
    return true;
}

bool TemplateComponent::startHook() {
    startTime = this->getSimulationTime();
    return true;
}

void TemplateComponent::updateHook() {
    // this is the actual body of a component. it is called on each cycle
    // if (in_torquesA_port.connected() && in_torquesB_port.connected()) {
    //     // read data and save state of data into "Flow", which can be "NewData", "OldData" or "NoData".
    //     in_torquesA_flow = in_torquesA_port.read(in_torquesA_var);
    //     in_torquesB_flow = in_torquesB_port.read(in_torquesB_var);
    // }

    // out_torques_port.write(out_torques_var);
}

void TemplateComponent::stopHook() {
}

void TemplateComponent::cleanupHook() {
}

// void TemplateComponent::preparePorts(){
//     if (portsArePrepared){
//         ports()->removePort("in_torquesA_port");
//         ports()->removePort("in_torquesB_port");
//         ports()->removePort("out_torques_port");
//     }

//     //prepare input
//     in_torquesA_var = rstrt::dynamics::JointTorques(DOFsize);
//     in_torquesA_port.setName("in_torquesA_port");
//     in_torquesA_port.doc("Input port for reading torquesA values");
//     ports()->addPort(in_torquesA_port);
//     in_torquesA_flow = RTT::NoData;

//     in_torquesB_var = rstrt::dynamics::JointTorques(DOFsize);
//     in_torquesB_port.setName("in_torquesB_port");
//     in_torquesB_port.doc("Input port for reading torquesB values");
//     ports()->addPort(in_torquesB_port);
//     in_torquesB_flow = RTT::NoData;

//     //prepare output
//     out_torques_var = rstrt::dynamics::JointTorques(DOFsize);
//     out_torques_var.torques.setZero();
//     out_torques_port.setName("out_torques_port");
//     out_torques_port.doc("Output port for sending torque values");
//     out_torques_port.setDataSample(out_torques_var);
//     ports()->addPort(out_torques_port);

//     portsArePrepared = true;
// }

double TemplateComponent::getSimulationTime() {
    return 1E-9 * RTT::os::TimeService::ticks2nsecs(RTT::os::TimeService::Instance()->getTicks());
}

//this macro should appear only once per library
ORO_CREATE_COMPONENT_LIBRARY()

// This macro, as you can see, creates the component. Every component should have this!
ORO_LIST_COMPONENT_TYPE(TemplateComponent)
