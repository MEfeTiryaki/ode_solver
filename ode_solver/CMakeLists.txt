# Specify the minimum version for CMake
cmake_minimum_required(VERSION 2.8)
project(ode_solver)

add_definitions("-std=c++11")

find_package(catkin REQUIRED COMPONENTS)
find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED  COMPONENTS system thread)

catkin_package(
	INCLUDE_DIRS
		include
	LIBRARIES
		${PROJECT_NAME} # exports the ode_solver lib to catkin_LIBRARIES
	CATKIN_DEPENDS
)


message(WARNING ${CATKIN_INCLUDE_DIRS})

include_directories(
	include
	${EIGEN3_INCLUDE_DIR}
	${Boost_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
	src/OdeSolver.cpp
	src/RungeKutta.cpp
	src/Euler.cpp
	src/EulerModified.cpp
	src/Simulator.cpp
)

target_link_libraries(
	${PROJECT_NAME}
  ${Boost_LIBRARIES}
)

message(WARNING ${CATKIN_PACKAGE_INCLUDE_DESTINATION})

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE)
