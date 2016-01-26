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

#include <stdio.h>
#include <objc/runtime.h>
#include <CoreGraphics/CoreGraphics.h>

Class ViewClass;

extern CGContextRef UIGraphicsGetCurrentContext();

// drawRect: 实现
void View_drawRect(id self, SEL _cmd, CGRect rect)
{
    // 获取上下文
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    // 设置view背景色 rgba
    CGContextSetFillColor(context, (CGFloat []){ 1, 1, 1, 1 });

    // 设置填充区域
    CGContextAddRect(context, (struct CGRect) { 0, 0, 320, 568 });
    CGContextFillPath(context);
    
    // 设置绿色自定义绘图区域颜色
    CGContextSetFillColor(context, (CGFloat []) { 0, 1, 0, 1 });
    // 设置绿色自定义绘图区域大小
    CGContextAddRect(context, (struct CGRect) { 130, 200, 60, 60 });
    CGContextFillPath(context);
}


__attribute__((constructor))
static void initView()
{
    // 创建UIView的子类View
    ViewClass = objc_allocateClassPair((Class) objc_getClass("UIView"), "View", 0);

    // 给View添加一个drawRect:方法
    class_addMethod(ViewClass, sel_getUid("drawRect:"), (IMP) View_drawRect, "v@:");

    // 注册ViewClass
    objc_registerClassPair(ViewClass);
}