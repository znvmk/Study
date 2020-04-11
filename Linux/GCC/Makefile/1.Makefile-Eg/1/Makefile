CC = gcc
CFLAGS = -Isub -Iadd -O2     #头文件搜索路径sub,add ,O2为优化
OBJSDIR = objs    #将生成文件放在一个文件夹里，不对文件的规范化造成危害
VPATH = add:sub    #定义搜索路径：add,sub和当前路径
OBJS = add_int.o add_float.o sub_int.o sub_float.o main.o
TARGET = cacu
RM = rm -rf

#生成cacu
#将OBJSDIR目录中的所有.o文件链接成cacu
#$(TARGET):$(OBJSDIR) $(OBJS)
#	$(CC) -o $(TARGET) $(OBJSDIR)/*.o $(CFLAGS)    
#将OBJS中所有扩展名为.o的文件替换为.c的文件
$(OBJS):%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $(OBJSDIR)/$@   #编译生成目标文件,存放在OBJSDIR目录中

$(OBJSDIR):
	mkdir -p ./$@    #建立目录，-p可以忽略父目录不存在的错误
clean: 
	-$(RM) $(TARGET) $(OBJSDIR)
