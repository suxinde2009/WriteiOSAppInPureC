//
//  AppDelegate.c
//  iOSAppWithPureC
//
//  Created by Su XinDe on 16/1/26.
//  Copyright © 2016年 com.su. All rights reserved.
//

#include <objc/runtime.h>
#include <objc/message.h>
#include <objc/objc.h>
#include <CoreGraphics/CoreGraphics.h>

// http://stackoverflow.com/questions/10289890/how-to-write-ios-app-purely-in-c/10290255#10290255

struct AppDel {
    
    Class isa;
    
    id window;

};

Class AppDelClass;

BOOL AppDel_didFinishLaunching(struct AppDel *self, SEL _cmd, void *application, void *options) {
    
    self->window = objc_msgSend(objc_getClass("UIWindow"), sel_getUid("alloc"));
   
    self->window = objc_msgSend(self->window, sel_getUid("initWithFrame:"), (struct CGRect){0, 0, 320, 568});

    id viewController = objc_msgSend(objc_msgSend(objc_getClass("UIViewController"), sel_getUid("alloc")), sel_getUid("init"));
    
    id view = objc_msgSend(objc_msgSend(objc_getClass("View"), sel_getUid("alloc")),
                           sel_getUid("initWithFrame:"),
                           (struct CGRect){0,0,320, 568});
    
    objc_msgSend(objc_msgSend(viewController, sel_getUid("view")), sel_getUid("addSubview:"), view);
    objc_msgSend(self->window, sel_getUid("setRootViewController:"), viewController);
    
    objc_msgSend(self->window, sel_getUid("makeKeyAndVisible"));

    return YES;
}


// http://stackoverflow.com/questions/2053029
__attribute__((constructor))
static void initAppDel()
{
    AppDelClass = objc_allocateClassPair((Class) objc_getClass("UIResponder"), "AppDelegate", 0);
    
    class_addIvar(AppDelClass, "window", sizeof(id), 0, "@");
    
    class_addMethod(AppDelClass, sel_getUid("application:didFinishLaunchingWithOptions:"), (IMP) AppDel_didFinishLaunching, "i@:@@");
    
    objc_registerClassPair(AppDelClass);
}