# 使用 wildcard 函数匹配当前目录下的所有 .cpp 文件， 此列表带目录
srcs_with_dir = $(wildcard ./*.cpp)
# 去除 .cpp 文件列表中的目录
srcs_without_dir = $(notdir $(srcs_with_dir))
# .o 文件列表
objs_without_path = $(patsubst %.cpp, %.o, $(srcs_without_dir))
# .o 文件列表， 此列表带目录
objs = $(addprefix $(work_dir)/$(obj_src_dir)/,$(objs_without_path))
# 可执行程序全路径
bin_name = $(work_dir)/$(bin_dir)/$(app)

vpath %.cpp .

ALL: $(bin_name)

$(work_dir)/$(obj_src_dir)/%.o : %.cpp
	$(CC) $(CXXFLAGS) -c $< $(inc_dir) -o $@

$(bin_name): $(objs)
	$(CC) $(CXXFLAGS) $^ -o $@
