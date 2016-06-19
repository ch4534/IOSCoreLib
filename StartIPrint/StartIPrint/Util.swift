//
//  Util.swift
//  StartIPrint
//
//  Created by lutery on 16/3/28.
//  Copyright © 2016年 lutery. All rights reserved.
//

import UIKit
import SystemConfiguration.CaptiveNetwork
import NetworkExtension

//@brief 通用工具类
class Util{
    
    // 获取屏幕的逻辑尺寸
    // @return 返回CGSize类型的屏幕尺寸
    class func getScreenSize()-> CGSize{
        //获取屏幕的逻辑分辨率
        let rect = UIScreen.main().bounds;
        //获取屏幕的缩放
//        let scale = UIScreen.mainScreen().scale;
        let scale:CGFloat = 1.0;
        //根据逻辑分辨率以及缩放比例获取屏幕的实际分辨率
        var screenSize = CGSize();
        screenSize.width = rect.size.width * scale;
        screenSize.height = rect.size.height * scale;
        
        return screenSize;
    }
    
    // 将制定的图像缩放到指定的尺寸
    // @param srcImage:UIImage 源图像
    // @param newSize:CGSize 目标尺寸
    // @return 返回缩放完成的图像
    class func resizeImage(_ srcImage:UIImage, newSize:CGSize) -> UIImage {
        UIGraphicsBeginImageContext(newSize);
        
        srcImage.draw(in: CGRect(x: 0, y: 0, width: newSize.width, height: newSize.height));
        
        let newImage = UIGraphicsGetImageFromCurrentImageContext();
        
        UIGraphicsEndImageContext();
        
        return newImage!;
    }
    
    class func showTipAlert(_ controller: UIViewController, message: String){
        let tipController = UIAlertController(title: "提示", message: message, preferredStyle: .alert);
        let sureAction = UIAlertAction(title: "确定", style: .destructive, handler: nil);
        
        tipController.addAction(sureAction);
        
        controller.present(tipController, animated: true, completion: nil);
    }
    
    class func IsIPad() -> Bool{
        let deviceType = UIDevice.current().model;
        let isFindIPad = deviceType.range(of: "iPad");
        
        if isFindIPad != nil {
            return true;
        }
        else {
            return false;
        }
    }
    
    class func getWifiName() -> NSString{
        let currentSSID = ""
        let interfaces = NEHotspotHelper.supportedNetworkInterfaces() as! [NEHotspotNetwork];
        for interface in interfaces{
            print("SSID = \(interface.ssid), BSSID = \(interface.bssid)");
        }
        
//        for interface in NEHotspotHelper.supportedNetworkInterfaces(){
//            if (interface.SSID != nil){
//                currentSSID = interface.SSID;
//            }
//        }
        
//        let interfaces = CNCopySupportedInterfaces()
//        if interfaces != nil {
//            let interfacesArray = Array(arrayLiteral: interfaces)
//            if interfacesArray.count > 0 {
//                let interfaceName =  String(interfacesArray[0])
//                let unsafeInterfaceData = CNCopyCurrentNetworkInfo(interfaceName)
//                if unsafeInterfaceData != nil {
//                    let interfaceData = unsafeInterfaceData as Dictionary!
//                    currentSSID = interfaceData[kCNNetworkInfoKeySSID] as! String
//                    let ssiddata = NSString(data:interfaceData[kCNNetworkInfoKeySSIDData]! as! NSData, encoding:NSUTF8StringEncoding) as! String
//                    // ssid data from hex
//                    print(ssiddata)
//                }
//            }
//        }
        return currentSSID
    }
    
//    class func convertUIImageToBitmapRGBA8(image:UIImage)->UnsafePointer<UInt8>{
//        let imageRef = image.CGImage;
//        let context =
//    }
    
//    private class func newBitmapRGBA8ContextFromImage(image:CGImageRef)->CGContextRef{
//        var context:CGContextRef? = nil;
//        var colorSpace:CGColorSpaceRef!;
//        
//    }
}

class TempImage{
    //缩放后的图像
    var scaleImage:UIImage?;
    //原始图像的路径
    var originImagePath:String = "";
    //原始图像的宽度
    var width = 0;
    //原始图像的高度
    var height = 0;
}
