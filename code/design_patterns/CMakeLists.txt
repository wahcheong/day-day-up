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

# Abstract Factory Pattern
set(ABSTRACT_FACTORY_SOURCES
    creational/abstract_factory/abstract_factory.cpp
    creational/abstract_factory/demo.cpp
)
add_executable(abstract_factory_demo ${ABSTRACT_FACTORY_SOURCES})
target_include_directories(abstract_factory_demo PRIVATE creational/abstract_factory)

# Builder Pattern
set(BUILDER_SOURCES
    creational/builder/builder.cpp
    creational/builder/demo.cpp
)
add_executable(builder_demo ${BUILDER_SOURCES})
target_include_directories(builder_demo PRIVATE creational/builder)

# Prototype Pattern
set(PROTOTYPE_SOURCES
    creational/prototype/prototype.cpp
    creational/prototype/demo.cpp
)
add_executable(prototype_demo ${PROTOTYPE_SOURCES})
target_include_directories(prototype_demo PRIVATE creational/prototype)

# Adapter Pattern
set(ADAPTER_SOURCES
    structural/adapter/adapter.cpp
    structural/adapter/demo.cpp
)
add_executable(adapter_demo ${ADAPTER_SOURCES})
target_include_directories(adapter_demo PRIVATE structural/adapter)

# Bridge Pattern
set(BRIDGE_SOURCES
    structural/bridge/bridge.cpp
    structural/bridge/demo.cpp
)
add_executable(bridge_demo ${BRIDGE_SOURCES})
target_include_directories(bridge_demo PRIVATE structural/bridge)
