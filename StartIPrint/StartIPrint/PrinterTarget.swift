//
//  PrinterTarget.swift
//  StartIPrint
//
//  Created by lutery on 16/6/3.
//  Copyright © 2016年 lutery. All rights reserved.
//

import UIKit

class PrinterTarget{
    var type = PrinterType.null;
    var pageSize = CGSize(width: 210.0, height: 297.0);
    var resolution = CGPoint(x: 180, y: 180);
    private static var sInstance:PrinterTarget? = nil;
    
    init(){
        
    }
    
    class func getInstance()->PrinterTarget?{
        if (sInstance == nil){
            sInstance = PrinterTarget();
        }
        
        return sInstance;
    }
    
    class func PrinterBitmap(_ xPos:Int, yPos:Int, image:UIImage, paperSize:CGSize, dpi:CGPoint, num:UInt, parse:Parse){
        //
    }
    
//    var pageSizes;
}

enum PrinterType {
    case null, wifi, bluetooth, tofile;
}
