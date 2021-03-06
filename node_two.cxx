/*
* (c) Copyright, Real-Time Innovations, 2020.  All rights reserved.
* RTI grants Licensee a license to use, modify, compile, and create derivative
* works of the software solely for use with RTI Connext DDS. Licensee may
* redistribute copies of the software provided that all such copies are subject
* to this license. The software is provided "as is", with no warranty of any
* type, including any warranty for fitness for any purpose. RTI is under no
* obligation to maintain or support the software. RTI shall not be liable for
* any incidental or consequential damages arising out of the use or inability
* to use the software.
*/

/* 
This file is derived from code automatically generated by the rtiddsgen 
command:

rtiddsgen -language C++ -example <arch> type1.idl

Example publication of type my_app::type1 automatically generated by 
'rtiddsgen'. To test it, follow these steps:

(1) Compile this file and the example subscription.

(2) Start the subscription

(3) Start the publication

(4) [Optional] Specify the list of discovery initial peers and 
multicast receive addresses via an environment variable or a file 
(in the current working directory) called NDDS_DISCOVERY_PEERS. 

You can run any number of publisher and subscriber programs, and can 
add and remove them dynamically from the domain.

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// values used by node_one and node_two
#include "common.h"

// delete all entities
static int node_shutdown(DDS::DomainParticipant *participant) {
    
    DDS::ReturnCode_t retcode;
    int status = 0;

    if (participant != NULL) {
        retcode = participant->delete_contained_entities();
        if (retcode != DDS::RETCODE_OK) {
            std::cout << "delete_contained_entities error " << retcode << std::endl;
            status = DDS_RETCODE_ERROR;
        }

        retcode = TheParticipantFactory->delete_participant(participant);
        if (retcode != DDS::RETCODE_OK) {
            std::cout << "delete_participant error " << retcode << std::endl;
            status = -1;
        }
    }

    return status;
}

DDS::ReturnCode_t register_types(DDS::DomainParticipant *participant) {

    DDS::ReturnCode_t retcode = DDS::RETCODE_ERROR;

    // register the 4 data types that will be used by this application:
    retcode = my_app::type1TypeSupport::register_type(
            participant, 
            my_app::type1TypeSupport::get_type_name());
    if (retcode != DDS::RETCODE_OK) {
        std::cout << "register_type type1 error " << retcode << std::endl;
        return retcode;
    }
    retcode = my_app::type2TypeSupport::register_type(
            participant, 
            my_app::type2TypeSupport::get_type_name());
    if (retcode != DDS::RETCODE_OK) {
        std::cout << "register_type type2 error " << retcode << std::endl;
        return retcode;
    }
    retcode = my_app::type3TypeSupport::register_type(
            participant, 
            my_app::type3TypeSupport::get_type_name());
    if (retcode != DDS::RETCODE_OK) {
        std::cout << "register_type type3 error " << retcode << std::endl;
        return retcode;
    }
    retcode = my_app::type4TypeSupport::register_type(
            participant, 
            my_app::type4TypeSupport::get_type_name());
    if (retcode != DDS::RETCODE_OK) {
        std::cout << "register_type type4 error " << retcode << std::endl;
        return retcode;
    }

    return DDS::RETCODE_OK;
}

namespace my_app {

    class type1Listener : public DDS::DataReaderListener {
      public:
        virtual void on_requested_deadline_missed(
            DDS::DataReader* /*reader*/,
            const DDS::RequestedDeadlineMissedStatus& /*status*/) {}

        virtual void on_requested_incompatible_qos(
            DDS::DataReader* /*reader*/,
            const DDS::RequestedIncompatibleQosStatus& /*status*/) {}

        virtual void on_sample_rejected(
            DDS::DataReader* /*reader*/,
            const DDS::SampleRejectedStatus& /*status*/) {}

        virtual void on_liveliness_changed(
            DDS::DataReader* /*reader*/,
            const DDS::LivelinessChangedStatus& /*status*/) {}

        virtual void on_sample_lost(
            DDS::DataReader* /*reader*/,
            const DDS::SampleLostStatus& /*status*/) {}

        virtual void on_subscription_matched(
            DDS::DataReader* /*reader*/,
            const DDS::SubscriptionMatchedStatus& /*status*/) {}

        virtual void on_data_available(DDS::DataReader* reader);
    };

    class type2Listener : public DDS::DataReaderListener {
      public:
        virtual void on_requested_deadline_missed(
            DDS::DataReader* /*reader*/,
            const DDS::RequestedDeadlineMissedStatus& /*status*/) {}

        virtual void on_requested_incompatible_qos(
            DDS::DataReader* /*reader*/,
            const DDS::RequestedIncompatibleQosStatus& /*status*/) {}

        virtual void on_sample_rejected(
            DDS::DataReader* /*reader*/,
            const DDS::SampleRejectedStatus& /*status*/) {}

        virtual void on_liveliness_changed(
            DDS::DataReader* /*reader*/,
            const DDS::LivelinessChangedStatus& /*status*/) {}

        virtual void on_sample_lost(
            DDS::DataReader* /*reader*/,
            const DDS::SampleLostStatus& /*status*/) {}

        virtual void on_subscription_matched(
            DDS::DataReader* /*reader*/,
            const DDS::SubscriptionMatchedStatus& /*status*/) {}

        virtual void on_data_available(DDS::DataReader* reader);
    };

    void type1Listener::on_data_available(DDS::DataReader* reader)
    {
        my_app::type1DataReader *type1_reader = NULL;
        my_app::type1Seq data_seq;
        DDS::SampleInfoSeq info_seq;
        DDS::ReturnCode_t retcode;
        int i;

        type1_reader = my_app::type1DataReader::narrow(reader);
        if (type1_reader == NULL) {
            std::cout << "ERROR: DataReader narrow error" << std::endl;
            return;
        }

        retcode = type1_reader->take(
                data_seq, 
                info_seq, 
                DDS::LENGTH_UNLIMITED,
                DDS::ANY_SAMPLE_STATE, 
                DDS::ANY_VIEW_STATE, 
                DDS::ANY_INSTANCE_STATE);
        if (retcode == DDS::RETCODE_NO_DATA) {
            return;
        } else if (retcode != DDS::RETCODE_OK) {
            std::cout << "ERROR: take error " << retcode << std::endl;
            return;
        }

        for (i = 0; i < data_seq.length(); ++i) {
            if (info_seq[i].valid_data) {
                std::cout << "DATA: Received data" << std::endl;
                my_app::type1TypeSupport::print_data(&data_seq[i]);
            }
        }

        retcode = type1_reader->return_loan(data_seq, info_seq);
        if (retcode != DDS::RETCODE_OK) {
            std::cout << "ERROR: return loan error " << retcode << std::endl;
        }
    }

    void type2Listener::on_data_available(DDS::DataReader* reader)
    {
        my_app::type2DataReader *type2_reader = NULL;
        my_app::type2Seq data_seq;
        DDS::SampleInfoSeq info_seq;
        DDS::ReturnCode_t retcode;
        int i;

        type2_reader = my_app::type2DataReader::narrow(reader);
        if (type2_reader == NULL) {
            std::cout << "ERROR: DataReader narrow error" << std::endl;
            return;
        }

        retcode = type2_reader->take(
                data_seq, 
                info_seq, 
                DDS::LENGTH_UNLIMITED,
                DDS::ANY_SAMPLE_STATE, 
                DDS::ANY_VIEW_STATE, 
                DDS::ANY_INSTANCE_STATE);
        if (retcode == DDS::RETCODE_NO_DATA) {
            return;
        } else if (retcode != DDS::RETCODE_OK) {
            std::cout << "ERROR: take error " << retcode << std::endl;
            return;
        }

        for (i = 0; i < data_seq.length(); ++i) {
            if (info_seq[i].valid_data) {
                std::cout << "DATA: Received data" << std::endl;
                my_app::type2TypeSupport::print_data(&data_seq[i]);
            }
        }

        retcode = type2_reader->return_loan(data_seq, info_seq);
        if (retcode != DDS::RETCODE_OK) {
            std::cout << "ERROR: return loan error " << retcode << std::endl;
        }
    }
}

