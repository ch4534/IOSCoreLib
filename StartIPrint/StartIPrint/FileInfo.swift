//
//  FileInfo.swift
//  StartIPrint
//
//  Created by lutery on 16/4/11.
//  Copyright © 2016年 lutery. All rights reserved.
//

import UIKit

// 文件信息类，用来表示文件以及文件夹信息
class FileInfo{
    // 获取以及设置文件的URI信息
    var FileUrl:String?{
        set(newValue){
            fileUrl = newValue;
            
            let lastOfslash = newValue?.rangeOfString("/", options: .BackwardsSearch, range: nil, locale: nil);
            
            if lastOfslash != nil{
                fileName = newValue?.substringFromIndex((lastOfslash?.startIndex)!.advancedBy(1));
            }
            else{
                fileName = newValue;
            }
        }
        get{
            return self.fileUrl;
        }
    };
    
    // 获取文件的类型
    var fileType:String?{
        get{
            
            if type == nil{
                let lastOfDot = fileUrl?.rangeOfString(".", options: .BackwardsSearch);
            
                if (lastOfDot != nil){
                    type = fileUrl?.substringFromIndex((lastOfDot?.startIndex)!);
                }
            }
            
            return type;
        }
    }
    
    // 获取文件的图标
    var fileIcon:UIImage{
        get{
            if icon == nil{
                if isFolder {
                    icon = FileInfo.typeIcon["folder"]!;
                }
                else{
                    var isFind = false;
                    let type = fileType;
            
                    if type != nil{
                        for key in FileInfo.typeIcon.keys{
                            if key == type! {
                                isFind = true;
                                break;
                            }
                        }
                    }
            
                    if isFind {
                        icon = FileInfo.typeIcon["type"]!;
                    }
                    else{
                        icon = FileInfo.unknowIcon!;
                    }
                }
            }
            
            return icon!;
        }
    }
    
    // 文件URI
    private var fileUrl:String?;
    // 文件类型
    private var type:String?;
    // 文件图标
    private var icon:UIImage?;
    // 文件名字
    var fileName:String?;
    // 是否是文件夹
    var isFolder:Bool = false;
    
    // 存储对应后缀名所对应的图标类型
    static var typeIcon:[String:UIImage] = [String:UIImage]();
    // 未知文件的图标
    static var unknowIcon = UIImage.init(named: "unknowfile");
}
