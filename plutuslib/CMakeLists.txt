project(plutuslib)

set(PLUTUS_LIB_HEADERS
    include/db/db_data_file.h 
    include/db/db_file_header.h
    include/db/db_record_pointer.h  
)

add_library(plutuslib SHARED source/db_data_file.cpp)

install(TARGETS plutuslib DESTINATION lib)
install(FILES ${PLUTUS_LIB_HEADERS} DESTINATION include)