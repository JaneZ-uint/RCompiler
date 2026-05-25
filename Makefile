CMAKE_BUILD_DIR := build

.PHONY: build run

build:
	@cmake -S . -B $(CMAKE_BUILD_DIR) >/dev/null 2>&1
	@cmake --build $(CMAKE_BUILD_DIR) >/dev/null 2>&1

run: build
	@$(CMAKE_BUILD_DIR)/RCompiler
