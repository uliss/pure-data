include(TestBigEndian)
include(FindLibDL)
include(windres)
test_big_endian(IS_BIG_ENDIAN)
if(NOT ${IS_BIG_ENDIAN})
    add_definitions(-DLITTLE_ENDIAN=0x0001 -DBYTE_ORDER=LITTLE_ENDIAN)
endif()

# needed for math constants in <math.h>: M_PI etc.
add_definitions(-D_USE_MATH_DEFINES)

set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_package(Threads)

set(PLATFORM_LINK_LIBRARIES)

if(UNIX AND NOT APPLE)
    add_definitions(-D_GNU_SOURCE)
    list(APPEND PLATFORM_LINK_LIBRARIES m)
    list(APPEND PLATFORM_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
    set(LINUX True)
endif()

# address sanitizer
if(WITH_ASAN)
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
    set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-omit-frame-pointer -fsanitize=address")
    set (CMAKE_LINKER_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-omit-frame-pointer -fsanitize=address")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
    set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
endif()

function(find_and_install_dll mask dir)
    file(GLOB _dll "${dir}/${mask}")
    if(_dll)
        message(STATUS "Found DLL: ${_dll}")
        install(PROGRAMS ${_dll} DESTINATION ${PD_EXE_INSTALL_PATH})
    else()
        message(STATUS "file is not found: ${dir}/${mask}")
    endif()
endfunction()

if(WIN32)
    find_program(WISH_PATH
        NAMES wish86.exe wish.exe
        PATHS C:/Tcl/bin)

    if(NOT WISH_PATH)
        message(FATAL_ERROR "wish.exe not found")
    else()
        message(STATUS "wish found: ${WISH_PATH}")
        get_filename_component(WISHAPP ${WISH_PATH} NAME)
        get_filename_component(WISH_BINDIR ${WISH_PATH} DIRECTORY)
    endif()

    # install wish.exe to bin directory
    install(PROGRAMS ${WISH_PATH} DESTINATION ${PD_EXE_INSTALL_PATH})
    include(InstallRequiredSystemLibraries)

    # install tcl.dll
    find_file(TCLDLL_PATH NAMES tcl86.dll PATHS ${WISH_BINDIR})
    if(TCLDLL_PATH)
        install(PROGRAMS ${TCLDLL_PATH} DESTINATION ${PD_EXE_INSTALL_PATH})
    endif()

    # install tk.dll
    find_file(TKDLL_PATH NAMES tk86.dll PATHS ${WISH_BINDIR})
    if(TKDLL_PATH)
        install(PROGRAMS ${TKDLL_PATH} DESTINATION ${PD_EXE_INSTALL_PATH})
    endif()

    # install zlib.dll
    find_file(ZLIBDLL_PATH NAMES zlib1.dll PATHS ${WISH_BINDIR})
    if(ZLIBDLL_PATH)
        install(PROGRAMS ${ZLIBDLL_PATH} DESTINATION ${PD_EXE_INSTALL_PATH})
    endif()

    # install tcl/tk libs
    function(install_tcl_dir name)
        # get normalized path
        get_filename_component(_path "${WISH_BINDIR}/../lib/${name}" ABSOLUTE)
        if(EXISTS ${_path})
            message(STATUS "Found TCL package: ${name} at ${_path}")
            install(DIRECTORY "${_path}" DESTINATION "${PD_LIBTCL_INSTALL_PATH}")
        else()
            message(STATUS "TCL package not found: ${name}")
        endif()
    endfunction()

    install_tcl_dir(tcl8)
    install_tcl_dir(tcl8.6)
    install_tcl_dir(tk8.6)
    install_tcl_dir(dde1.4)
    install_tcl_dir(tcllib1.18)
    install_tcl_dir(tcllib1.19)
    # try different tooltip location
    install_tcl_dir(tklib0.6)
    install_tcl_dir(tklib0.6/tooltip)
    install_tcl_dir(tooltip)
    install_tcl_dir(reg1.3)

    include(InstallRequiredSystemLibraries)
    install(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS}
        DESTINATION bin
        COMPONENT Libraries)

    # install README, LICENSE.txt to root
    install(FILES
            ${CMAKE_SOURCE_DIR}/README.txt
            ${CMAKE_SOURCE_DIR}/LICENSE.txt
        DESTINATION
            ${CMAKE_INSTALL_PREFIX})

    if(${CMAKE_SYSTEM_NAME} STREQUAL "WindowsStore")
        message("Building for UWP")
        set(FIPS_UWP 1)
    else()
        set(FIPS_UWP 0)
    endif()

    if (FIPS_UWP)
        set(CMAKE_CXX_STANDARD_LIBRARIES "WindowsApp.lib")
        set(CMAKE_C_STANDARD_LIBRARIES "WindowsApp.lib")
    else()
        set(CMAKE_CXX_STANDARD_LIBRARIES "-lkernel32 -lgdi32 -lole32 -lwinmm -luuid -lwsock32 -lws2_32")
        set(CMAKE_C_STANDARD_LIBRARIES ${CMAKE_CXX_STANDARD_LIBRARIES})
    endif()

    add_definitions(-DPD_INTERNAL -DWINVER=0x0502 -D_WIN32_WINNT=0x0502)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mms-bitfields")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -mms-bitfields")

    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mms-bitfields -O2 -funroll-loops -fomit-frame-pointer")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -mms-bitfields -O2 -funroll-loops -fomit-frame-pointer")

    set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all-symbols -lpthread")
    set(CMAKE_EXE_LINKER_FLAGS "-shared-libgcc -lpthread")

    list(APPEND PLATFORM_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

    # MSYS64 clang flags:
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-incompatible-ms-struct")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-incompatible-ms-struct")
    endif()

    add_custom_target(prepare_win_tests
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:puredata-core>" "${PROJECT_BINARY_DIR}/ceammc/ext/tests"
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:ceammc_core>" "${PROJECT_BINARY_DIR}/ceammc/ext/tests"
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:ceammc_sound>" "${PROJECT_BINARY_DIR}/ceammc/ext/tests"
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:wrapper_lib>" "${PROJECT_BINARY_DIR}/ceammc/ext/tests"
    )
