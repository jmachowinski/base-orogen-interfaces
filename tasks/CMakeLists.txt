# Generated from orogen/lib/orogen/templates/tasks/CMakeLists.txt

include(interfacesTaskLib)

if(BUILD_STATIC)
    ADD_LIBRARY(${INTERFACES_TASKLIB_NAME}
    StateAggregator.cpp
    OrocosStateAggregator.cpp
    ${INTERFACES_TASKLIB_SOURCES}
)
else()
    ADD_LIBRARY(${INTERFACES_TASKLIB_NAME} SHARED 
    StateAggregator.cpp
    OrocosStateAggregator.cpp
    ${INTERFACES_TASKLIB_SOURCES}
)
endif()

add_dependencies(${INTERFACES_TASKLIB_NAME}
    regen-typekit)


TARGET_LINK_LIBRARIES(${INTERFACES_TASKLIB_NAME}
    ${OrocosRTT_LIBRARIES}
    ${INTERFACES_TASKLIB_DEPENDENT_LIBRARIES})
SET_TARGET_PROPERTIES(${INTERFACES_TASKLIB_NAME}
    PROPERTIES LINK_INTERFACE_LIBRARIES "${INTERFACES_TASKLIB_INTERFACE_LIBRARIES}")

INSTALL(TARGETS ${INTERFACES_TASKLIB_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib/orocos
    ARCHIVE DESTINATION lib/orocos)

INSTALL(FILES ${INTERFACES_TASKLIB_HEADERS}
    StateAggregator.hpp
    OrocosStateAggregator.hpp
    DESTINATION include/orocos/interfaces)

