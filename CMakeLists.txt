cmake_minimum_required(VERSION 3.10)
project(GP_scheduling LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror")

find_package(PythonInterp)
find_package(PythonLibs)
message(STATUS "PYTHON_LIBRARIES = ${PYTHON_LIBRARIES}")
include_directories(${PYTHON_INCLUDE_DIRS})

include_directories(include)
include_directories(include/Heuristics)
include_directories(include/Nodes)
include_directories(include/Nodes/TreeOperators)
include_directories(periodic_tasks_simulator/include)

add_executable(GP_scheduling main.cpp
		src/Heuristics/EDDHeuristic.cpp       
		src/Heuristics/HODGHeuristic.cpp  
		src/Heuristics/RMHeuristic.cpp          
		src/Heuristics/WSPTHeuristic.cpp
		src/Heuristics/EvaluateHeuristic.cpp
		src/Heuristics/MONHeuristic.cpp   
		src/Heuristics/SchedulingHeuristic.cpp
		src/Nodes/AbstractNode.cpp  
		src/Nodes/DivNode.cpp  
		src/Nodes/PosNode.cpp  
		src/Nodes/SLNode.cpp   
		src/Nodes/TreeConstructor.cpp  
		src/Nodes/WNode.cpp
		src/Nodes/AddNode.cpp       
		src/Nodes/MulNode.cpp  
		src/Nodes/ptNode.cpp   
		src/Nodes/SPrNode.cpp  
		src/Nodes/ddNode.cpp        
		src/Nodes/NrNode.cpp   
		src/Nodes/SDNode.cpp   
		src/Nodes/SubNode.cpp  
		src/Nodes/TreeOperators/CrossoverOperator.cpp  
		src/Nodes/TreeOperators/SelectionOperator.cpp  
		src/Nodes/TreeOperators/MutationOperator.cpp   
		src/function.cpp
		src/optimization_function.cpp)


add_subdirectory( periodic_tasks_simulator )
target_link_libraries( GP_scheduling periodic_simulator )
target_link_libraries(GP_scheduling ${PYTHON_LIBRARIES})
