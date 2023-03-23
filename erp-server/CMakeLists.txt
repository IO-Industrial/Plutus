
set(target erp-server.wt)

INCLUDE_DIRECTORIES( include/model )

set(src
  src/main.cpp
  src/model/session.cpp 
  src/model/user.cpp
  src/application.cpp
  src/navigation.cpp
  src/menu.cpp
  src/mainpage.cpp
  )

add_executable(${target} ${src})

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
  target_link_libraries(${target}
  ${libs}

  ${Wt_LIBRARIES}
)
else()
  target_link_libraries(${target}
  ${libs}

  ${Wt_DEBUG_LIBRARIES}
)
endif()
