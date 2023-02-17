set(target mtfind)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

file(GLOB sources
    ${CMAKE_CURRENT_SOURCE_DIR}/common/config_reader.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/config_reader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/common/safe_queue.h
    ${CMAKE_CURRENT_SOURCE_DIR}/common/logger.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/logger.h

    ${CMAKE_CURRENT_SOURCE_DIR}/daemonizer/service.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/daemonizer/service.h
    ${CMAKE_CURRENT_SOURCE_DIR}/daemonizer/daemon.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/daemonizer/daemon.h

    ${CMAKE_CURRENT_SOURCE_DIR}/parse_worker.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/parse_worker.h
    ${CMAKE_CURRENT_SOURCE_DIR}/write_worker.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/write_worker.h
    ${CMAKE_CURRENT_SOURCE_DIR}/read_worker.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/read_worker.h
    ${CMAKE_CURRENT_SOURCE_DIR}/application.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/application.h

    ${CMAKE_CURRENT_SOURCE_DIR}/settings.h
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cc)

add_executable(${target} ${sources})

target_include_directories(${target}
     PRIVATE
       ${CMAKE_CURRENT_SOURCE_DIR}/daemonizer/
       ${CMAKE_CURRENT_SOURCE_DIR}/common/
       ${CMAKE_CURRENT_SOURCE_DIR})

set_property(TARGET ${target}
     PROPERTY
       CXX_STANDARD 17)
