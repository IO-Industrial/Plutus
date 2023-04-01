project(plutuslib)

add_library(plutuslib SHARED source/db_data_file.cpp)

install(TARGETS plutuslib DESTINATION lib)
#install(FILES test.h DESTINATION include)