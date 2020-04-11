TAR:hello
OBJ:hello.o
ASM:hello.s
PCF:hello.i

cc :=gcc

$(TAR):$(OBJ)
	cc $(OBJ) -o $(TAR) 
$(OBJ):$(ASM)
	cc -c $(ASM) -o $(OBJ)
$(ASM):$(PCF)
	cc -S $(PCF) -o $(ASM)
$(PCF):hello.c
	cc -E hello.c -o $(PCF)

#伪目标
.PHONY:clean
clean:
	rm -rf *.o *.s *.i
