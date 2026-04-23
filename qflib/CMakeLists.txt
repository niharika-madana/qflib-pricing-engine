set(qflib_SOURCES
    math/interpol/piecewisepolynomial.cpp 
    math/stats/errorfunction.cpp
    math/linalg/choldcmp.cpp 
    math/linalg/eigensym.cpp
    math/linalg/spectrunc.cpp
    methods/montecarlo/pathgenerator.cpp
    methods/pde/pdebase.cpp
    methods/pde/pde1dsolver.cpp
    pricers/simplepricers.cpp
    pricers/bsmcpricer.cpp
    pricers/multiassetbsmcpricer.cpp 
    market/market.cpp
    market/yieldcurve.cpp
    market/volatilitytermstructure.cpp
)

add_library(qflib STATIC ${qflib_SOURCES})

target_include_directories(qflib PRIVATE 
    .. 
    ${THIRDPARTY_DIRECTORY}/armadillo-${ARMA_VERSION}/include
)

# compiler and linker option adjustments for targets
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(qflib PRIVATE "/permissive-")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU") 
    target_compile_options(qflib PRIVATE -fPIC)
endif()
