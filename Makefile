CMAKE_BUILD_DIR := build

.PHONY: run

run:
	@cmake -S . -B $(CMAKE_BUILD_DIR) >/dev/null 2>&1
	@cmake --build $(CMAKE_BUILD_DIR) >/dev/null 2>&1
	@$(CMAKE_BUILD_DIR)/RCompiler
