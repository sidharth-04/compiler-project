add_executable(tests
	tests.c
	testutils.c
	queueTests.c
	stackTests.c
	symbolTableTests.c
)

target_link_libraries(tests PRIVATE
	util
)
