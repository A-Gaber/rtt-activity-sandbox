/** 
 * Author: Dennis Leroy Wigand
 * Date:   28 Feb 2017
 *
 */

#pragma once

#include <rtt/Port.hpp>
#include <rtt/TaskContext.hpp>
#include <string>

#include <rst-rt/robot/JointState.hpp>
#include <rst-rt/dynamics/JointTorques.hpp>
#include <boost/lexical_cast.hpp>

class TemplateComponent: public RTT::TaskContext {
public:
    TemplateComponent(std::string const & name);

    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();

    double getSimulationTime();

private:
    // // Declare input ports and their datatypes
    // RTT::InputPort<rstrt::dynamics::JointTorques> in_torquesA_port;

    // // Declare output ports and their datatypes
    // RTT::OutputPort<rstrt::dynamics::JointTorques> out_torques_port;

    // // Data flow:
    // RTT::FlowStatus in_torquesA_flow;

    // // variables
    // rstrt::dynamics::JointTorques in_torquesA_var;
    // rstrt::dynamics::JointTorques out_torques_var;
    double startTime;
};

