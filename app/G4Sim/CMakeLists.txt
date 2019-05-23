SET(G4SIM_APPS
  G4Sim
  G4Thin
  G4Sim_bias
  G4Thin_bias
  G4Sim_binned
  G4Thin_binned
  G4Thin_func
)

if(DEFINED USE_FHICL AND USE_FHICL)
  add_dependencies(G4SimLib fhiclcpp-simple)
endif()

include_directories(${INCDIRS})

include(${Geant4_USE_FILE})
include_directories(${ROOT_INCLUDE_DIRS})

# Requried for fhiclcpp
include_directories(${CMAKE_INSTALL_PREFIX}/include)

foreach(appname ${G4SIM_APPS})
  add_executable(${appname} ${appname}.cc)
  target_link_libraries(${appname} ${MODULETargets})
  target_link_libraries(${appname} ${ROOT_LIBRARIES})
  target_link_libraries(${appname} ${Geant4_LIBRARIES})

  install(TARGETS ${appname} DESTINATION bin)
endforeach()
