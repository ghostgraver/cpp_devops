srcs_with_dir = $(wildcard ./*.cpp)
srcs_without_dir = $(notdir $(srcs_with_dir))
objs_without_path = $(patsubst %.cpp, %.o, $(srcs_without_dir))
objs = $(addprefix $(work_dir)/$(obj_src_dir)/,$(objs_without_path))
bin_name = $(work_dir)/$(bin_dir)/$(app)

vpath %.cpp .

ALL: $(bin_name)

$(work_dir)/$(obj_src_dir)/%.o : %.cpp
	$(CC) $(CXXFLAGS) -c $< $(inc_dir) -o $@

$(bin_name): $(objs)
	$(CC) $(CXXFLAGS) $^ -o $@
