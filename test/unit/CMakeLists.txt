
add_executable(unittests
        annotationstatetokenizer_unittest.cpp
        ciarrow_unittest.cpp
        cigeneral_unittest.cpp
        cilanguage_unittest.cpp
        cilineendings_unittest.cpp
        csalign_unittest.cpp
        csgeneric_unittest.cpp
        csline_unittest.cpp
        csposition_unittest.cpp
        cssize_unittest.cpp
        csvertical_unittest.cpp
        ctgenstructure_unittest.cpp
        cuetimes_unittest.cpp
        datastatetokenizer_unittest.cpp
        endtagstatetokenizer_unittest.cpp
        escapestatetokenizer_unittest.cpp
        filestructure_unittest.cpp
        lexer_unittest.cpp
        plboldtag_unittest.cpp
        plclasstag_unittest.cpp
        plescapecharacter_unittest.cpp
        plformat_unittest.cpp
        plitalictag_unittest.cpp
        pllangtag_unittest.cpp
        plrubytag_unittest.cpp
        pltagformat_unittest.cpp
        pltimestamp_unittest.cpp
        plunderlinetag_unittest.cpp
        plvoicetag_unittest.cpp
        readcuetext_unittest.cpp
        regression_tests.cpp
        setcuesettings_unittest.cpp
        starttagstatetokenizer_unittest.cpp
        string_unittest.cpp
        stringlist_unittest.cpp
        tagclasstokenizer_unittest.cpp
        tagstatetokenizer_unittest.cpp
        timestamptokenizer_unittest.cpp)

target_include_directories(unittests PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/src"
        ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(unittests
        gtest_main
        libwebvtt
        libwebvttxx)

# write this value to test_config.h so it can be picked up as the TEST_FILE_DIR define
# see https://cmake.org/cmake/help/latest/command/configure_file.html
set(TEST_FILE_DIR "${PROJECT_SOURCE_DIR}/test/unit")
configure_file(test_config.h.in test_config.h @ONLY)

if (WIN32 OR WIN64)
  set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ ${CMAKE_CXX_STANDARD_LIBRARIES}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
endif (WIN32 OR WIN64)

add_test(NAME libwebvtt_tests COMMAND unittests)
