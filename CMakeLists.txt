cmake_minimum_required(VERSION 3.15)
project(compiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(compiler main.cpp Lexer.cpp Lexer.h Parser.cpp Parser.h Generator.cpp Generator.h Node.cpp Node.h VirtualMachine.cpp VirtualMachine.h ObjectCode.cpp ObjectCode.h)