int node_two_main(int domainId, int sample_count)
{

    DDS::ReturnCode_t retcode;
    int count = 0;  
    DDS::Duration_t send_period = {1,0}; // sleep for 1s once per loop

    // create a single DomainParticipant-- in general, an application will 
    // require only 1 DP for each Domain in which it will participate
    DDS::DomainParticipant *participant = NULL;
    participant = TheParticipantFactory->create_participant(
            domainId, 
            DDS::PARTICIPANT_QOS_DEFAULT, 
            NULL /* listener */, 
            DDS::STATUS_MASK_NONE);
    if (participant == NULL) {
        std::cout << "create_participant error" << std::endl;
        node_shutdown(participant);
        return -1;
    }

    // create a single Publisher-- this Publisher can be used to create an 
    // arbitrary number of DataWriters
    DDS::Publisher *publisher = NULL;
    publisher = participant->create_publisher(
            DDS::PUBLISHER_QOS_DEFAULT, 
            NULL /* listener */, 
            DDS::STATUS_MASK_NONE);
    if (publisher == NULL) {
        std::cout << "create_publisher error" << std::endl;
        node_shutdown(participant);
        return -1;
    }

    // create a single Subscriber-- this Subscriber can be used to create an 
    // arbitrary number of DataReaders
    DDS::Subscriber *subscriber = NULL;
    subscriber = participant->create_subscriber(
            DDS::SUBSCRIBER_QOS_DEFAULT, 
            NULL /* listener */, 
            DDS::STATUS_MASK_NONE);
    if (subscriber == NULL) {
        std::cout << "create_subscriber error" << std::endl;
        node_shutdown(participant);
        return -1;
    }

    // register the 4 data types that will be used by this application
    if (register_types(participant) != DDS::RETCODE_OK) {
        std::cout << "register_types() error " << std::endl;
        node_shutdown(participant);
    };

    // create that Topics that will be used (either to publish to, or subscribe
    // from) in this application
    DDS::Topic *topic1 = NULL;
    topic1 = participant->create_topic(
            topic1_name,
            my_app::type1TypeSupport::get_type_name(), 
            DDS::TOPIC_QOS_DEFAULT, 
            NULL /* listener */,
            DDS::STATUS_MASK_NONE);
    if (topic1 == NULL) {
        std::cout << "create_topic topic1 error" << std::endl;
        node_shutdown(participant);
        return -1;
    }
    DDS::Topic *topic2 = NULL;
    topic2 = participant->create_topic(
            topic2_name,
            my_app::type2TypeSupport::get_type_name(), 
            DDS::TOPIC_QOS_DEFAULT, 
            NULL /* listener */,
            DDS::STATUS_MASK_NONE);
    if (topic2 == NULL) {
        std::cout << "create_topic topic2 error" << std::endl;
        node_shutdown(participant);
        return -1;
    }
    DDS::Topic *topic3 = NULL;
    topic3 = participant->create_topic(
            topic3_name,
            my_app::type3TypeSupport::get_type_name(), 
            DDS::TOPIC_QOS_DEFAULT, 
            NULL /* listener */,
            DDS::STATUS_MASK_NONE);
    if (topic3 == NULL) {
        std::cout << "create_topic topic3 error" << std::endl;
        node_shutdown(participant);
        return -1;
    }
    DDS::Topic *topic4 = NULL;
    topic4 = participant->create_topic(
            topic4_name,
            my_app::type4TypeSupport::get_type_name(), 
            DDS::TOPIC_QOS_DEFAULT, 
            NULL /* listener */,
            DDS::STATUS_MASK_NONE);
    if (topic4 == NULL) {
        std::cout << "create_topic topic4 error" << std::endl;
        node_shutdown(participant);
        return -1;
    }

    // create a DataWriter for use with topic3
    DDS::DataWriter *writer3 = NULL;
    writer3 = publisher->create_datawriter(
            topic3, 
            DDS::DATAWRITER_QOS_DEFAULT, 
            NULL /* listener */,
            DDS::STATUS_MASK_NONE);
    if (writer3 == NULL) {
        std::cout << "create_datawriter error" << std::endl;
        node_shutdown(participant);
        return -1;
    }
    // narrow (cast) the DW to be specific to type3, which is the data type of
    // topic3
    my_app::type3DataWriter * topic3_writer = NULL;
    topic3_writer = my_app::type3DataWriter::narrow(writer3);
    if (topic3_writer == NULL) {
        std::cout << "topic3_writer narrow error" << std::endl;
        node_shutdown(participant);
        return -1;
    }
    // create a type3 data sample for writing to Topic3
    my_app::type3 *instance3 = NULL;
    instance3 = my_app::type3TypeSupport::create_data();
    if (instance3 == NULL) {
        std::cout << "my_app::type3TypeSupport::create_data error" << std::endl;
        node_shutdown(participant);
        return -1;
    }
    
    // create a DataWriter for use with topic4
    DDS::DataWriter *writer4 = NULL;
    writer4 = publisher->create_datawriter(
            topic4, 
            DDS::DATAWRITER_QOS_DEFAULT, 
            NULL /* listener */,
            DDS::STATUS_MASK_NONE);
    if (writer4 == NULL) {
        std::cout << "create_datawriter error" << std::endl;
        node_shutdown(participant);
        return -1;
    }
    // narrow (cast) the DW to be specific to type4, which is the data type of
    // topic4
    my_app::type4DataWriter * topic4_writer = NULL;
    topic4_writer = my_app::type4DataWriter::narrow(writer4);
    if (topic4_writer == NULL) {
        std::cout << "topic4_writer narrow error" << std::endl;
        node_shutdown(participant);
        return -1;
    }
    // create a type4 data sample for writing to Topic4
    my_app::type4 *instance4 = NULL;
    instance4 = my_app::type4TypeSupport::create_data();
    if (instance4 == NULL) {
        std::cout << "my_app::type4TypeSupport::create_data error" << std::endl;
        node_shutdown(participant);
        return -1;
    }

    /* Create a listener for reader1 */
    my_app::type1Listener *reader1_listener = NULL; 
    reader1_listener = new my_app::type1Listener();

    // create a DataReader for use with topic1
    DDS::DataReader *reader1 = NULL;
    reader1 = subscriber->create_datareader(
            topic1, 
            DDS::DATAREADER_QOS_DEFAULT, 
            reader1_listener,
            DDS::STATUS_MASK_ALL);
    if (reader1 == NULL) {
        std::cout << "create_datareader error" << std::endl;
        node_shutdown(participant);
        delete reader1_listener;
        return -1;
    }

    /* Create a listener for reader2 */
    my_app::type2Listener *reader2_listener = NULL; 
    reader2_listener = new my_app::type2Listener();

    // create a DataReader for use with topic2
    DDS::DataReader *reader2 = NULL;
    reader2 = subscriber->create_datareader(
            topic2, 
            DDS::DATAREADER_QOS_DEFAULT, 
            reader2_listener,
            DDS::STATUS_MASK_ALL);
    if (reader2 == NULL) {
        std::cout << "create_datareader error" << std::endl;
        node_shutdown(participant);
        delete reader2_listener;
        return -1;
    }

    DDS::InstanceHandle_t instance_handle = DDS::HANDLE_NIL;

    // main loop
    for (count=0; (sample_count == 0) || (count < sample_count); ++count) {

        // In each pass through the loop, we will write one sample each to 
        // topic3 and topic 4. This example application is receiving samples on
        // topic1 and topic2 by using listener callbacks... so there is no 
        // code to read in this loop.
        
        std::cout << "Writing to topic3, count " << count << std::endl;
        instance3->id = 108;                // arbitrary value
        instance3->value = (0.7 * count);   // arbitrary value
        retcode = topic3_writer->write(*instance3, instance_handle);
        if (retcode != DDS::RETCODE_OK) {
            std::cout << "write error " << retcode << std::endl;
        }

        // write to topic4
        std::cout << "Writing to topic4, count " << count << std::endl;
        instance4->id = 270;        // arbitrary value
        instance4->value = count;   // arbitrary value
        retcode = topic4_writer->write(*instance4, instance_handle);
        if (retcode != DDS::RETCODE_OK) {
            std::cout << "write error " << retcode << std::endl;
        }

        NDDSUtility::sleep(send_period);
    }

    // delete the data samples created earlier
    retcode = my_app::type3TypeSupport::delete_data(instance3);
    if (retcode != DDS::RETCODE_OK) {
        std::cout << "my_app::type3TypeSupport::delete_data error " << retcode
                << std::endl;
    }
    retcode = my_app::type4TypeSupport::delete_data(instance4);
    if (retcode != DDS::RETCODE_OK) {
        std::cout << "my_app::type4TypeSupport::delete_data error " << retcode
                << std::endl;
    }

    // delete the listeners created earlier
    delete reader1_listener;
    delete reader2_listener;

    /* Delete all entities */
    return node_shutdown(participant);
}

int main(int argc, char *argv[])
{
    int domain_id = 0;
    int sample_count = 0; /* infinite loop */

    if (argc >= 2) {
        domain_id = atoi(argv[1]);
    }
    if (argc >= 3) {
        sample_count = atoi(argv[2]);
    }

    return node_two_main(domain_id, sample_count);
}

