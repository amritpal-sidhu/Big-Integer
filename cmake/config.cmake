
set(UNITY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Third-Party/Unity CACHE PATH "")
set(GENERATE_TEST_RUNNER_SCRIPT ${UNITY_DIR}/auto/generate_test_runner.rb CACHE FILEPATH "")

include_directories(Third-Party)

macro(run_tests_macro)

    set(TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/unit_tests)
    set(TEST_RUNNER_DIR ${CMAKE_BINARY_DIR}/utilities/${PROJECT_NAME}/CMakeFiles)

    if(NOT EXISTS ${TEST_RUNNER_DIR})
        file(MAKE_DIRECTORY ${TEST_RUNNER_DIR})
    endif()

    foreach(SRC_FILE ${LOCAL_SOURCES})

        get_filename_component(FILENAME ${SRC_FILE} NAME_WE)

        if (EXISTS ${TEST_DIR}/test_${FILENAME}.cpp)

            execute_process(COMMAND ruby ${GENERATE_TEST_RUNNER_SCRIPT} 
                                         ${TEST_DIR}/test_${FILENAME}.cpp
                                         ${TEST_RUNNER_DIR}/test_${FILENAME}_runner.cpp)

            add_library(test_${FILENAME} OBJECT ${TEST_DIR}/test_${FILENAME}.cpp)
            target_link_libraries(test_${FILENAME} PUBLIC unity ${PROJECT_NAME})
            target_include_directories(test_${FILENAME} PUBLIC ${UNITY_DIR}/src)
            add_dependencies(test_${FILENAME} unity)

            add_executable(test_${FILENAME}_runner ${TEST_RUNNER_DIR}/test_${FILENAME}_runner.cpp)
            target_link_libraries(test_${FILENAME}_runner PUBLIC test_${FILENAME})
            
            add_custom_command(TARGET test_${FILENAME}_runner POST_BUILD
                               WORKING_DIRECTORY ${TEST_DIR}
                               COMMAND $<TARGET_FILE:test_${FILENAME}_runner>
                               USES_TERMINAL)
        else()
            message(STATUS "No unit test for ${FILENAME} exists.")
        endif()

    endforeach()

endmacro()
