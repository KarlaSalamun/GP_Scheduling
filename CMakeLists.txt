cmake_minimum_required(VERSION 3.15)
project(GP_scheduling)

set(CMAKE_CXX_STANDARD 14)

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
        EvaluateHeuristic.h EvaluateHeuristic.cpp
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
        Nodes/WNode.cpp)