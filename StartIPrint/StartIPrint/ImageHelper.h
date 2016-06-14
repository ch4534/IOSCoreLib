//
//  ImageHelper.h
//  StartIPrint
//
//  Created by lutery on 16/6/13.
//  Copyright © 2016年 lutery. All rights reserved.
//

#ifndef ImageHelper_h
#define ImageHelper_h

#import <Foundation/Foundation.h>
@import UIKit;

@interface ImageHelper : NSObject{
    
}

+ (unsigned char *) convertUIImageToBitmapRGBA8:(UIImage* )image;

+ (CGContextRef) newBitmapRGBA8ContextFromImage:(CGImageRef)image;

+ (UIImage*) convertBitmapRGBA8ToUIImage:(unsigned char *)buffer withWidth:(int)width withHeight:(int)height;

@end


#endif /* ImageHelper_h */
