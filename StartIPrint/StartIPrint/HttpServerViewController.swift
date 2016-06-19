//
//  HttpServerViewController.swift
//  StartIPrint
//
//  Created by lutery on 16/5/17.
//  Copyright © 2016年 lutery. All rights reserved.
//

import UIKit

//
// 文件上传ViewController
class HttpServerViewController: UIViewController {

    // http地址标签
    @IBOutlet weak var httpAddress: UILabel!
    // 无线网络名称
    @IBOutlet weak var netName: UILabel!
    //上传进度
    @IBOutlet weak var uploadProgress: UIProgressView!
    //当前数据的上传进度
    private var currentDataLength:UInt64 = 0;
    
    //1GB字节数
    static let GBUnit = 1073741824;
    //1MB字节数
    static let MBUnit = 1048576;
    //1KB字节数
    static let KBUnit = 1024;
    
    //HttpServer对象
    var httpServer:HTTPServer?;
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        //初始化httpserver对象，设置链接类型以及监听端口
        httpServer = HTTPServer();
        httpServer?.setType("_http._tcp.");
        httpServer?.setPort(16918);
        //设置网页资源路径，设置上传文件保存路径，设置链接处理逻辑类
        let webPath = Bundle.main().bundlePath + "/website";
        print("webpath \(webPath)");
        httpServer?.setDocumentRoot(webPath);
        httpServer?.setConnectionClass(AYHTTPConnection);
        
//        print("SSID = \(Util.getWifiName())");
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated);
        
        //当视图显示的时候，启动Server，并添加四个相应的监听事件
        self.startServer();
        NotificationCenter.default().addObserver(self, selector: #selector(uploadWithStart), name: UPLOADSTART, object: nil);
        NotificationCenter.default().addObserver(self, selector: #selector(uploading),name: UPLOADING, object: nil);
        NotificationCenter.default().addObserver(self, selector: #selector(uploadWithEnd),name: UPLOADEND, object: nil);
        NotificationCenter.default().addObserver(self, selector: #selector(uploadWithDisconnect),name: UPLOADISCONNECTED, object: nil);
    }
    
    override func viewDidDisappear(_ animated: Bool) {
        super.viewDidDisappear(animated);
        
        //当视图消失的时候，关闭Server，并移除四个监听事件
        httpServer?.stop();
        NotificationCenter.default().removeObserver(self, name: NSNotification.Name(rawValue: UPLOADSTART), object: nil);
        NotificationCenter.default().removeObserver(self, name: NSNotification.Name(rawValue: UPLOADING), object: nil);
        NotificationCenter.default().removeObserver(self, name: NSNotification.Name(rawValue: UPLOADEND), object: nil);
        NotificationCenter.default().removeObserver(self, name: NSNotification.Name(rawValue: UPLOADISCONNECTED), object: nil);
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    /**
     启动服务器
     */
    func startServer(){
        if httpServer != nil{
            do{
                //启动服务器，并在界面上显示相应的端口名字以及监听端口
                try httpServer?.start();
                httpAddress.text = "http://\((httpServer!.hostName())!):\(httpServer!.listeningPort())";
            }
            catch{
                NSLog("Error Started HTTP Server");
            }
        }
    }
    
    /**
     上传启动监听函数，由于是私有函数，设置为监听对象需要添加@objc头
     
     - parameter notification: 存储相应的监听信息
     */
    @objc private func uploadWithStart(_ notification:Notification){
        let fileSize = (notification as NSNotification).userInfo!["totalfilessize"]?.int64Value;
//        var showFileSize = "";
        
        print("Upload Start And FileSize = \(fileSize)");
    }
    
    /**
     上传停止监听函数
     
     - parameter notification: 存储相应的监听信息
     */
    @objc private func uploadWithEnd(_ notification:Notification){
        print("Upload End");
    }
    
    /**
     上传断开连接监听函数
     
     - parameter notification: 存储相应的监听信息
     */
    @objc private func uploadWithDisconnect(_ notification:Notification){
        print("Upload Disconnect");
    }
    
    /**
     正在上传函数
     
     - parameter notification: 存储相应的监听信息
     */
    @objc private func uploading(_ notification:Notification){
        let value:Float = ((notification as NSNotification).userInfo!["progressvalue"]?.floatValue)!;
        currentDataLength += UInt64(((notification as NSNotification).userInfo!["cureentvaluelength"]?.int32Value)!);
        print("currentDataLength = \(currentDataLength), ProgressValue = \(value)");
    }
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
