project(xrUICore)

# Files import
file(GLOB_RECURSE UICore_SOURCE_XML_FILES
    "UIXml*.*"
    "xrUIXml*.*"
)
file(GLOB_RECURSE UICore_SOURCE_ALL_FILES CONFIGURE_DEPENDS
    "*.cpp"
    "*.h"
)

set(UICore_SRC_FILES)

source_group("UICore" FILES ${UICore_SOURCE_ALL_FILES})
source_group("Parser" FILES ${UICore_SOURCE_XML_FILES})

# Apply list
list(APPEND UICore_SRC_FILES ${UICore_SOURCE_ALL_FILES})

# Remove unused files
list(FILTER UICore_SRC_FILES EXCLUDE REGEX "UITreeViewItem.*")

# xrUICore project
add_library(xrUICore SHARED ${UICore_SRC_FILES})
target_include_directories(xrUICore PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_precompile_headers(xrUICore PRIVATE "stdafx.h")

# Project defines
target_compile_definitions(xrUICore PRIVATE XRUICore_EXPORTS)
target_compile_definitions(xrUICore PRIVATE _USRDLL)

# Linker list
target_link_libraries(xrUICore PUBLIC xrCore)
target_link_libraries(xrUICore PUBLIC xrAbstractions)
target_link_libraries(xrUICore PUBLIC xrScripts)

# Move precompiled header
set_target_properties(xrUICore PROPERTIES DISABLE_PRECOMPILE_HEADERS ON)
set_target_properties(xrUICore PROPERTIES COMPILE_FLAGS "/Yustdafx.h")
set_source_files_properties(stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")
target_precompile_headers(xrUICore PRIVATE "stdafx.h")

file(GLOB_RECURSE UICore_SOURCE_PCH_FILES "stdafx.*")
source_group("pch" FILES ${UICore_SOURCE_PCH_FILES})
