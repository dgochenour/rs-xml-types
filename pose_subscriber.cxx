// (c) Copyright, Real-Time Innovations, 2022.  All rights reserved.
// RTI grants Licensee a license to use, modify, compile, and create derivative
// works of the software solely for use with RTI Connext DDS. Licensee may
// redistribute copies of the software provided that all such copies are subject
// to this license. The software is provided "as is", with no warranty of any
// type, including any warranty for fitness for any purpose. RTI is under no
// obligation to maintain or support the software. RTI shall not be liable for
// any incidental or consequential damages arising out of the use or inability
// to use the software.

#include <algorithm>
#include <iostream>

#include <rti/rti.hpp>

#include "generated/Pose.hpp"

int process_data(dds::sub::DataReader<don::Pose> reader) {

    int count = 0;
    dds::sub::LoanedSamples<don::Pose> samples = reader.take();
    for (const auto& sample : samples) {
        if (sample.info().valid()) {
            count++;
            std::cout << sample.data() << std::endl;
        } else {
            std::cout << "Instance state changed to "
            << sample.info().state().instance_state() << std::endl;
        }
    }

    return count; 
} 

int main(int argc, char *argv[]) {

    dds::domain::DomainParticipant participant(0);
    dds::topic::Topic<don::Pose> topic(participant, don::pose_topic_name);
    dds::sub::Subscriber subscriber(participant);
    dds::sub::DataReader<don::Pose> reader(subscriber, topic);

    unsigned int samples_read = 0;
    dds::sub::cond::ReadCondition read_condition(
        reader,
        dds::sub::status::DataState::any(),
        [reader, &samples_read]() { samples_read += process_data(reader); });

    dds::core::cond::WaitSet waitset;
    waitset += read_condition;

    while (1) {
        std::cout << "don::Pose DataReader sleeping up to 1 sec..." << std::endl;

        // Run the handlers of the active conditions. Wait for up to 1 second.
        waitset.dispatch(dds::core::Duration(1));
    }
}