# Helper modules.
include(CheckFunctionExists)
include(CheckIncludeFile)

set(CMAKE_VERBOSE_MAKEFILE 1) 
set(GDB 1 CACHE BOOL "debugging or not")
set(OPENMP 0 BOOL "Openmp use")

# For which compilers we shall search (if none found then the 
# default cmake compiler detection will be invoked. 

# Search for compilers in the specified order.  
	find_program(THE_C NAMES icc gcc-mp-4.8 gcc gcc44 gcc43 )
#
	if( ${THE_C} MATCHES "gcc.*" )
		string(REPLACE "gcc" "g++" C_XX ${THE_C} )
		string(REPLACE "gcc" "gfortran" F_C ${THE_C} )
       	elseif( ${THE_C} MATCHES "icc" )                    
		set(C_XX "icpc")
		set(F_C "ifort")
	else()       
 		set(THE_C "0")	      
       	endif( ${THE_C} MATCHES "gcc.*" ) 
#
	if(  THE_C AND C_XX AND F_C )
	     find_program(THE_CXX ${C_XX} )
	     find_program(THE_F ${F_C} )
	     if( THE_F AND THE_CXX ) 
	     	 set(CMAKE_C_COMPILER ${THE_C} CACHE INTERNAL   "the C   compiler" FORCE) 
	    	 set(CMAKE_CXX_COMPILER ${THE_CXX} CACHE INTERNAL   "the C++ compiler" FORCE)
		 set(CMAKE_Fortran_COMPILER ${THE_F} CACHE INTERNAL    "the F compiler" FORCE)
	     endif( THE_F AND THE_CXX ) 
	endif(  THE_C AND C_XX AND F_C )
# END COMPILERS SET UP................ 