endif()

if(APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -funroll-loops -fomit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -funroll-loops -fomit-frame-pointer")

    set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG -ffast-math -funroll-loops -fomit-frame-pointer")
    set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -O2 -DNDEBUG -ffast-math -funroll-loops -fomit-frame-pointer")

    set(BUNDLE "Pd-${PD_MACOSX_BUNDLE_SUFFIX}.app")
    set(BUNDLE_FULL_PATH "${PROJECT_BINARY_DIR}/dist/${BUNDLE}")
    set(MAKE_BUNDLE_SCRIPT ${PROJECT_BINARY_DIR}/dist/ceammc_build.sh)

    # copy and substitute variables to Info.plist
    file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/dist)
    configure_file(${PROJECT_SOURCE_DIR}/ceammc/gui/Info.plist ${PROJECT_BINARY_DIR}/dist/Info.plist)

    set(CUSTOM_TCL "/Library/Frameworks/Tcl.framework")
    set(CUSTOM_TK  "/Library/Frameworks/Tk.framework")
    set(CUSTOM_WISH "${CUSTOM_TK}/Versions/8.6/Resources/Wish.app")

    set(SYSTEM_TCL     "/System/Library/Frameworks/Tcl.framework")
    set(SYSTEM_TK      "/System/Library/Frameworks/Tk.framework")
    set(SYSTEM_WISH_V5 "${SYSTEM_TK}/Versions/8.5/Resources/Wish.app")
    set(SYSTEM_WISH_V4 "${SYSTEM_TK}/Versions/8.4/Resources/Wish.app")

    set(IS_SYSTEM_TK 0)
    set(TK_VERSION "")

    if(EXISTS ${CUSTOM_TCL} AND EXISTS ${CUSTOM_TK} AND EXISTS ${CUSTOM_WISH})
        set(TCL_PATH "${CUSTOM_TCL}")
        set(TK_PATH  "${CUSTOM_TK}")
        set(WISH_APP "${CUSTOM_WISH}")
        set(TK_VERSION "8.6")
    elseif(EXISTS ${SYSTEM_TCL} AND EXISTS ${SYSTEM_TK})
        set(TCL_PATH "${SYSTEM_TCL}")
        set(TK_PATH  "${SYSTEM_TK}")

        if(EXISTS ${SYSTEM_WISH_V5})
            set(WISH_APP "${SYSTEM_WISH_V5}")
            set(TK_VERSION "8.5")
        elseif(EXISTS ${SYSTEM_WISH_V4})
            set(WISH_APP "${SYSTEM_WISH_V4}")
            set(TK_VERSION "8.4")
        else()
            message(FATAL_ERROR "Wish.app not found in \"${SYSTEM_TK}\"")
        endif()
        set(IS_SYSTEM_TK 1)
    else()
        message(FATAL_ERROR "TCL not found")
    endif()

    message(STATUS "found Tcl: ${TCL_PATH}")
    message(STATUS "found Tk:  ${TK_PATH}")
    message(STATUS "found Wish.app: ${WISH_APP}")
    message(STATUS "found Tcl/Tk version: ${TK_VERSION}")

    add_custom_command(
        OUTPUT ${MAKE_BUNDLE_SCRIPT}
        COMMAND ${CMAKE_COMMAND}
            -DPROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}"
            -DPROJECT_BINARY_DIR="${PROJECT_BINARY_DIR}"
            -DBUNDLE=${BUNDLE_FULL_PATH}
            -DWISH_APP=${WISH_APP}
            -DTCL_PATH=${TCL_PATH}
            -DLEAPMOTION_LIBRARY=${LEAPMOTION_LIBRARY}
            -DDYLIBBUNDLER="${CMAKE_BINARY_DIR}/ceammc/distrib/mac/dylibbundler"
            -DTK_PATH=${TK_PATH}
            -DIS_SYSTEM_TK=${IS_SYSTEM_TK}
            -DTK_VERSION=${TK_VERSION}
            -P ${PROJECT_SOURCE_DIR}/cmake/cmake_build_mac.cmake)

    add_custom_command(
        OUTPUT ${BUNDLE_FULL_PATH}
        COMMAND sh ${MAKE_BUNDLE_SCRIPT}
        COMMAND ${CMAKE_COMMAND}
            -DBUNDLE=${BUNDLE_FULL_PATH}
            -P ${PROJECT_SOURCE_DIR}/cmake/bundle.cmake
        DEPENDS pd)

    # app target
    # `make app` creates MacOSX bundle
    add_custom_target(app DEPENDS ${MAKE_BUNDLE_SCRIPT} ${BUNDLE_FULL_PATH})

    add_custom_target(codesign
        COMMAND sh ${PROJECT_SOURCE_DIR}/mac/codesign.sh ${BUNDLE_FULL_PATH}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/mac)

    add_custom_target(dmg
        COMMAND
            sh ${PROJECT_SOURCE_DIR}/mac/dmg.sh
            ${BUNDLE_FULL_PATH}
            "${PD_MACOSX_BUNDLE_SUFFIX}-macosx-${MACOSX_VERSION}"
            ${PROJECT_SOURCE_DIR}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        DEPENDS app)

    find_program(GPGENV_EXE NAMES gpgenv)

    if(GPGENV_EXE)
        add_custom_target(deploy
            COMMAND
                ${PROJECT_BINARY_DIR}/dist/github_upload_release.sh
                "${PROJECT_BINARY_DIR}/Pd_${PD_MACOSX_BUNDLE_SUFFIX}-macosx-${MACOSX_VERSION}.dmg"
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            DEPENDS dmg src-zip src-tar ceammc_lib)
    endif()
endif()

if(UNIX AND NOT APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -funroll-loops -fomit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -funroll-loops -fomit-frame-pointer")

    set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG -ffast-math -funroll-loops -fomit-frame-pointer")
    set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -O2 -DNDEBUG -ffast-math -funroll-loops -fomit-frame-pointer")
endif()
