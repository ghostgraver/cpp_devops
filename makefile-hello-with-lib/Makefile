# 主程序
export app = graver
# person 库
export lib_person = person
# 测试程序
export test_app = graver_test


# 命令行参数 -----------------------------------------------------

# 构建类型
BUILD_TYPE ?= release
# 是否构建测试程序
BUILD_TEST ?= on
# 库链接类型
LINK_TYPE ?=dynamic

# ----------------------------------------------------------------

# 工作目录
export work_dir = $(shell pwd)
# 构建目录
export build_dir = build

# 根据构建类型， 设置不同的构建目录
ifeq ($(BUILD_TYPE),debug)
	export bin_dir = $(build_dir)/debug/dist/bin
	export test_bin_dir = $(build_dir)/debug/dist/test
	export obj_app_dir = $(build_dir)/debug/obj/src/app
	export obj_person_dir = $(build_dir)/debug/obj/src/person
	export obj_test_dir = $(build_dir)/debug/obj/test
	export lib_dir = $(build_dir)/debug/dist/lib
else
	export bin_dir = $(build_dir)/release/dist/bin
	export test_bin_dir = $(build_dir)/release/dist/test
	export obj_app_dir = $(build_dir)/release/obj/src/app
	export obj_person_dir = $(build_dir)/release/obj/src/person
	export obj_test_dir = $(build_dir)/release/obj/test
	export lib_dir = $(build_dir)/release/dist/lib
endif

# 编译命令
export CC := g++

# 编译选项
CXXFLAGS_common = -Wall -Wextra
CXXFLAGS_debug = -g
CXXFLAGS_release = -O2
ifeq ($(BUILD_TYPE),debug)
    export CXXFLAGS := $(CXXFLAGS_common) $(CXXFLAGS_debug)
else
    export CXXFLAGS := $(CXXFLAGS_common) $(CXXFLAGS_release)
endif

# person 库 ------------------------------------
# person 动态库名称
export lib_person_dynamic_name = lib$(lib_person).so
# person 静态库名称
export lib_person_static_name = lib$(lib_person).a
# person 库链接
ifeq ($(LINK_TYPE), dynamic)
	export person_link = -lperson
else
	export person_link = -l:libperson.a
endif
# person .o 文件列表
srcs_person_with_dir = $(wildcard ./src/person/*.cpp)
srcs_person_without_dir = $(notdir $(srcs_person_with_dir))
objs_person_without_path = $(patsubst %.cpp, %.o, $(srcs_person_without_dir))
export objs_person = $(addprefix $(work_dir)/$(obj_person_dir)/,$(objs_person_without_path))


# 主程序头文件目录
export inc_dir = -I $(work_dir)/include

# 测试程序头文件目录
export inc_test_dir = $(inc_dir) -I $(work_dir)/third

# 子目录的 make 命令
export MAKE = bear --output build/release/compile_commands.json -- make -w

# 默认目标
ALL: before_build app_build test_build


# 伪目标
.PHONY:before_build clean_debug clean_release clean run rerun test retest format tidy doc help

# 构建前准备
before_build:
	$(call fun_parse_objs, ./src/person/*.cpp)
	@echo $(objs_t)
	$(call fun_mkdir, build/release) # 由于 bear 命令要求目录必须存在， 所以创建此目录
	$(call fun_mkdir, $(bin_dir))
	$(call fun_mkdir, $(test_bin_dir))
	$(call fun_mkdir, $(obj_app_dir))
	$(call fun_mkdir, $(obj_person_dir))
	$(call fun_mkdir, $(obj_test_dir))
	$(call fun_mkdir, $(lib_dir))

# 构建主程序
app_build:person_build
	@$(MAKE) -C src/app
person_build:
	@$(MAKE) -C src/person

# 构建测试程序
ifeq ($(BUILD_TEST),on)
test_build:
	@$(MAKE) -C test
else
test_build:
endif
	
# 清理
clean_debug:
	-rm -rf $(build_dir)/debug
clean_release:
	-rm -rf $(build_dir)/release
clean:clean_debug clean_release

# 运行主程序
run:ALL
	cd $(bin_dir) && ./$(app)
rerun: clean_release ALL run

# 运行测试程序
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

# 格式化
ifeq ($(BUILD_TEST),on)
format:
	find src -type f \( -name "*.c" -o -name "*.cc" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -exec clang-format -style=file:.clang-format -i {} \;
	find test -type f \( -name "*.c" -o -name "*.cc" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -exec clang-format -style=file:.clang-format -i {} \;
else
format:
	find src -type f \( -name "*.c" -o -name "*.cc" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -exec clang-format -style=file:.clang-format -i {} \;
endif

# clang-tidy 检查
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

# 生成 doxygen 文档
doc:
	rm -rf build/doc
	mkdir -p build/doc
	cd doc && doxygen Doxyfile
	cd ..
	cp doc/doxygen-awesome-css/doxygen-awesome-fragment-copy-button.js build/doc/html/
	cp doc/doxygen-awesome-css/doxygen-awesome-interactive-toc.js build/doc/html/
	cp -r doc/images build/doc/html/images

help:
	@echo "targets:"
	@echo "\tALL             默认目标"
	@echo "\tbefore_build    构建前准备"
	@echo "\tclean_debug     清理 debug"
	@echo "\tclean_release   清理 release"
	@echo "\tclean           清理所有"
	@echo "\tapp_build       构建主程序"
	@echo "\ttest_build      构建测试程序"
	@echo "\trun             运行主程序"
	@echo "\trerun           清理并运行主程序"
	@echo "\ttest            运行测试程序"
	@echo "\tretest          清理并运行测试程序"
	@echo "\tformat          使用 clang-format 格式化"
	@echo "\ttidy            使用 clang-tidy 检查代码"
	@echo "\tdoc             使用 doxygen 生成文档"
	@echo "\thelp            打印此帮助文档"
	@echo "options:"
	@echo "\tBUILD_TYPE      构建类型"
	@echo "\t\trelease       release 构建(默认值)"
	@echo "\t\tdebug         debug 构建"
	@echo "\tBUILD_TEST      是否构建测试程序"
	@echo "\t\ton            构建测试程序(默认值)"
	@echo "\t\toff           不构建测试程序"



# 自定义函数 -----------------------------
# 目录不存在则创建
define fun_mkdir
	@if [ ! -d $(1) ]; then \
		mkdir -p $(1); \
	fi
endef





