# 컴파일러 및 옵션 설정
CC = gcc
CFLAGS = -I src -fexec-charset=UTF-8
TARGET = my_compiler

# 소스 파일 및 생성 파일 정의
SRCS = src/main.c src/parser.tab.c src/lex.yy.c src/ast.c src/codegen.c
OBJS = $(SRCS:.c=.o)

# 기본 타겟: make만 치면 실행됨
all: $(TARGET)

# 컴파일러 생성 규칙
$(TARGET): src/parser.tab.c src/lex.yy.c
	$(CC) -o $(TARGET) $(SRCS) $(CFLAGS)
	@echo "Build Successful! Run ./$(TARGET) <input_file>"

# Parser 생성 (Bison)
src/parser.tab.c src/parser.tab.h: src/parser.y
	bison -d -o src/parser.tab.c src/parser.y

# Scanner 생성 (Flex)
src/lex.yy.c: src/scanner.l src/parser.tab.h
	flex -o src/lex.yy.c src/scanner.l

# 청소 규칙 (만들어진 파일 삭제)
clean:
	rm -f src/lex.yy.c src/parser.tab.c src/parser.tab.h $(TARGET) $(TARGET).exe out.s program program.exe

# 가짜 타겟 (파일 이름과 겹치지 않도록)
.PHONY: all clean