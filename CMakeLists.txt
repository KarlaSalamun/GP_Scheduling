cmake_minimum_required(VERSION 3.15)
project(GP_scheduling)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/include/python2.7/)
find_package(Python2 COMPONENTS Development NumPy)
link_libraries(Python2::Python Python2::NumPy)

add_executable(GP_scheduling main.cpp
        CrossoverOperator.cpp CrossoverOperator.h
        GeneticAlgorithm.h GeneticAlgorithm.cpp
        MutationOperator.h MutationOperator.cpp
        SelectionOperator.h SelectionOperator.cpp
        Solution.h Solution.cpp
        TreeMutation.h TreeMutation.cpp
        TreeSelection.h TreeSelection.cpp
        TreeCrossover.h TreeCrossover.cpp
        TreeSolution.h TreeSolution.cpp
        TreeConstructor.h TreeConstructor.cpp
        Nodes/AbstractNode.h Nodes/AbstractNode.cpp
        ../function.h ../function.cpp
        GPEvaluateHeuristic.h GPEvaluateHeuristic.cpp
        TaskCreator.h TaskCreator.cpp
        Task.h Task.cpp
        Nodes/AddNode.cpp Nodes/AddNode.h
        Nodes/ddNode.cpp Nodes/ddNode.h
        Nodes/DivNode.cpp Nodes/DivNode.h
        Nodes/MulNode.cpp Nodes/MulNode.h
        Nodes/NrNode.cpp Nodes/NrNode.h
        Nodes/PosNode.cpp Nodes/PosNode.h
        Nodes/ptNode.cpp Nodes/ptNode.h
        Nodes/SDNode.h Nodes/SDNode.cpp
        Nodes/SPrNode.cpp
        Nodes/SubNode.cpp
        Nodes/WNode.cpp
        Heuristics/SchedulingHeuristic.h Heuristics/SchedulingHeuristic.cpp
        Heuristics/RMHeuristic.h Heuristics/RMHeuristic.cpp
        Heuristics/EvaluateHeuristic.cpp Heuristics/EvaluateHeuristic.h
        Heuristics/MONHeuristic.cpp Heuristics/MONHeuristic.h
        Heuristics/WSPTHeuristic.cpp Heuristics/WSPTHeuristic.h
        Heuristics/EDDHeuristic.cpp Heuristics/EDDHeuristic.h
        Heuristics/HODGHeuristic.cpp Heuristics/HODGHeuristic.h
        matplotlibcpp.h)
