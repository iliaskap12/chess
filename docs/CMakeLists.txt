set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)

## first we can indicate the documentation build as an option and set it to ON by default
#option(BUILD_DOC "Build documentation" ON)
#
#set(DOXYGEN_IN Doxyfile.in)
#set( DOXYGEN_OUTPUT_DIRECTORY doxygen )
#set( DOXYGEN_INPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/include" "${CMAKE_SOURCE_DIR}/src" "${CMAKE_SOURCE_DIR}/docs")
#set( DOXYGEN_COLLABORATION_GRAPH YES )
#set( DOXYGEN_EXTRACT_ALL YES )
#set( DOXYGEN_CLASS_DIAGRAMS YES )
#set( DOXYGEN_HIDE_UNDOC_RELATIONS NO )
#set( DOXYGEN_HAVE_DOT YES )
#set( DOXYGEN_CLASS_GRAPH YES )
#set( DOXYGEN_CALL_GRAPH YES )
#set( DOXYGEN_CALLER_GRAPH YES )
#set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
#configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
#add_custom_target( doc_doxygen ALL
#        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
#        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#        COMMENT "Generating API documentation with Doxygen"
#        VERBATIM )

#doxygen_add_docs(docs ${PROJECT_NAME} mainpage.md
#        WORKING_DIRECTORY "../include")
