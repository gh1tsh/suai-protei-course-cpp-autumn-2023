add_test([=[HelloTest.BasicAssertions]=]  /home/ghitsh/suai/suai-protei-course-cpp/suai-protei-course-cpp-autumn-2023/task-1/cmake-build-debug/hello_test [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HelloTest.BasicAssertions]=]  PROPERTIES WORKING_DIRECTORY /home/ghitsh/suai/suai-protei-course-cpp/suai-protei-course-cpp-autumn-2023/task-1/cmake-build-debug SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  hello_test_TESTS HelloTest.BasicAssertions)
