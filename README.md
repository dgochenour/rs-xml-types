# Using XML-defined Types with RTI Routing Service

## Description

This example demonstrates how XML type definition can be used in an RTI Routing Service configuration. CUrrently, the example includes type definitions in the Routing Serivce configuration XML file. The eventual goal is to be able to include `rtiddsgen`-generated XML type definitions as external files; however, this goal must wait until 6he Connext Professional 6.1.2 maintenance release.


The repo contains three main components:
- `pose_publisher` 
    - Simple DDS application that publishes samples of type `Pose` to the Topic `Pose Topic` in **Domain 0**
- `pose_subscriber`
    - Simple DDS application that subscribes to the Topic `Pose Topic` in **Domain 1**
- `rs-config.xml`
    - RTI Routing Service configuration file to route the `Pose Topic` Topic between **Domain 0** and **Domain 1**

## Assumptions

The `NDDSHOME` environment valiable must be set. Every RTI Connext Professional installation includes a script to accomplish this.
```
<INSTALL DIR>/rti_connext_dds-6.1.1/resource/scripts/rtisetenv_<ARCHITECTURE>.bash 
```
This document assumes that this will be called in the repo's base directory. For example, on MacOS:
```
cd rs-xml-types
source /Applications/rti_connext_dds-6.1.1/resource/scripts/rtisetenv_x64Darwin17clang9.0.bash 
```
## Generating Type-support code

From the repo base directory:
```
./generate_type_support.sh
```
## Building the DDS applications
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```
The resulting executables can be found in the `objs/<ARCHITECTURE>` directory.

## Running the applications and starting Routing Service

Open 3 terminal sessions and set the `NDDSHOME` environment valiable in each as described above. 

### In terminal #1
- Start the publisher
```
cd rs-xml-types
./objs/x64Darwin17clang9.0/pose_publisher
```
### In terminal #2
- Start the subscriber
```
cd rs-xml-types
./objs/x64Darwin17clang9.0/pose_publisher
```
### In terminal #3
- Start the Routing Service instance
```
cd rs-xml-types
$NDDSHOME/bin/rtiroutingservice -cfgFile "rs-config.xml" -cfgName PoseBothWays
```