cmake_minimum_required(VERSION 2.8.11)
PROJECT( camera )


IF ( "$ENV{ROBOCOMP}" STREQUAL "")
  MESSAGE(WARNING "ROBOCOMP variable not set. Using the default value: /opt/robocomp")
  SET (ENV{ROBOCOMP} "/opt/robocomp/")
ENDIF ( "$ENV{ROBOCOMP}" STREQUAL "")

IF(NOT EXISTS $ENV{ROBOCOMP}/cmake)
  MESSAGE(FATAL_ERROR "Couldn't find RoboComp in $ENV{ROBOCOMP}! Exiting...")
ENDIF(NOT EXISTS $ENV{ROBOCOMP}/cmake)

INCLUDE( $ENV{ROBOCOMP}/cmake/robocomp.cmake )
INCLUDE ( CMakeListsSpecific.txt)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/apriltags APRILCC)

# Sources set
SET ( SOURCES
  ${SOURCES}
  ${APRILCC}
  $ENV{ROBOCOMP}/classes/rapplication/rapplication.cpp
  $ENV{ROBOCOMP}/classes/sigwatch/sigwatch.cpp
  $ENV{ROBOCOMP}/classes/qlog/qlog.cpp
  main.cpp
  genericmonitor.cpp
  specificmonitor.cpp
  commonbehaviorI.cpp
  genericworker.cpp
  specificworker.cpp
  getapriltagsI.cpp
)



#ROBOCOMP
ROBOCOMP_INITIALIZE( $ENV{ROBOCOMP}/ )
ROBOCOMP_WRAP_ICE( CommonBehavior GetAprilTags  AprilTags  GenericBase  JointMotor  RGBD  JointMotor  GenericBase )
SET (EXECUTABLE_OUTPUT_PATH ${RC_COMPONENT_DEVEL_PATH}/bin)

# Qt4
ADD_DEFINITIONS( -Wall -DQT_DLL -DQT_GUI_LIB -DQT_CORE_LIB )
FIND_PACKAGE( Qt4 REQUIRED )
SET( QT_USE_QTGUI TRUE )
SET( QT_USE_QTOPENGL TRUE )
SET( QT_USE_QTXML TRUE )
SET( QT_USE_QTSTATE TRUE )
SET( QT_USE_QTSTATEMACHINE TRUE )
SET( CMAKE_AUTOMOC TRUE )
INCLUDE( ${QT_USE_FILE} )

# Specify construction and link process
ADD_EXECUTABLE( camera ${SOURCES} ${MOC_SOURCES} ${RC_SOURCES} ${UI_HEADERS} )
TARGET_LINK_LIBRARIES( camera /usr/local/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES} ${QT_LIBRARIES} ${LIBS} ${STATIC_LIBS} ${SPECIFIC_LIBS})
INSTALL(FILES ${EXECUTABLE_OUTPUT_PATH}/camera DESTINATION ${RC_COMPONENT_INSTALL_PATH}/bin/ PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE )
