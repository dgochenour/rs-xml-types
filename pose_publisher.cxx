// (c) Copyright, Real-Time Innovations, 2022.  All rights reserved.
// RTI grants Licensee a license to use, modify, compile, and create derivative
// works of the software solely for use with RTI Connext DDS. Licensee may
// redistribute copies of the software provided that all such copies are subject
// to this license. The software is provided "as is", with no warranty of any
// type, including any warranty for fitness for any purpose. RTI is under no
// obligation to maintain or support the software. RTI shall not be liable for
// any incidental or consequential damages arising out of the use or inability
// to use the software.

#include <iostream>
#include <cstdlib>

#include <rti/rti.hpp>

#include "generated/Pose.hpp"

int main(int argc, char *argv[]) {

    dds::domain::DomainParticipant participant(0);
    dds::topic::Topic<don::Pose> topic(participant, don::pose_topic_name);
    dds::pub::Publisher publisher(participant);

    // Create a DataWriter with default QoS
    dds::pub::DataWriter<don::Pose> writer(publisher, topic);

    don::Pose data;
    // Main loop, write data

    int samples_written = 0;
    
    while (1) {

        data.obj_id(samples_written % 3);
        data.position().x(std::rand());
        data.position().y(std::rand());
        data.position().z(std::rand());

        data.orientation().x(std::rand());
        data.orientation().y(std::rand());
        data.orientation().z(std::rand());
        data.orientation().w(std::rand());

        std::cout << "Writing don::Pose, count " << samples_written++ << std::endl;

        writer.write(data);

        // Send once every second
        rti::util::sleep(dds::core::Duration(0, 100000000));
    }
}
