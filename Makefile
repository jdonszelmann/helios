# windows version
version = 0.0.1
arch ?= x86_64
out := "main.exe"
dir := "shell echo %CD%"
dirs = $(shell dir src\arch\$(arch) /b /s /o:n)
includedirs :=  $(shell dir src\arch\$(arch)\*include /b /s /o:n /ad)

CFLAGS= -m32 -Wall -O -fno-pie -fstrength-reduce -fomit-frame-pointer	\
        -finline-functions -nostdinc -fno-builtin -ffreestanding		\
        -fno-stack-protector -c

CFLAGS += $(foreach dir, $(includedirs), -I./$(dir))

c_source_files := $(shell dir src\arch\$(arch)\*.c /b /s /o:n)
c_object_files := $(patsubst $(dir)\src\arch\$(arch)\%.c, \
    $(dir)\build\arch\$(arch)\%.o, $(c_source_files))

.P HONY: all clean run runrel iso

all: $(executable)

clean:
	@rm -r build

run: $(executable)


$(executable): $(c_object_files)
	$(info "linking...")
	@ld -nostdlib -m elf_i386 -o $(out) $(assembly_object_files) $(c_object_files)

# compile assembly files
build/arch/$(arch)/%.o: src/arch/$(arch)/%.c
	@mkdir -p $(shell dirname $@)
	$(info "compiling $<")
	@gcc $(CFLAGS) $< -o $@