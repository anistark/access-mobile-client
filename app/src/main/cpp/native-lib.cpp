/*
* This file is part of the IOTA Access distribution
* (https://github.com/iotaledger/access)
*
* Copyright (c) 2020 IOTA Stiftung.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <jni.h>
#include <string>
#include <android/log.h>
#include <libauthdac.h>
#include <cstring>
#include <malloc.h>


// Android log function wrappers
static const char *kTAG = "jniAPILibDacAuthNative";
#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, kTAG, __VA_ARGS__))
#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))

#define SIGNATURE_LEN 64

// processing callback to handler class
typedef struct JniLibDacAuthContext {
    jclass libDacAuthClz;
    jobject libDacAuthObj;
    jobject socketObj;

} JniLibDacAuthContext_t;

JavaVM *javaVM = nullptr;

ssize_t read_socket(void *ext, void *data, unsigned short len) {
    JniLibDacAuthContext_t *ctx = (JniLibDacAuthContext_t *) ext;
    JNIEnv *env;

    LOGI("read_socket");

    javaVM->AttachCurrentThread(&env, nullptr);

    jmethodID receiveData = env->GetMethodID(ctx->libDacAuthClz, "ReceiveData",
                                             "(Lorg/iota/access/api/tcp/TCPSocketObject;[BS)I");

    if (receiveData == nullptr || env->ExceptionOccurred()) {
        env->ExceptionClear();
        // do smth in case of failure
        LOGE("read_socket sendData");
        return 0;
    }


    LOGI("read_socket");

    jbyteArray data_ = env->NewByteArray(len);

    jint ret = env->CallIntMethod(ctx->libDacAuthObj, receiveData, ctx->socketObj, data_, len);

    env->GetByteArrayRegion(data_, 0, len, (jbyte *) data);

    env->DeleteLocalRef(data_);
    LOGI("read_socket %d", ret);

    return ret;
}

ssize_t write_socket(void *ext, void *data, unsigned short len) {
    JniLibDacAuthContext_t *ctx = (JniLibDacAuthContext_t *) ext;
    JNIEnv *env;

    LOGI("write_socket");

    javaVM->AttachCurrentThread(&env, nullptr);

    jmethodID sendData = env->GetMethodID(ctx->libDacAuthClz, "SendData",
                                          "(Lorg/iota/access/api/tcp/TCPSocketObject;[BS)I");

    if (sendData == nullptr || env->ExceptionOccurred()) {
        env->ExceptionClear();
        // do smth in case of failure
        LOGE("write_socket receiveData");
        return 0;
    }

    LOGI("write_socket");

    jbyteArray data_ = env->NewByteArray(len);
    env->SetByteArrayRegion(data_, 0, len, (const jbyte *) data);

    jint ret = env->CallIntMethod(ctx->libDacAuthObj, sendData, ctx->socketObj, data_, len);

    env->DeleteLocalRef(data_);
    LOGI("write_socket %d", ret);

    return ret;
}

int verify(unsigned char *key, int len) {
    return 0;//DAC_OK;
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_iota_access_api_APILibDacAuthNative_dacInitClient(JNIEnv *env, jobject instance,
                                                           jlongArray session_, jobject socketObj) {
    if (session_ == nullptr) {
        return 0;
    }
    jlong *session = env->GetLongArrayElements(session_, nullptr);
    jint ret = 0;

    env->GetJavaVM(&javaVM);

    dacSession_t *dacSession = (dacSession_t *) malloc(sizeof(dacSession_t));
    JniLibDacAuthContext_t *jniLibDacAuthContext = (JniLibDacAuthContext_t *) malloc(
            sizeof(JniLibDacAuthContext_t));

    ret = (jint) dacInitClient(dacSession, jniLibDacAuthContext);
    dacSession->f_read = read_socket;
    dacSession->f_write = write_socket;
    dacSession->f_verify = verify;

    session[0] = (jlong) dacSession;

    jniLibDacAuthContext->libDacAuthClz = (jclass) env->NewGlobalRef(
            env->FindClass("org/iota/access/api/APILibDacAuthNative"));
    jniLibDacAuthContext->libDacAuthObj = env->NewGlobalRef(instance);
    jniLibDacAuthContext->socketObj = env->NewGlobalRef(socketObj);

    LOGI("APILibDacAuthNative_dacInitClient ret %d", ret);

    env->ReleaseLongArrayElements(session_, session, 0);
    return ret;
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_iota_access_api_APILibDacAuthNative_dacAuthenticate(JNIEnv *env, jobject instance,
                                                             jlongArray session_) {
    if (session_ == nullptr) {
        return 0;
    }
    jlong *session = env->GetLongArrayElements(session_, nullptr);
    dacSession_t *dacSession = (dacSession_t *) *session;
    jint ret = 0;

    ret = dacAuthenticate(dacSession);

    LOGI("APILibDacAuthNative_dacAuthenticate ret %d", ret);

    env->ReleaseLongArrayElements(session_, session, 0);
    return ret;
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_iota_access_api_APILibDacAuthNative_dacSetOption(JNIEnv *env, jobject instance,
                                                          jlongArray session_, jstring key_,
                                                          jbyteArray data_) {
    if (session_ == nullptr) {
        return 0;
    }
    jlong *session = env->GetLongArrayElements(session_, nullptr);
    const char *key = env->GetStringUTFChars(key_, nullptr);
    jbyte *data = env->GetByteArrayElements(data_, nullptr);
    dacSession_t *dacSession = (dacSession_t *) *session;
    jint ret = 0;

    // TODO: Write this
    dacSetOption(dacSession, key, (unsigned char *) data);
    LOGI("APILibDacAuthNative_dacSetOption ret %d", ret);

    env->ReleaseLongArrayElements(session_, session, 0);
    env->ReleaseStringUTFChars(key_, key);
    env->ReleaseByteArrayElements(data_, data, 0);
    return ret;
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_iota_access_api_APILibDacAuthNative_dacSend(JNIEnv *env, jobject instance,
                                                     jlongArray session_, jbyteArray data_,
                                                     jshort length) {
    if (session_ == nullptr) {
        return 0;
    }
    jlong *session = env->GetLongArrayElements(session_, nullptr);
    jbyte *data = env->GetByteArrayElements(data_, nullptr);
    dacSession_t *dacSession = (dacSession_t *) *session;
    jint ret = 0;

    // TODO: test this

    LOGI("APILibDacAuthNative_dacSend");
    ret = dacSend(dacSession, (const unsigned char *) data, length);

    env->ReleaseByteArrayElements(data_, data, 0);
    env->ReleaseLongArrayElements(session_, session, 0);
    return ret;
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_iota_access_api_APILibDacAuthNative_dacReceive(JNIEnv *env, jobject instance,
                                                        jlongArray session_, jbyteArray data_,
                                                        jshort length) {
    if (session_ == nullptr) {
        return 0;
    }
    jlong *session = env->GetLongArrayElements(session_, nullptr);
    jbyte *data = env->GetByteArrayElements(data_, nullptr);
    dacSession_t *dacSession = (dacSession_t *) *session;
    jint ret = 0;

    // TODO: test this

    LOGI("APILibDacAuthNative_dacReceive");
    ret = dacReceive(dacSession, (unsigned char **) &data, (unsigned short *) &length);

    env->ReleaseLongArrayElements(session_, session, 0);
    env->ReleaseByteArrayElements(data_, data, 0);
    return ret;
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_iota_access_api_APILibDacAuthNative_dacRelease(JNIEnv *env, jobject instance,
                                                        jlongArray session_) {
    if (session_ == nullptr) {
        return 0;
    }
    jlong *session = env->GetLongArrayElements(session_, nullptr);
    dacSession_t *dacSession = (dacSession_t *) *session;
    jint ret = 0;

    // TODO: release object references
    ret = dacRelease(dacSession);

    LOGI("APILibDacAuthNative_dacRelease");

    env->ReleaseLongArrayElements(session_, session, 0);
    return ret;
}
//
//extern "C"
//JNIEXPORT jint JNICALL
//Java_org_iota_access_api_APILibDacAuthNative_cryptoSign(
//        JNIEnv *env,
//        jobject thiz,
//        jbyteArray signature,
//        jbyteArray message,
//        jbyteArray private_key
//) {
//    int ret = 0;
//    jbyte *message_jbyte = env->GetByteArrayElements(message, nullptr);
//    jbyte *prv_key = env->GetByteArrayElements(private_key, nullptr);
//
//    size_t message_len = strlen((char *) message_jbyte);
//
//    unsigned long long signed_message_len = 0;
//
//    char *signed_message = (char *) malloc((message_len + SIGNATURE_LEN) * sizeof(char));
//
//    jbyte signature_[SIGNATURE_LEN] = {0};
//
//    ret = cryptoSign(
//            (unsigned char *) signed_message,
//            &signed_message_len,
//            (unsigned char *) message_jbyte,
//            (unsigned long long) message_len, (unsigned char *) prv_key);
//
//    memcpy(signature_, signed_message, SIGNATURE_LEN);
//
//    env->ReleaseByteArrayElements(signature, signature_, 0);
//
//    free(signed_message);
//
//    return ret;
//}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_org_iota_access_api_APILibDacAuthNative_cryptoSign(
        JNIEnv *env,
        jobject thiz,
        jbyteArray message,
        jbyteArray private_key
) {
    jbyteArray signature = env->NewByteArray(SIGNATURE_LEN);
    jbyte *message_jbyte = env->GetByteArrayElements(message, nullptr);
    jbyte *prv_key = env->GetByteArrayElements(private_key, nullptr);

    size_t message_len = strlen((char *) message_jbyte);

    unsigned long long signed_message_len = 0;

    char *signed_message = (char *) malloc((message_len + SIGNATURE_LEN) * sizeof(char));

    cryptoSign(
            (unsigned char *) signed_message,
            &signed_message_len,
            (unsigned char *) message_jbyte,
            (unsigned long long) message_len, (unsigned char *) prv_key);

    env->SetByteArrayRegion(
            signature,
            0,
            SIGNATURE_LEN,
            reinterpret_cast<const jbyte *>(signed_message));

    free(signed_message);

    return signature;
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_iota_access_api_APILibDacAuthNative_generateKeyPair(
        JNIEnv *env,
        jobject thiz,
        jbyteArray public_key,
        jbyteArray private_key
) {
    int ret;

    jbyte *pub_key = env->GetByteArrayElements(public_key, nullptr);
    jbyte *prv_key = env->GetByteArrayElements(private_key, nullptr);

    ret = cryptoSignKeypair((unsigned char *) pub_key, (unsigned char *) prv_key);

    env->ReleaseByteArrayElements(public_key, pub_key, 0);
    env->ReleaseByteArrayElements(private_key, prv_key, 0);

    return ret;
}
