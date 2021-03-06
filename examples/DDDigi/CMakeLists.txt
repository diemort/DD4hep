#==========================================================================
#  AIDA Detector description implementation 
#--------------------------------------------------------------------------
# Copyright (C) Organisation europeenne pour la Recherche nucleaire (CERN)
# All rights reserved.
#
# For the licensing terms see $DD4hepINSTALL/LICENSE.
# For the list of contributors see $DD4hepINSTALL/doc/CREDITS.
#
#==========================================================================
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

IF(NOT TARGET DD4hep::DDCore)
  find_package ( DD4hep REQUIRED )
  include ( ${DD4hep_DIR}/cmake/DD4hep.cmake )
  include ( ${DD4hep_DIR}/cmake/DD4hepBuild.cmake )
  dd4hep_configure_output()
ENDIF()

dd4hep_set_compiler_flags()
#==========================================================================
dd4hep_configure_output ()

set(DDDigiexamples_INSTALL  ${CMAKE_INSTALL_PREFIX}/examples/DDDigi)
#
dd4hep_add_plugin(DDDigiExampleLib SOURCES src/*.cpp )
target_link_libraries(DDDigiExampleLib DD4hep::DDDigi Boost::boost ROOT::Geom ROOT::GenVector ROOT::RIO ROOT::Gui ROOT::Hist)
install(TARGETS DDDigiExampleLib LIBRARY DESTINATION lib)
install(DIRECTORY scripts DESTINATION ${DDDigiexamples_INSTALL})
#
dd4hep_configure_scripts (DDDigi DEFAULT_SETUP WITH_TESTS)
#
# Test basic processing chain
dd4hep_add_test_reg(DDDigi_framework
  COMMAND    "${CMAKE_INSTALL_PREFIX}/bin/run_test_DDDigi.sh"
  EXEC_ARGS  python ${DDDigiexamples_INSTALL}/scripts/TestFramework.py
  REGEX_PASS "\\+\\+\\+ 10 Events out of 10 processed."
  REGEX_FAIL "Error;ERROR;Exception"
  )
#
# Test colored noise factory
dd4hep_add_test_reg(DDDigi_colored_noise
  COMMAND    "${CMAKE_INSTALL_PREFIX}/bin/run_test_DDDigi.sh"
  EXEC_ARGS  geoPluginRun -ui -plugin DD4hep_FalphaNoise -shots 1000000 -variance 1 -alpha 0.5
  REGEX_PASS "FalphaNoise      INFO  Distribution  RMS                 1.0"
  REGEX_FAIL "Error;ERROR;Exception"
  )
#

