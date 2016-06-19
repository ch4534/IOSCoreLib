//
//  FileBrowseUtil.swift
//  StartIPrint
//
//  Created by lutery on 16/4/11.
//  Copyright © 2016年 lutery. All rights reserved.
//

import UIKit

//浏览位置枚举 local本地 cloud云端
enum classBrowse{
    case local,cloud
}

//
// 文件浏览类
class FileBrowseUtil{
    
    //静态全局类，指向自身
    private static var gSelf:FileBrowseUtil?;
    //表示顶级目录，这里的顶级目录时Document目录
    private var topUrl:String?;
    //表示已经扫描到目录下面的文件
    private var listFiles = [FileInfo]();
    //表示当前文件浏览类浏览的是本地还是云端
    var whereBrowse = classBrowse.local;
    
    private init(){
//        let manager = NSFileManager.defaultManager();
//        let pathResImg = "\(NSBundle.mainBundle().bundlePath)/Resource/Image";
//        let fileenum = manager.enumeratorAtPath(pathResImg);
//        
//        for fileName in fileenum! {
//            
//        }
        
        //初始化生产icon,UIImage.init这里既可以从包中的文件路径生成，也可以从assets中生成
        FileInfo.typeIcon["bmp"] = UIImage.init(named: "bmp");
        FileInfo.typeIcon["folder"] = UIImage.init(named: "folder");
        FileInfo.typeIcon["pdf"] = UIImage.init(named: "pdf");
        FileInfo.typeIcon["prn"] = UIImage.init(named: "fileprint");
        FileInfo.typeIcon["png"] = UIImage.init(named: "bmp");
        FileInfo.typeIcon["jpg"] = UIImage.init(named: "bmp");
        FileInfo.typeIcon["doc"] = UIImage.init(named: "docx_win");
        FileInfo.typeIcon["docx"] = UIImage.init(named: "docx_win");
        
        //获取Document文件夹目录
        topUrl = NSSearchPathForDirectoriesInDomains(.documentDirectory, .userDomainMask, true)[0] as String;
    }
    
    // 获取文件浏览单例
    // 
    // return FileBrowseUtil 获取文件浏览单例可选值
    class func getInstance() -> FileBrowseUtil? {
        if gSelf == nil{
            gSelf = FileBrowseUtil();
        }
        
        return gSelf;
    }
    
    // 得到当前浏览的文件夹下的所有文件
    //
    // return [FileInfo]? 获取当前目录下所有的文件/文件夹数组可选值
    func getCurrentFiles() -> [FileInfo]?{
        return listFiles;
    }
    
    // 获取根目录下的所有文件
    //
    // return [FileInfo]? 获取根目录下的所有文件/文件夹数组的可选值
    func getRootFiles() -> [FileInfo]?{
        if topUrl != nil {
            return getFiles(topUrl!);
        }
        
        return nil;
    }
    
    // 获取指定路径下的所有文件
    func getFiles(_ url:String) -> [FileInfo]?{
        if InContainsUrl(url) && FileBrowseUtil.isDirectory(url) {
            do{
                listFiles.removeAll();
                let fileManager = FileManager.default();
                let fileNames = try fileManager.contentsOfDirectory(atPath: url);
            
                for name in fileNames {
                    let path = "\(url)/\(name)";
                    var isFolder:ObjCBool = false;
                    fileManager.fileExists(atPath: path, isDirectory: &isFolder);
                    
                    let fileInfo = FileInfo();
                    fileInfo.FileUrl = path;
                    
                    if isFolder {
                        fileInfo.isFolder = true;
                    }
                    
                    listFiles.append(fileInfo);
                }
                
                if topUrl != url {
                    let lastOfslash = url.range(of: "/", options: .backwardsSearch, range: nil, locale: nil);
                    let upUrl = url.substring(to: (lastOfslash?.lowerBound)!);
                    
                    let fileInfo = FileInfo();
                    fileInfo.FileUrl = upUrl;
                    fileInfo.fileName = "..";
                    fileInfo.isFolder = true;
                    
                    listFiles.insert(fileInfo, at: 0);
                }
                
                return listFiles;
            }
            catch {
                
            }
        }
        
        return nil;
    }
    
    // 判断传入的路径是否是文件夹
    // 
    // param url:String 传入需要判断的路径
    //
    // return Bool 返回true表示是文件夹，返回false表示不是文件夹
    class func isDirectory(_ url:String) -> Bool{
        var isFolder:ObjCBool = false;
        do{
            let fileManager = FileManager.default();
            fileManager.fileExists(atPath: url, isDirectory: &isFolder);
        }
        
        if isFolder {
            return true;
        }
        else{
            return false;
        }
    }
    
    // 判断当前的路径是否是顶级路径下
    //
    // param url:String 传入需要判断的路径
    //
    // return Bool 返回true表示是在顶级路径下，返回false表示不是在顶级路径下
    private func InContainsUrl(_ url:String) -> Bool{
        
        var bRet = true;
        
        repeat{
            if topUrl == nil {
                bRet = false;
                break;
            }
            
            if url.range(of: topUrl!) == nil{
                bRet = false;
                break;
            }
        } while(false);
        
        return bRet;
    }
    
    // 判断是否已经到了顶级目录
    //
    // param fileInfo FileInfo 传入需要判断的FileInfo
    //
    // return Bool 返回true表示已经是顶级目录了，返回false表示还没到顶级目录
    func IsTopUrl(_ fileInfo:FileInfo) -> Bool {
        
        var url = "";
        
        if fileInfo.isFolder {
            url = fileInfo.FileUrl!;
        }
        else {
            let tempUrl = fileInfo.FileUrl;
            let lastOfslash = tempUrl?.range(of: "/", options: .backwardsSearch, range: nil, locale: nil);
            
            if lastOfslash != nil {
//                url = (tempUrl?.substring(to: String.CharacterView.index(lastOfslash?.lowerBound, offsetBy: -1)));
//                url = (tempUrl?.substring(to: (lastOfslash?.index(lastOfslash?.startIndex, offsetBy: -1))!))!;
                url = (tempUrl?.substring(to: (tempUrl?.index((lastOfslash?.lowerBound)!, offsetBy: -1))!))!;
            }
        }
        
        return topUrl == url;
    }
}
