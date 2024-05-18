dynamic_lib_name = $(work_dir)/$(lib_dir)/$(lib_person_dynamic_name)
static_lib_name = $(work_dir)/$(lib_dir)/$(lib_person_static_name)

vpath %.cpp .

ALL: $(dynamic_lib_name) $(static_lib_name)

$(work_dir)/$(obj_person_dir)/%.o : %.cpp
	$(CC) $(CXXFLAGS) -fPIC -c $< $(inc_dir) -o $@

$(dynamic_lib_name): $(objs_person)
	$(CC) $(CXXFLAGS) -shared $^ -o $@
$(static_lib_name): $(objs_person)
	ar -rc $@ $(objs_person)

