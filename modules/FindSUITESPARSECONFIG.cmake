# - Try to find SUITEPARSE_CONFIG
#  
#  OUTPUT:
#  SUITESPARSE_CONFIG_FOUND        - system has SUITEPARSE_CONFIG
#  SUITESPARSE_CONFIG_INCLUDE_DIRS - include directories for SUITEPARSE_CONFIG
#  SUITESPARSE_CONFIG_LIBRARIES    - libraries for SUITEPARSE_CONFIG
#
#  Xiaozhe Hu
#  02/27/2013

message(STATUS "Checking for package 'SUITESPARSE_CONFIG'")

# Check for header file
find_path(SUITESPARSE_CONFIG_INCLUDE_DIRS SuiteSparse_config.h UFconfig.h
 HINTS ${SUITESPARSE_CONFIG_DIR} ${SUITESPARSE_CONFIG_DIR}/include ${SUITESPARSE_CONFIG_DIR}/SuiteSparse_config ${SUITESPARSE_CONFIG_DIR}/SuiteSparse_config/include ${SUITESPARSE_CONFIG_DIR}/SuiteSparse_config ${SUITESPARSE_CONFIG_DIR}/SuiteSparse_config/include $ENV{SUITESPARSE_CONFIG_DIR} $ENV{SUITESPARSE_CONFIG_DIR}/include
 PATH_SUFFIXES suitesparse SuiteSparse ufsparse
 DOC "Directory where the SUITESPARSE_CONFIG header is located"
 )
mark_as_advanced(SUITESPARSE_CONFIG_INCLUDE_DIRS)

# Check for SUITESPARSE_CONFIG library
find_library(SUITESPARSE_CONFIG_LIBRARIES suitesparseconfig ufconfig 
  HINTS ${SUITESPARSE_CONFIG_DIR} ${SUITESPARSE_CONFIG_DIR}/lib ${SUITESPARSE_CONFIG_DIR}/SuiteSparse_config ${SUITESPARSE_CONFIG_DIR}/SuiteSparse_config/lib  $ENV{SUITESPARSE_CONFIG_DIR} $ENV{SUITESPARSE_CONFIG_DIR}/lib $ENV{SUITESPARSE_CONFIG_DIR}/SuiteSparse_config $ENV{SUITESPARSE_CONFIG_DIR}/SuiteSparse_config/lib
  DOC "The SUITESPARSE_CONFIG library"
  )
mark_as_advanced(SUITESPARSE_CONFIG_LIBRARIES)

# Standard package handling
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SUITESPARSE_CONFIG
  "SUITESPARSE_CONFIG could not be found. Be sure to set SUITESPARSE_CONFIG_DIR."
  SUITESPARSE_CONFIG_LIBRARIES SUITESPARSE_CONFIG_INCLUDE_DIRS)