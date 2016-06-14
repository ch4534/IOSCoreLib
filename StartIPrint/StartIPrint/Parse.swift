//
//  Parse.swift
//  StartIPrint
//
//  Created by lutery on 16/3/28.
//  Copyright © 2016年 lutery. All rights reserved.
//

import Foundation
import UIKit

// 解析类型
enum ParseType {
    case image
    case File
}

// 解析类，用来将所支持的文件解析成图片
class Parse{
    // 图片类，用来防止传入的图片太大导致内存溢出
    var image:TempImage?;
    // 解析类型
    var type:ParseType?;
    // 总共页数
    private var countPage = 0;
    // 可接受解析的文件类型
    var acceptFileType = ["pdf", "jpg", "png", "bmp"];
    
    init(){
        
    }
    
    //初始化类，传入临时图片类
    init(image:TempImage){
        self.image = image;
        type = ParseType.image;
        countPage = 1;
    }
    
    //便利初始化类，对于解析图片创建临时图片类在这个里面，便利初始化类可以调用其他的构造函数进行进一步初始化
    convenience init(image:UIImage){
        //将原始图像保存早临时缓存文件夹
        let imagedata = UIImageJPEGRepresentation(image, 1.0);
        let paths = NSTemporaryDirectory();
        let tempFilePath = paths.stringByAppendingString("tempImage");
        imagedata?.writeToFile(tempFilePath, atomically: true);
        
        //获取屏幕的尺寸，创建临时图像，传入解析层
        let screenSize = Util.getScreenSize();
        let tempImage = TempImage();
        tempImage.width =  Int(Float(image.size.width));
        tempImage.height = Int(Float(image.size.height));
        tempImage.originImagePath = tempFilePath;
        tempImage.scaleImage = Util.resizeImage(image, newSize: screenSize);
        
        self.init(image:tempImage);
    }
    
    //获取总攻页数
    func countPages() -> Int{
//        var countPage = 0;
//        
//        if type != nil{
//            switch type! {
//            case .image:
//                countPage = 1;
//                
//            case .File:
//                countPage = 0;
//            
//            }
//        }
        
        return countPage;
    }
    
    //解析的状态
    //返回true表示解析成功，返回false表示解析失败
    func ParseStatus() -> Bool {
        if image != nil{
            return true;
        }
        
        return false;
    }
    
    //得到预览视图，
    func getPreviewImage(num:Int) -> UIImage?{
        var preview:UIImage? = nil;
        
        if type != nil && num < countPage{
            switch type! {
            case .image:
                preview = image?.scaleImage;
                
            case .File:
                preview = nil;
            }
        }
        
        return preview;
    }
    
    //得到页面的原始尺寸，也可以用来获取原始图像的比例
    func getPageSize(PageNumber i:Int) -> CGSize?{
        if i < countPage && type != nil {
            return CGSize(width: image!.width, height: image!.height);
        }
        
        return nil;
    }
    
    //得到指定比例尺寸的图像，可能会造成图像的变形
    func getPageImage(PageNumber i:Int, PageSize size: CGSize) -> UIImage?{
        if i < countPage && type != nil {
            switch type! {
            case .image:
                let originImage = UIImage(contentsOfFile: self.image!.originImagePath);
                return Util.resizeImage(originImage!, newSize: size)
                
            case .File:
                break;
            }
        }
        
        return nil;
    }
    
    //类方法，判断是否是可接受解析的数据类型
    class func IsAcceptType(fileName:String) -> Bool{
        return Parse().IsAcceptType(fileName);
    }
    
    //对象方法，判断是否是可接受解析的数据类型
    func IsAcceptType(fileName:String) -> Bool{
        let rangeDot = fileName.rangeOfString(".", options: .BackwardsSearch, range: nil, locale: nil);
        if rangeDot != nil {
            let fileType = fileName.substringFromIndex((rangeDot?.startIndex.advancedBy(1))!).lowercaseString;
            
            for type in acceptFileType {
                if fileType == type {
                    return true;
                }
            }
        }
        
        return false;
    }
}