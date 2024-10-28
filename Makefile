#There are three main versions of the MingW:
# 1 - mingw32-gcc.exe the compiler will build 32-bit applications on 32-bit systems.
# 2 - i686-w64-mingw32-gcc.exe the compiler will build 32-bit applications on 64-bit systems.
# 3 - x86_64-w64-mingw32-gcc.exe the compiler will build 64-bit applications on 64-bit systems.

# Derleyiciler
CC32 = i686-w64-mingw32-gcc       # 32-bit derleyici (Windows)
CC64 = x86_64-w64-mingw32-gcc     # 64-bit derleyici (Windows)
CC_LINUX = gcc                    # Linux derleyicisi
WINDRES = windres                 # Resource compiler for Windows

# Derleme bayrakları
CFLAGS = -Wall -Wextra -std=c99
CFLAGS32 = $(CFLAGS)

# Hedef dosyalar
EXEC = StudyTimer
OUT = bin

# Kaynak dosyalar
SRC = $(wildcard src/*.c)

# Nesne dosyaları
OBJ64 = $(patsubst src/%.c,obj/64/%.o,$(SRC))
OBJ32 = $(patsubst src/%.c,obj/32/%.o,$(SRC))

# Windows 64-bit için ikon kaynak dosyası
ICON_RC = studyt.rc
ICON_RES = obj/64/studyt.res

# Windows 64-bit için
WIN64_EXE = $(OUT)/$(EXEC)_w64.exe
WIN_LDFLAGS = -Llib/w64 -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows -static

# Tüm hedefleri derle
all: clean $(WIN64_EXE)

# 64-bit nesne dosyalarını derleme
obj/64/%.o: src/%.c
	$(CC64) $(CFLAGS) -c $< -o $@

# İkon dosyasını .rc dosyasından .res dosyasına dönüştür
$(ICON_RES): $(ICON_RC)
	$(WINDRES) -O coff $< -o $@

# Windows 64-bit için derleme
$(WIN64_EXE): $(OBJ64) $(ICON_RES)
	$(CC64) $(OBJ64) $(ICON_RES) -o $@ $(WIN_LDFLAGS)

# Temizleme
clean:
	@rm -f $(WIN64_EXE) obj/64/*.o obj/64/*.res
