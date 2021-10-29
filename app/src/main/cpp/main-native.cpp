#include <jni.h>
#include <android/log.h>
#include <math.h>
#include <string>
#include <sstream>

using namespace std;
//
// Created by Ismoil on 28.10.2021.
//

#define log_d(TAG, MESSAGE)  __android_log_write(ANDROID_LOG_DEBUG, TAG, MESSAGE)

#define CONNECT_PACKAGE(NAME) Java_uz_gita_circleimage_MainActivity_##NAME
#define fun(TYPE, NAME, ...) JNIEXPORT TYPE JNICALL CONNECT_PACKAGE(NAME)(JNIEnv *env, jobject thiz, ## __VA_ARGS__)

//extern "C"
//JNIEXPORT void JNICALL
//Java_uz_gita_circleimage_MainActivity_makeCircle(JNIEnv *env, jobject thiz, jintArray data,jint width, jint height) {
//
//    int index, r;
//    int x, y;
//
//    // Get input data
//    jint *buffer = env->GetIntArrayElements(data, NULL);
//    env->ReleaseIntArrayElements(data, buffer, JNI_ABORT);
//
//
//    if (width > height) {
//        r = height / 2;
//    } else {
//        r = width / 2;
//    }
//
//
//    for (y = 0; y <= height - 1; y++) {
//        for (x = 0; x <= width - 1; x++) {
//            index = y * width + x;
//            bool b = ((x - width / 2) * (x - width / 2) + (y - height / 2) * (y - height / 2) >
//                      r * r);
//            if (b) {
//                buffer[index] = 0;
//            }
//        }
//    }
//
//
//    // Update output array
//    env->SetIntArrayRegion(data, 0, width * height, buffer);
//}

extern "C" {

    fun(jstring, getInfo) {
        return env->NewStringUTF("Salom");
    }

    fun(void , makeCircle, jintArray data, jint width, jint height){
        int index, r;
        int x, y;

        // Get input data
        jint *buffer = env->GetIntArrayElements(data, NULL);
        env->ReleaseIntArrayElements(data, buffer, JNI_ABORT);


        if (width > height) {
            r = height / 2;
        } else {
            r = width / 2;
        }


        for (y = 0; y <= height - 1; y++) {
            for (x = 0; x <= width - 1; x++) {
                index = y * width + x;
                bool b = ((x - width / 2) * (x - width / 2) + (y - height / 2) * (y - height / 2) >
                          r * r);
                if (b) {
                    buffer[index] = 0;
                }
            }
        }

        // Update output array
        env->SetIntArrayRegion(data, 0, width * height, buffer);
    }
}



//
//extern "C"
//JNIEXPORT void JNICALL
//Java_uz_gita_circleimage_MainActivity_ndkEmboss(JNIEnv *env, jobject thiz, jintArray data,
//                                                jint width, jint height) {
//
//    int i, index, pp, rr, gg, bb;
//    int *tem;
//    int x, y;
//    double Lx, Ly, Lz, NzLz, az, elev;
//    int Nx, Ny, Nz;
//    int yl, yr, xl, xr, v;
//    int i1, i2, i3, i4, i5, i6, i7, i8;
//
//
//    // Get input data
//    jint *buffer = env->GetIntArrayElements(data, NULL);
//    env->ReleaseIntArrayElements(data, buffer, JNI_ABORT);
//    tem = (int *) malloc(sizeof(int) * width * height);
//
//    // Populate into the output array as greyscale
//    for (i = 0; i < width * height; i++) {
//        pp = buffer[i];
//        rr = ((pp >> 16) & 0xff);
//        gg = ((pp >> 8) & 0xff);
//        bb = (pp & 0xff);
//        pp = (int) (rr * 0.3 + gg * 0.59 + bb * 0.11);
//        tem[i] = pp;
//    }
//
//    // Prepare the light source
//    az = 30 * 3.14159 / 180;
//    elev = 30 * 3.14159 / 180;
//    Lx = cos(az) * cos(elev) * 255;
//    Ly = sin(az) * cos(elev) * 255;
//    Lz = sin(elev) * 255;
//    Nz = (6 * 255) / 3;
//    NzLz = Nz * Lz;
//
//    // Apply the light source
//    for (y = 0; y <= height - 1; y++) {
//        for (x = 0; x <= width - 1; x++) {
//            index = y * width + x;
//            yl = (y - 1 + height) % height;
//            xl = (x - 1 + width) % width;
//            yr = (y + 1 + height) % height;
//            xr = (x + 1 + width) % width;
//            i1 = yl * width + xl;
//            i2 = yr * width + xr;
//            i3 = yr * width + xl;
//            i4 = yl * width + xr;
//            i5 = y * width + xl;
//            i6 = y * width + xr;
//            i7 = yr * width + x;
//            i8 = yl * width + x;
//            Nx = tem[i1] + tem[i5] + tem[i3] - tem[i4] - tem[i6]
//                 - tem[i2];
//            Ny = tem[i3] + tem[i7] + tem[i2] - tem[i1] - tem[i8]
//                 - tem[i4];
//            v = (int) (Nx * Lx + Ny * Ly + NzLz);
//            if (Nx == 0 && Ny == 0)
//                v = (int) Lz;
//            else if (v < 0)
//                v = 0;
//            else
//                v = (int) (v / sqrt(Nx * Nx + Ny * Ny + Nz * Nz));
//            v = (v > 255) ? 255 : ((v < 0) ? 0 : v);
//            buffer[index] = 0xff000000 | (v << 16) | (v << 8) | v;
//        }
//    }
//
//    free(tem);
//    // Update output array
//    env->SetIntArrayRegion(data, 0, width * height, buffer);
//}