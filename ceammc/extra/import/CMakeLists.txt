include(PdExternal)
# for m_pd.h and others
include_directories(${PROJECT_SOURCE_DIR}/src)

pd_add_external(NAME import
    FILES import.c
    INTERNAL True
    LIBRARY import
    HELP_FILES import-help.pd import-meta.pd)
