//
//  View.c
//  iOSAppWithPureC
//
//  Created by Su XinDe on 16/1/26.
//  Copyright © 2016年 com.su. All rights reserved.
//

#include <stdio.h>
#include <objc/runtime.h>
#include <CoreGraphics/CoreGraphics.h>

Class ViewClass;

extern CGContextRef UIGraphicsGetCurrentContext();

// drawRect:
void View_drawRect(id self, SEL _cmd, CGRect rect)
{
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    CGContextSetFillColor(context, (CGFloat []){ 1, 1, 1, 1 });
    
    CGContextAddRect(context, (struct CGRect) { 0, 0, 320, 568 });
    CGContextFillPath(context);
    
    CGContextSetFillColor(context, (CGFloat []) { 0, 1, 0, 1 });
    CGContextAddRect(context, (struct CGRect) { 130, 200, 60, 60 });
    CGContextFillPath(context);
}


__attribute__((constructor))
static void initView()
{
    ViewClass = objc_allocateClassPair((Class) objc_getClass("UIView"), "View", 0);

    class_addMethod(ViewClass, sel_getUid("drawRect:"), (IMP) View_drawRect, "v@:");
    
    objc_registerClassPair(ViewClass);
}