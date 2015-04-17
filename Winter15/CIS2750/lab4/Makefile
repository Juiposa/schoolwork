JNI_HEADER = -I/usr/lib/jvm/java-1.*.0-openjdk-amd64/include  -I/usr/lib/jvm/java-1.*.0-openjdk-amd64/include/linux
LD_PATH = export LD_LIBRARY_PATH={LD_LIBRARY_PATH}:.

all: build
	
JNI_example.o:
	gcc -c -g -Wall -shared $(JNI_HEADER) jniC.c -o JNI_example.o -fPIC

build: JNI_example.o
	gcc -shared -Wl,-soname,libJNI_Example.so $(JNI_HEADER) -o libJNI_Example.so JNI_example.o 
	$(LD_PATH)