//
//  main.m
//  iOSAppWithPureC
//
//  Created by Su XinDe on 16/1/26.
//  Copyright © 2016年 com.su. All rights reserved.
//

#include <CoreFoundation/CoreFoundation.h>
#include <objc/runtime.h>
#include <objc/message.h>

extern int UIApplicationMain(int, ...);

int main(int argc, char * argv[]) {
   
    id autoreleasePool = objc_msgSend(objc_msgSend(objc_getClass("NSAutoreleasePool"), sel_registerName("alloc")), sel_registerName("init"));
    
    int ret = UIApplicationMain(argc, argc, nil, CFSTR("AppDelegate"));
    
    objc_msgSend(autoreleasePool, sel_registerName("drain"));
    
    return ret;

}
