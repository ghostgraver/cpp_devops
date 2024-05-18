srcs_with_dir = $(wildcard ./*.cpp)
srcs_without_dir = $(notdir $(srcs_with_dir))
objs_without_path = $(patsubst %.cpp, %.o, $(srcs_without_dir))
objs = $(addprefix $(work_dir)/$(obj_test_dir)/,$(objs_without_path))
bin_name = $(work_dir)/$(test_bin_dir)/$(test_app)

vpath %.cpp .

ALL: $(bin_name)

$(work_dir)/$(obj_test_dir)/%.o : %.cpp
	$(CC) $(CXXFLAGS) -c $< $(inc_test_dir) -o $@

$(bin_name): $(objs)
	$(CC) $(CXXFLAGS) $^ -o $@
