# All helper source files
set (HELPER_SRCS
    app.cc
    app.h
    send_ipc_message_handler.cc
    send_ipc_message_handler.h
    render_process_handler.cc
    render_process_handler.h
)

# Source files specific to Windows
set (HELPER_SRCS_WINDOWS
    main_win.cc
)

# Source files specific to MacOS
set (HELPER_SRCS_LINUX
    main_linux.cc
)

# Source files specific to Linux
set (HELPER_SRCS_MAC
    main_mac.cc
)

# CEF macro to merge shared with platform-specific source files
APPEND_PLATFORM_SOURCES(HELPER_SRCS) 
source_group(helper FILES ${HELPER_SRCS})

set(HELPER_SRCS
    ${HELPER_SRCS}
    )

SET_CEF_TARGET_OUT_DIR()

if(OS_WINDOWS)
    ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")

    set(HELPER_TARGET "client-bevy_helper")
    set(HELPER_OUTPUT_NAME "client-bevy Helper")

    add_executable(${HELPER_TARGET} WIN32 ${HELPER_SRCS})
    add_dependencies(${HELPER_TARGET} libcef_dll_wrapper)
    SET_EXECUTABLE_TARGET_PROPERTIES(${HELPER_TARGET})
    target_link_libraries(${HELPER_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS})

    if(USE_SANDBOX)
        # Logical target used to link the cef_sandbox library.
        ADD_LOGICAL_TARGET("cef_sandbox_lib" "${CEF_SANDBOX_LIB_DEBUG}" "${CEF_SANDBOX_LIB_RELEASE}")
        target_link_libraries(${HELPER_TARGET} cef_sandbox_lib ${CEF_SANDBOX_STANDARD_LIBS})
    endif()

    # ADD_WINDOWS_MANIFEST("${CMAKE_CURRENT_SOURCE_DIR}" "${CEF_TARGET}" "exe")

    COPY_FILES("${HELPER_TARGET}" "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CEF_TARGET_OUT_DIR}")
    COPY_FILES("${HELPER_TARGET}" "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CEF_TARGET_OUT_DIR}")
endif()

if(OS_MAC)
    set(HELPER_TARGET "client-bevy")
    set(HELPER_OUTPUT_NAME "client-bevy Helper")

    ADD_LOGICAL_TARGET("cef_sandbox_lib" "${CEF_SANDBOX_LIB_DEBUG}" "${CEF_SANDBOX_LIB_RELEASE}")

    add_executable(${HELPER_TARGET} ${HELPER_SRCS})
    add_dependencies(${HELPER_TARGET} libcef_dll_wrapper)
    SET_EXECUTABLE_TARGET_PROPERTIES(${HELPER_TARGET})
    target_link_libraries(${HELPER_TARGET} libcef_dll_wrapper ${CEF_STANDARD_LIBS})

    set_target_properties(${HELPER_TARGET} PROPERTIES
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
        XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO"
    )
    
    if(USE_SANDBOX)
        target_link_libraries(${HELPER_TARGET} cef_sandbox_lib)
    endif()
endif()

if(OS_LINUX)
    ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")

    set(HELPER_TARGET "client-bevy_helper")
    set(HELPER_OUTPUT_NAME "client-bevy Helper")

    add_executable(${HELPER_TARGET} WIN32 ${HELPER_SRCS})
    SET_EXECUTABLE_TARGET_PROPERTIES(${HELPER_TARGET})
    target_link_libraries(${HELPER_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS})

    COPY_FILES("${HELPER_TARGET}" "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CEF_TARGET_OUT_DIR}")
    COPY_FILES("${HELPER_TARGET}" "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CEF_TARGET_OUT_DIR}")
endif()