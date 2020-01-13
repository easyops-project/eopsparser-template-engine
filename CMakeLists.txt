cmake_minimum_required(VERSION 3.15)

project(eopstemplateengine) # setting the project name

add_definitions(-DNAPI_VERSION=4) # adding NAPI V4 Def

# add library files
include_directories(lib/EasyOps-Native-Lib/include) #include the native lib
include_directories(lib/nlohmann) #include the native lib
add_subdirectory(lib/EasyOps-Native-Lib)

# setup Source Files
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp") # add all source files
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} eopslibrary)


#add stuff
add_definitions("-DAWS_INSTANCES=\"${CMAKE_SOURCE_DIR}/src/Models/AWS/EC2/Assets/InstanceType.json\"")
add_definitions("-DAZURE_WINDOWS_INSTANCES=\"${CMAKE_SOURCE_DIR}/src/Models/Azure/Compute/Assets/WindowsInstanceType.json\"")
add_definitions("-DAZURE_LINUX_INSTANCES=\"${CMAKE_SOURCE_DIR}/src/Models/Azure/Compute/Assets/LinuxInstanceType.json\"")
add_definitions("-DAZURE_OS_IMAGES=\"${CMAKE_SOURCE_DIR}/src/Models/Azure/Compute/Assets/OsImages.json\"")

# set properties
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node") #set target property to .node

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