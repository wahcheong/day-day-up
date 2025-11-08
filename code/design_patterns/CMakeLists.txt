cmake_minimum_required(VERSION 3.14)
project(DesignPatterns LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Singleton Pattern
set(SINGLETON_SOURCES
    creational/singleton/singleton.cpp
    creational/singleton/demo.cpp
)
add_executable(singleton_demo ${SINGLETON_SOURCES})
target_include_directories(singleton_demo PRIVATE creational/singleton)


# Simple Factory Pattern
set(SIMPLE_FACTORY_SOURCES
    creational/simple_factory/simple_factory.cpp
    creational/simple_factory/demo.cpp
)
add_executable(simple_factory_demo ${SIMPLE_FACTORY_SOURCES})
target_include_directories(simple_factory_demo PRIVATE creational/simple_factory)

# Factory Method Pattern
set(FACTORY_METHOD_SOURCES
    creational/factory_method/factory_method.cpp
    creational/factory_method/demo.cpp
)
add_executable(factory_method_demo ${FACTORY_METHOD_SOURCES})
target_include_directories(factory_method_demo PRIVATE creational/factory_method)
