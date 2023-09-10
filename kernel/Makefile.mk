CURRENT_DIR = kernel/

OBJS_AS := boot.o
OBJS_C := print.o main.o

clean-files := *.o *.bin

$(eval $(call resolve_path))
