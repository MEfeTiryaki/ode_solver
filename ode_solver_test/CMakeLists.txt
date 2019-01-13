# Specify the minimum version for CMake
cmake_minimum_required(VERSION 2.8)
project(ode_solver_test)

add_definitions("-std=c++11")

find_package(catkin REQUIRED
	COMPONENTS
		ode_solver
		plotgui
)

find_package(Eigen3 REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Boost REQUIRED  COMPONENTS system)

catkin_package(
	INCLUDE_DIRS
	LIBRARIES
	CATKIN_DEPENDS
		ode_solver
		plotgui
	DEPENDS
)
message(WARNING ${catkin_INCLUDE_DIRS})

include_directories(
	include
	${EIGEN3_INCLUDE_DIR}
  ${catkin_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
	${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(pendulum_test
	src/pendulum_test.cpp
)

target_link_libraries(pendulum_test
  #${PROJECT_NAME}
	${catkin_LIBRARIES}
  ${Qt5Widgets_LIBRARIES}
	${Boost_LIBRARIES}
)

add_executable(pendulum_scope_test
	src/pendulumScope_test.cpp
)

target_link_libraries(pendulum_scope_test
  #${PROJECT_NAME}
	${catkin_LIBRARIES}
  ${Qt5Widgets_LIBRARIES}
	${Boost_LIBRARIES}
)





#install(DIRECTORY include/${PROJECT_NAME}/
#  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#  FILES_MATCHING PATTERN "*.h"
#  PATTERN ".svn" EXCLUDE)
