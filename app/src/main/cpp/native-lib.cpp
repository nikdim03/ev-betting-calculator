#include <jni.h>
#include <string>

//extern "C" JNIEXPORT jstring JNICALL
//Java_com_example_betting_MainActivity_stringFromJNI(
//        JNIEnv *env,
//        jobject /* this */) {
//    std::string hello = "Hello from C++";
//    return env->NewStringUTF(hello.c_str());
//}
//
//extern "C" JNIEXPORT jstring JNICALL
//Java_com_example_betting_MainActivity_process(
//        JNIEnv *env,
//        jobject mainActivityInstance) {
//    const jclass mainActivityCls = env->GetObjectClass(mainActivityInstance);
//    const jmethodID jmethodId = env->GetMethodID(mainActivityCls, "processInJava",
//                                                 "()Ljava/lang/String;");
//    if (jmethodId == nullptr) {
//        return env->NewStringUTF("");
//    }
//
//    const jobject result = env->CallObjectMethod(mainActivityInstance, jmethodId);
//    const std::string java_msg = env->GetStringUTFChars((jstring) result, JNI_FALSE);
//    const std::string c_msg = "Result from Java => ";
//    const std::string msg = c_msg + java_msg;
//
//    return env->NewStringUTF(msg.c_str());
//}

extern "C" JNIEXPORT jdouble JNICALL
Java_com_example_betting_MainActivity_calculatePLose(JNIEnv *env, jobject activity) {
    jclass activityClass = env->GetObjectClass(activity);
    jmethodID getPWinMethodID = env->GetMethodID(activityClass, "getPWin", "()D");
    jdouble pWin = env->CallDoubleMethod(activity, getPWinMethodID);
    return 1.0 - pWin;
}

extern "C" JNIEXPORT jdouble JNICALL
Java_com_example_betting_MainActivity_calculateROI(JNIEnv *env, jobject activity) {
    jclass activityClass = env->GetObjectClass(activity);

    jmethodID getOddsMethodID = env->GetMethodID(activityClass, "getOdds", "()D");
    jdouble odds = env->CallDoubleMethod(activity, getOddsMethodID);

    jmethodID getPWinMethodID = env->GetMethodID(activityClass, "getPWin", "()D");
    jdouble pWin = env->CallDoubleMethod(activity, getPWinMethodID);
    jdouble pLose = 1 - pWin;

    jdouble roi = (pWin * (odds - 1.0) - pLose) * 100.0;
    return roi;
}

extern "C" JNIEXPORT jdouble JNICALL
Java_com_example_betting_MainActivity_calculateEV(JNIEnv *env, jobject activity) {
    jclass activityClass = env->GetObjectClass(activity);
    jmethodID getBankrollMethodID = env->GetMethodID(activityClass, "getBankroll", "()D");
    jdouble bankroll = env->CallDoubleMethod(activity, getBankrollMethodID);

    jmethodID getOddsMethodID = env->GetMethodID(activityClass, "getOdds", "()D");
    jdouble odds = env->CallDoubleMethod(activity, getOddsMethodID);

    jmethodID getPWinMethodID = env->GetMethodID(activityClass, "getPWin", "()D");
    jdouble pWin = env->CallDoubleMethod(activity, getPWinMethodID);

    jdouble pLose = 1.0 - pWin;
    jdouble ev = pWin * bankroll * (odds - 1.0) - (bankroll * pLose);
    return ev;
}

extern "C" JNIEXPORT jdouble JNICALL
Java_com_example_betting_MainActivity_calculateBankrollPercentage(JNIEnv *env, jobject activity) {
    jclass activityClass = env->GetObjectClass(activity);

    jmethodID getOddsMethodID = env->GetMethodID(activityClass, "getOdds", "()D");
    jdouble odds = env->CallDoubleMethod(activity, getOddsMethodID);

    jmethodID getPWinMethodID = env->GetMethodID(activityClass, "getPWin", "()D");
    jdouble pWin = env->CallDoubleMethod(activity, getPWinMethodID);

    jdouble pLose = 1.0 - pWin;
    return (((odds - 1.0) * pWin - pLose) / (odds - 1.0)) * 100.0;
}

extern "C" JNIEXPORT jdouble JNICALL
Java_com_example_betting_MainActivity_calculateBet(JNIEnv *env, jobject activity) {
    jclass activityClass = env->GetObjectClass(activity);
    jmethodID getBankrollMethodID = env->GetMethodID(activityClass, "getBankroll", "()D");
    jdouble bankroll = env->CallDoubleMethod(activity, getBankrollMethodID);

    jmethodID getPWinMethodID = env->GetMethodID(activityClass, "getPWin", "()D");
    jdouble pWin = env->CallDoubleMethod(activity, getPWinMethodID);

    jmethodID getOddsMethodID = env->GetMethodID(activityClass, "getOdds", "()D");
    jdouble odds = env->CallDoubleMethod(activity, getOddsMethodID);

    jdouble pLose = 1.0 - pWin;
    jdouble bankrollPercentage = (((odds - 1.0) * pWin - pLose) / (odds - 1.0)) * 100.0;

    jdouble bet = (bankrollPercentage / 100.0) * bankroll;
    return bet;
}