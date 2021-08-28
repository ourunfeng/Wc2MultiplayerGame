#include <GUI/GUIElement.h>
#include <easytech.h>
#include <CStateManager/CMenuState.h>
#include <jni.h>

static JavaVM *g_vm = NULL;

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved){
    JNIEnv* env = NULL;
    if (vm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK)
        return JNI_ERR;
    g_vm = vm;
    return JNI_VERSION_1_6;
}

def_easytech(_ZN10CMenuState7OnEventERK5Event)
bool CMenuState::OnEvent(const Event &event){
    switch (event.type) {
        case Event::GUI : {
            switch (event.info.GUI.type) {
                case Event::info::GUI::Other : {
                    switch (event.info.GUI.info){
                        case OTHER_HOME:{
                            JNIEnv* env = NULL;
                            if (g_vm != NULL && (g_vm->GetEnv((void**) &env, JNI_VERSION_1_6) == JNI_OK)){
                                jclass cls_activity = env->FindClass("com/easytech/wc2/ModActivity");
                                jmethodID mtd_getInfoPopup = env->GetStaticMethodID(cls_activity,"getInfoPopup","()Lcom/easytech/wc2/InfoPopup;");
                                jobject obj_infoPopup = env->CallStaticObjectMethod(cls_activity,mtd_getInfoPopup);
                                jclass cls_infoPopup = env->FindClass("com/easytech/wc2/InfoPopup");
                                jmethodID mtd_showOnUiThread = env->GetMethodID(cls_infoPopup,"showOnUiThread","()V");
                                if (obj_infoPopup != NULL){
                                    env->CallVoidMethod(obj_infoPopup ,mtd_showOnUiThread);
                                    return false;
                                }
                            }

                        }
                    }
                }
            }
        }
    }
    return easytech(_ZN10CMenuState7OnEventERK5Event)(this,&event);
}