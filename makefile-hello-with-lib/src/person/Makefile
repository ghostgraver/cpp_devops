srcs_with_dir = $(wildcard ./*.cpp)
srcs_without_dir = $(notdir $(srcs_with_dir))
objs_without_path = $(patsubst %.cpp, %.o, $(srcs_without_dir))
objs = $(addprefix $(work_dir)/$(obj_dir)/,$(objs_without_path))

dynamic_lib_name = $(work_dir)/$(lib_dir)/$(lib_dynamic_name)
static_lib_name = $(work_dir)/$(lib_dir)/$(lib_static_name)

vpath %.cpp .

ALL: $(dynamic_lib_name) $(static_lib_name)

$(dynamic_lib_name) : $(objs)
	$(CC) $(CXXFLAGS) -shared $^ -o $@

$(static_lib_name) : $(objs)
	ar -rc $@ $(objs)

$(work_dir)/$(obj_dir)/%.o : %.cpp
	$(CC) $(CXXFLAGS) -fPIC -c $< $(inc_path) -o $@ 

