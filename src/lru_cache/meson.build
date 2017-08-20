project('lru_cache', 'cpp', default_options : ['cpp_std=c++14'])


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
alternate_lib_sources = ['lru_cache_alternate_lib.cpp']  # The alternate_lib version is an adaptation from a Java solution.
lib_sources = ['lru_cache_lib.cpp']  # The original version is my solution.

# Add the sources that comprise your unit tests here.
unit_test_sources = ['lru_cache_test.cpp']

# Add the sources that comprise your executable here.
exe_sources = ['lru_cache_exe.cpp']


lru_cache_lib = static_library(
  'lru_cache_lib',
  lib_sources)

lru_cache_alternate_lib = static_library(
  'lru_cache_lib_alternate',
  alternate_lib_sources)

lru_cache_tests = executable(
  'lru_cache_tests',
  sources: unit_test_sources,
  include_directories: includes,
  link_with: lru_cache_lib,
  dependencies: boost_utfw)

lru_cache_alternate_tests = executable(
  'lru_cache_alternate_tests',
  sources: unit_test_sources,
  include_directories: includes,
  link_with: lru_cache_alternate_lib,
  dependencies: boost_utfw)

lru_cache_exe = executable(
  'lru_cache',
  sources: exe_sources,
  include_directories: includes,
  link_with: lru_cache_lib,
  # Uncomment this and comment the above to use the alternate library in the interactive executable.
  #link_with: lru_cache_alternate_lib,
  install: true)

test('Unit Tests', lru_cache_tests)
test('Unit Tests for Alternate lib', lru_cache_alternate_tests)
