project('interview_practice', 'cpp', default_options : ['cpp_std=c++14'])


#
# Use boost to get unit tests
#

# Since my system's libraries are a mess, be very explicit about where to find boost.
# In this case, we're relying on the library from Homebrew.
boost_root = '/usr/local/Cellar/boost/1.63.0'
boost_inc = boost_root + '/include/'
boost_lib = boost_root + '/lib'

cc = meson.get_compiler('cpp')
boost_utfw = cc.find_library('boost_unit_test_framework', dirs : boost_lib)


#
# Define a library for business logic, the main executable that
# uses the business logic, and a unit test that tests the business logic.
#

# Add include directories here.  Boost is already here, for unit tests.
includes = include_directories(boost_inc)

# Add the sources that comprise your library here.
lib_sources = ['adder_lib.cpp']

# Add the sources that comprise your unit tests here.
unit_test_sources = ['interview_practice_test.cpp']

# Add the sources that comprise your executable here.
exe_sources = ['interview_practice_exe.cpp']


interview_practice_lib = static_library(
          'interview_practice_lib',
          lib_sources)

interview_practice_tests = executable(
          'interview_practice_tests',
          sources: unit_test_sources,
          include_directories: includes,
          link_with: interview_practice_lib,
          dependencies: boost_utfw)

interview_practice_exe = executable(
          'interview_practice',
          sources: exe_sources,
          include_directories: includes,
          link_with: interview_practice_lib,
# Uncomment this line and add a pch.h file in the pch directory to get a precompiled header.
#          cpp_pch: 'pch/pch.h',
          install: true)

test('Unit Tests', interview_practice_tests)
