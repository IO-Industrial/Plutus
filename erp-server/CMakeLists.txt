
set(target erp-server.wt)

set(src
  src/main.cpp
  )

add_executable(${target} ${src})

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
  target_link_libraries(${target}
  ${libs}

  ${Wt_LIBRARY}                  # wt
  ${Wt_HTTP_LIBRARY}             # wthttp
)
else()
  target_link_libraries(${target}
  ${libs}

  ${Wt_DEBUG_LIBRARY}            # wtd           or wt
  ${Wt_HTTP_DEBUG_LIBRARY}       # wthttpd       or wthttp
)
endif()
