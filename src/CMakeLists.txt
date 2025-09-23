find_package(OpenCV REQUIRED)


# add_executable(
#     exec1
#     chapter1.cpp
# )


# add_executable(
#     exec2
#     chapter2.cpp
# )

# add_executable(
#     exec4
#     chapter4.cpp
# )

# add_executable(
#     exec5
#     chapter5.cpp
# )

# add_executable(
#     exec6
#     chapter6.cpp
# )

# add_executable(
#     exec7
#     chapter7.cpp
# )

# add_executable(
#     exec8
#     chapter8.cpp
# )

add_executable(
    documentScanner
    documentScanner.cpp
)

# target_link_libraries(exec1 ${OpenCV_LIBS})
# target_link_libraries(exec2 ${OpenCV_LIBS})
# target_link_libraries(exec4 ${OpenCV_LIBS})
# target_link_libraries(exec5 ${OpenCV_LIBS})
# target_link_libraries(exec6 ${OpenCV_LIBS})
# target_link_libraries(exec7 ${OpenCV_LIBS})
# target_link_libraries(exec8 ${OpenCV_LIBS})
target_link_libraries(documentScanner ${OpenCV_LIBS})
