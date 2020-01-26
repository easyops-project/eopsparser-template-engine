cmake_minimum_required(VERSION 3.15)

project(eopstemplateengine) # setting the project name

add_definitions(-DNAPI_VERSION=4) # adding NAPI V4 Def

# add curl
#set(CURL_LIBRARY "-lcurl") 
#find_package(CURL REQUIRED) 
#include_directories(${CURL_INCLUDE_DIR})

# add library files
include_directories(lib/EasyOps-Native-Lib/include) #include the native lib
include_directories(lib/nlohmann) #include the native lib
include_directories(lib/http) #include the native lib
add_subdirectory(lib/EasyOps-Native-Lib)

# setup Source Files
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp") # add all source files
list(REMOVE_ITEM SOURCE_FILES "src/handler.cpp")
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} eopslibrary)
#target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})

#add stuff

#aws
add_definitions("-DAWS_INSTANCES=\"${CMAKE_SOURCE_DIR}/assets/AWSAssets/InstanceType.json\"")
add_definitions("-DAWS_AVAILABILITY_ZONES=\"${CMAKE_SOURCE_DIR}/assets/AWSAssets/AvailabilityZoneLocations.json\"")
add_definitions("-DAWS_OS_AMI_CACHE=\"${CMAKE_SOURCE_DIR}/assets/AWSAssets/AwsOSAMICache.json\"")

#azure
add_definitions("-DAZURE_WINDOWS_INSTANCES=\"${CMAKE_SOURCE_DIR}/assets/AzureAssets/WindowsInstanceType.json\"")
add_definitions("-DAZURE_LINUX_INSTANCES=\"${CMAKE_SOURCE_DIR}/assets/AzureAssets/LinuxInstanceType.json\"")
add_definitions("-DAZURE_OS_IMAGES=\"${CMAKE_SOURCE_DIR}/assets/AzureAssets/OsImages.json\"")
add_definitions("-DAZURE_AVAILABILITY_ZONES=\"${CMAKE_SOURCE_DIR}/assets/AzureAssets/AzureAvailabilityZones.json\"")

# set properties
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".so") #set target property to .node

#includes
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/node_modules/node-addon-api ${CMAKE_JS_INC}) # include node addon api and js
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB}) # link the CMAKEJSLIB

##aws sdk
#find_package(AWSSDK REQUIRED COMPONENTS ec2)
#target_link_libraries(${PROJECT_NAME} ${AWSSDK_LINK_LIBRARIES})

# adding node-addon-api
execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})

add_library(wrapped SHARED src/handler.cpp)
target_link_libraries(wrapped ${PROJECT_NAME})
target_link_libraries(wrapped ${CMAKE_JS_LIB}) # link the CMAKEJSLIB
target_include_directories(wrapped PRIVATE ${CMAKE_SOURCE_DIR}/node_modules/node-addon-api ${CMAKE_JS_INC}) # include node addon api and js
set_target_properties(wrapped PROPERTIES PREFIX "" SUFFIX ".node") #set target property to .node


