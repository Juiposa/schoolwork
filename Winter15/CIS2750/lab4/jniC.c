#include <stdio.h>
#include <jni.h>
#include "JNI_example.h"

JNIEXPORT void JNICALL Java_JNI_1example_printHello (JNIEnv * env, jclass obj) {
	printf("Hello C world.\n");
}