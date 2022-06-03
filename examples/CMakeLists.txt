add_executable(test_unique test_unique.cc)
add_executable(test_quick_sort test_quick_sort.cc)
add_executable(test_partition test_partition.cc)

add_executable(false_sharing false_sharing.cc)
target_link_libraries(false_sharing benchmark pthread)