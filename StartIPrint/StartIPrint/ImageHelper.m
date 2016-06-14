//
//  ImageHelper.m
//  StartIPrint
//
//  Created by lutery on 16/6/13.
//  Copyright © 2016年 lutery. All rights reserved.
//

#import "ImageHelper.h"

@implementation ImageHelper

/**
 *  将UIImage转换为rgba裸数据
 *
 *  @param image <#image description#>
 *
 *  @return <#return value description#>
 */
+ (unsigned char *) convertUIImageToBitmapRGBA8:(UIImage*)image{
    CGImageRef imageRef = image.CGImage;
    
    CGContextRef context = [self newBitmapRGBA8ContextFromImage:imageRef];
    
    if (!context){
        return NULL;
    }
    
    size_t width = CGImageGetWidth(imageRef);
    size_t height = CGImageGetHeight(imageRef);
    
    CGRect rect = CGRectMake(0, 0, width, height);
    
    CGContextDrawImage(context, rect, imageRef);
    
    unsigned char* bitmapData = (unsigned char*)CGBitmapContextGetData(context);
    
    size_t bytesPerRow = CGBitmapContextGetBytesPerRow(context);
    size_t bufferLength = bytesPerRow * height;
    
    unsigned char* newBitmap = NULL;
    
    if (bitmapData){
        newBitmap = (unsigned char*)malloc(sizeof(unsigned char) * bytesPerRow * height);
        
        if (newBitmap){
            for (int i = 0; i < bufferLength; ++i){
                newBitmap[i] = bitmapData[i];
            }
        }
        
        free(bitmapData);
    }
    else{
        NSLog(@"Error getting bitmap pixel data\n");
    }
    
    CGContextRelease(context);
    
    return newBitmap;
}

+ (CGContextRef) newBitmapRGBA8ContextFromImage:(CGImageRef)image {
    CGContextRef context = NULL;
    CGColorSpaceRef colorSpace;
    uint32_t* bitmapData;
    
    size_t bitsPerPixel = 32;
    size_t bitsPerComponent = 8;
    size_t bytesPerPixel = bitsPerPixel / bitsPerComponent;
    
    size_t width = CGImageGetWidth(image);
    size_t height = CGImageGetHeight(image);
    
    size_t bytesPerRow = width * bytesPerPixel;
    size_t bufferLength = bytesPerRow * height;
    
    colorSpace = CGColorSpaceCreateDeviceRGB();
    
    if (!colorSpace){
        NSLog(@"Error allocting color space RGB\n");
        return NULL;
    }
    
    bitmapData = (uint32_t*)malloc(bufferLength);
    
    if (!bitmapData){
        NSLog(@"Error allocating memory for bitmap\n");
        CGColorSpaceRelease(colorSpace);
        return NULL;
    }
    
    context = CGBitmapContextCreate(bitmapData, width, height, bitsPerComponent, bytesPerRow, colorSpace, kCGImageAlphaPremultipliedLast);
    
    if (!context){
        free(bitmapData);
        NSLog(@"Bitmap context not created");
    }
    
    CGColorSpaceRelease(colorSpace);
    
    return context;
}

+ (UIImage*) convertBitmapRGBA8ToUIImage:(unsigned char *)buffer withWidth:(int)width withHeight:(int)height{
    size_t bufferLength = width * height * 4;
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, buffer, bufferLength, NULL);
    size_t bitsPerComponent = 8;
    size_t bitsPerPixel = 32;
    size_t bytesPerRow = 4 * width;
    
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    if (colorSpaceRef == NULL){
        NSLog(@"Error allocating color space");
        return nil;
    }
    
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
    
    CGImageRef iref = CGImageCreate(width, height, bitsPerComponent, bitsPerPixel, bytesPerRow, colorSpaceRef, bitmapInfo, provider, NULL, YES, renderingIntent);
    
    uint32_t* pixels = (uint32_t*)malloc(bufferLength);
    
    if (pixels == NULL){
        NSLog(@"Error: Memory allocated for bitmap");
        CGDataProviderRelease(provider);
        CGColorSpaceRelease(colorSpaceRef);
        CGImageRelease(iref);
        return nil;
    }
    
    CGContextRef context = CGBitmapContextCreate(pixels, width, height, bitsPerComponent, bytesPerRow, colorSpaceRef, kCGImageAlphaPremultipliedLast);
    
    if (context == NULL){
        NSLog(@"Error context not created");
        free(pixels);
    }
    
    UIImage* image = nil;
    
    if (context){
        CGContextDrawImage(context, CGRectMake(0.0f, 0.0f, width, height), iref);
        
        CGImageRef imageRef = CGBitmapContextCreateImage(context);
        
        if ([UIImage respondsToSelector:@selector(imageWithCGImage:scale:orientation:)]){
            float scale = [[UIScreen mainScreen]scale];
            image = [UIImage imageWithCGImage:imageRef scale:scale orientation:UIImageOrientationUp];
        }
        else{
            image = [UIImage imageWithCGImage:imageRef];
        }
        
        CGImageRelease(imageRef);
        CGContextRelease(context);
    }
    
    CGColorSpaceRelease(colorSpaceRef);
    CGImageRelease(iref);
    CGDataProviderRelease(provider);
    
    if (pixels){
        free(pixels);
    }
    
    return image;
}

@end


