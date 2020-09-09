(c) Copyright, Real-Time Innovations, 2020.  All rights reserved.
RTI grants Licensee a license to use, modify, compile, and create derivative
works of the software solely for use with RTI Connext DDS. Licensee may
redistribute copies of the software provided that all such copies are subject
to this license. The software is provided "as is", with no warranty of any
type, including any warranty for fitness for any purpose. RTI is under no
obligation to maintain or support the software. RTI shall not be liable for
any incidental or consequential damages arising out of the use or inability
to use the software.
***

# Overview

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

# Before building

- It is assumed that you are working in a modern Linux / x64 environment
- It is assumed that your environment is properly configured to build Connext DDS Professional applications

A script is included as part of your installation to simplify this configuration.
From the terminal shell session in which you build, source the following script:

$ source <your install location>/rti_connext_dds-6.0.1/resource/scripts/rtisetenv_x64Linux4gcc7.3.0.bash

# Building this example:
 
 You may build/link with the Release or Debug versions of the Connext DDS 
 Professional libraries by setting the value of CMAKE_BUILD_TYPE 

$ git clone https://github.com/dgochenour/dds_pro_multi_topic.git
$ cd dds_pro_multi_topic
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=[Debug|Release] ..
$ make


# Run this Example:

1) Open two console (bash) windows. In each one...
2) Navigate to the dds_pro_multi_topic directory (you will see the USER_QOS_PROFILES.xml file there)
3) Run rtisetenv_x64Linux4gcc7.3.0.bash as you did in the build shell
4) Run the two generated applications, one per shell:
    - $ ./objs/x64Linux4gcc7.3.0/node_one 
    - $ ./objs/x64Linux4gcc7.3.0/node_two 

    - the applications can be stopped with Ctrl-C

# Current limitations

- In the interest of keeping the examples simple and single-threaded, listener callbacks are used to receive data
    - In most cases a better approach is to use a Waitset or simply poll
    - This example may be expanded in the future to show other options
