project(TestProject)

set(SOURCE_FILES
	LiseuseApp.cpp
	LiseuseApp.h
	LiseuseFrame.cpp
	LiseuseFrame.h
	LiseusePanel.cpp
	LiseusePanel.h)

find_package(wxWidgets)

include(${wxWidgets_USE_FILE})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
