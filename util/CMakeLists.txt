add_library(util
	loggers/logger.c
	structures/queue.c
	structures/stack.c
	structures/symbolTable.c
	typesystem/primitives.c
	typesystem/typeSystem.c
)

target_include_directories(util PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/loggers
	${CMAKE_CURRENT_SOURCE_DIR}/structures
	${CMAKE_CURRENT_SOURCE_DIR}/typesystem
)
