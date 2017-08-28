project('merge_arrays', 'cpp', default_options : ['cpp_std=c++14'])


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

# Add the sources that comprise your unit tests here.
unit_test_sources = ['merge_arrays_test.cpp']

# Add the sources that comprise your executable here.
exe_sources = ['merge_arrays_exe.cpp']

merge_arrays_tests = executable(
          'merge_arrays_tests',
          sources: unit_test_sources,
          include_directories: includes,
          dependencies: boost_utfw)

merge_vectors_tests = executable(
          'merge_vectors_tests',
          sources: unit_test_sources,
          include_directories: includes,
          dependencies: boost_utfw)

merge_arrays_exe = executable(
          'merge_arrays',
          sources: exe_sources,
          include_directories: includes,
          link_with: merge_arrays_lib,
          install: true)

test('Merge Arrays Unit Tests', merge_arrays_tests)
test('Merge Vectors Unit Tests', merge_vectors_tests)
