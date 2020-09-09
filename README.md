================================================================================
(c) Copyright, Real-Time Innovations, 2020.  All rights reserved.
RTI grants Licensee a license to use, modify, compile, and create derivative
works of the software solely for use with RTI Connext DDS. Licensee may
redistribute copies of the software provided that all such copies are subject
to this license. The software is provided "as is", with no warranty of any
type, including any warranty for fitness for any purpose. RTI is under no
obligation to maintain or support the software. RTI shall not be liable for
any incidental or consequential damages arising out of the use or inability
to use the software.
================================================================================

This example is comprised of two applications, "node_one" and "node_two", that
each access four Topics. Each Topic has a unique data type for four user-defined
types total in use.

- node_one

    - publishes data to "Topic 1" (of my_app::type1)
    - publishes data to "Topic 2" (of my_app::type2)
    - subscribes to "Topic 3" (of my_app::type3)
    - subscribes to "Topic 4" (of my_app::type4)

- node_two

    - publishes data to "Topic 3" (of my_app::type3)
    - publishes data to "Topic 4" (of my_app::type4)
    - subscribes to "Topic 1" (of my_app::type1)
    - subscribes to "Topic 2" (of my_app::type2)

The primary purpose of this example is to demonstrate how to implement any 
arbitrary number of endpoints (DataReaders and DataWriters) in a single 
application using a single DomainParticipant

To Build this example:
======================
 
$ git clone 

To Modify the Data:
===================
To modify the data being sent, edit the type1_publisher.cxx
file where it says:
/* Modify the instance to be written here */

To Run this Example:
====================
Make sure you are in the directory where the USER_QOS_PROFILES.xml file was
generated (the same directory this README file is in).
Run /home/don/rti_connext_dds-6.0.1/resource/scripts/rtisetenv_x64Linux4gcc7.3.0.bash
to make sure the Connext libraries are in the path, especially if you opened
a new command prompt window.
Run the publishing or subscribing application by typing:
> objs/x64Linux4gcc7.3.0/node_one <domain_id> <sample_count>
> objs/x64Linux4gcc7.3.0/node_two <domain_id> <sample_count>
