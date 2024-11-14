set(TARGET_NAME zello_world)

add_executable(${TARGET_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/zello_world.cpp
)
    
if(MSVC)
    set_target_properties(${TARGET_NAME}
        PROPERTIES
            VS_DEBUGGER_COMMAND_ARGUMENTS ""
            VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)"
    )
endif()

set(LEVELZERO_DIR "C:/Users/gta/source/repos/parallel-computing-lab/level-zero-1.18.5-win64")
set(LZ_INC_DIR ${LEVELZERO_DIR}/include/level_zero ${LEVELZERO_DIR}/include)
set(LZ_LIB_DIR ${LEVELZERO_DIR}/lib)

target_include_directories( ${TARGET_NAME} PUBLIC ${LEVELZERO_DIR}/include/level_zero  ${LEVELZERO_DIR}/include)

target_link_libraries(${TARGET_NAME} PRIVATE
    ${LZ_LIB_DIR}
)
#    ${CMAKE_DL_LIBS}
#)
link_directories(${LEVELZERO_DIR}/lib)

target_link_libraries(${TARGET_NAME} PRIVATE 
      ${LEVELZERO_DIR}/lib/ze_loader.lib
      ${LEVELZERO_DIR}/lib/ze_tracing_layer.lib
      ${LEVELZERO_DIR}/lib/ze_validation_layer.lib
	)
