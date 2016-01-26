/*
 The MIT License (MIT)
 
 Copyright (c) 2016 SuXinDe (Email: suxinde2009@126.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include <objc/runtime.h>
#include <objc/message.h>
#include <objc/objc.h>
#include <CoreGraphics/CoreGraphics.h>

// 参考: http://stackoverflow.com/questions/10289890/how-to-write-ios-app-purely-in-c/10290255#10290255

//
struct AppDel {
    
    Class isa;
    
    id window;

};


// 等价于 [AppDelegate class])
Class AppDelClass;

// 应用程序入口，等价于-application:didFinishLaunchingWithOptions:
BOOL AppDel_didFinishLaunching(struct AppDel *self, SEL _cmd, id application, id options) {
//BOOL AppDel_didFinishLaunching(struct AppDel *self, SEL _cmd, void *application, void *options) {
    
    // 创建UIWindow
    self->window = objc_msgSend(objc_getClass("UIWindow"), sel_getUid("alloc"));
   
    // 设置window大小，此处没有设置LauchImage, 所以硬编码 568依旧显示为480
    self->window = objc_msgSend(self->window, sel_getUid("initWithFrame:"), (struct CGRect){0, 0, 320, 568});
    
    // 创建viewController
    id viewController = objc_msgSend(objc_msgSend(objc_getClass("UIViewController"), sel_getUid("alloc")), sel_getUid("init"));

    // 创建viewController的中间的自定义绿色视图
    id view = objc_msgSend(objc_msgSend(objc_getClass("View"), sel_getUid("alloc")),
                           sel_getUid("initWithFrame:"),
                           (struct CGRect){0,0,320, 568});
    // 将view添加到viewController.view上
    objc_msgSend(objc_msgSend(viewController, sel_getUid("view")), sel_getUid("addSubview:"), view);
    
    // window设置rootViewController
    objc_msgSend(self->window, sel_getUid("setRootViewController:"), viewController);
    
    // 等价于[window makeKeyAndVisible];
    objc_msgSend(self->window, sel_getUid("makeKeyAndVisible"));

    return YES;
}

// gcc attribute extension (constructor)
// http://stackoverflow.com/questions/2053029
__attribute__((constructor))
static void initAppDel()
{
    // 创建一个UIResponder的子类AppDelegate
    AppDelClass = objc_allocateClassPair((Class) objc_getClass("UIResponder"), "AppDelegate", 0);
    
    // 用oc runtime给AppDelegate添加成员变量window
    class_addIvar(AppDelClass, "window", sizeof(id), 0, "@");
    
    // 用oc runtime给AppDelegate添加成员方法 -application:didFinishLaunchingWithOptions:
    class_addMethod(AppDelClass, sel_getUid("application:didFinishLaunchingWithOptions:"), (IMP) AppDel_didFinishLaunching, "i@:@@");
    
    // 注册AppDelClass
    objc_registerClassPair(AppDelClass);
}