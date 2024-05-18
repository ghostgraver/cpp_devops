export app = graver
export test_app = graver_test


# -----------------------------------------------------

BUILD_TYPE ?= release
BUILD_TEST ?= on

# ----------------------------------------------------------------

export CC := g++
CXXFLAGS_common = -Wall -Wextra
CXXFLAGS_debug = -g
CXXFLAGS_release = -O2
ifeq ($(BUILD_TYPE),debug)
    export CXXFLAGS := $(CXXFLAGS_common) $(CXXFLAGS_debug)
else
    export CXXFLAGS := $(CXXFLAGS_common) $(CXXFLAGS_release)
endif

export work_dir = $(shell pwd)
export build_dir = build

ifeq ($(BUILD_TYPE),debug)
	export bin_dir = $(build_dir)/debug/bin
	export test_bin_dir = $(build_dir)/debug/test
	export obj_src_dir = $(build_dir)/debug/obj/src
	export obj_test_dir = $(build_dir)/debug/obj/test
else
	export bin_dir = $(build_dir)/release/bin
	export test_bin_dir = $(build_dir)/release/test
	export obj_src_dir = $(build_dir)/release/obj/src
	export obj_test_dir = $(build_dir)/release/obj/test
endif

export inc_dir = -I $(work_dir)/include

export inc_test_dir = $(inc_dir) -I $(work_dir)/third
export test_bin = $(test_bin_dir)/$(test)

export MAKE = bear --output build/release/compile_commands.json -- make -w

ALL: before_build app_build test_build
	

.PHONY:before_build clean_debug clean_release clean run rerun test retest format tidy doc

define fun_mkdir
	@if [ ! -d $(1) ]; then \
		mkdir -p $(1); \
	fi
endef

before_build:
	$(call fun_mkdir, $(bin_dir))
	$(call fun_mkdir, $(test_bin_dir))
	$(call fun_mkdir, $(obj_src_dir))
	$(call fun_mkdir, $(obj_test_dir))

app_build:
	@$(MAKE) -C src

ifeq ($(BUILD_TEST),on)
test_build:
	@$(MAKE) -C test
else
test_build:
endif
	

clean_debug:
	-rm -rf $(build_dir)/debug
clean_release:
	-rm -rf $(build_dir)/release
clean:clean_debug clean_release

run:ALL
	cd $(bin_dir) && ./$(app)
rerun: clean_release ALL run

ifeq ($(BUILD_TEST),on)
test:ALL
	cd $(test_bin_dir) && ./$(test_app)
else
test:
endif

ifeq ($(BUILD_TEST),on)
retest:clean_release ALL test
else
retest:
endif


ifeq ($(BUILD_TEST),on)
format:
	find src -type f \( -name "*.c" -o -name "*.cc" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -exec clang-format -style=file:.clang-format -i {} \;
	find test -type f \( -name "*.c" -o -name "*.cc" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -exec clang-format -style=file:.clang-format -i {} \;
else
format:
	find src -type f \( -name "*.c" -o -name "*.cc" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -exec clang-format -style=file:.clang-format -i {} \;
endif

ifeq ($(BUILD_TEST),on)
tidy:format
	find src -type f -name "*.cpp" -print0 | xargs -0 clang-tidy --config-file=.clang-tidy -p=build/ninja-release --quiet
	find include -type f -name "*.h" -print0 | xargs -0 clang-tidy --config-file=.clang-tidy -p=build/ninja-release --quiet
	find test -type f -name "*.h" -print0 | xargs -0 clang-tidy --config-file=.clang-tidy -p=build/ninja-release --quiet
else
tidy:format
	find src -type f -name "*.cpp" -print0 | xargs -0 clang-tidy --config-file=.clang-tidy -p=build/ninja-release --quiet
	find include -type f -name "*.h" -print0 | xargs -0 clang-tidy --config-file=.clang-tidy -p=build/ninja-release --quiet
endif

doc:
	rm -rf build/doc
	mkdir -p build/doc
	cd doc && doxygen Doxyfile
	cd ..
	cp doc/doxygen-awesome-css/doxygen-awesome-fragment-copy-button.js build/doc/html/
	cp doc/doxygen-awesome-css/doxygen-awesome-interactive-toc.js build/doc/html/
	cp -r doc/images build/doc/html/images