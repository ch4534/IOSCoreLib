//
//  FileBrowseViewController.swift
//  StartIPrint
//
//  Created by lutery on 16/4/5.
//  Copyright © 2016年 lutery. All rights reserved.
//

import UIKit

//文档浏览类，用来浏览选择document文件夹下的文件
class FileBrowseViewController:UITableViewController/*,UINavigationControllerDelegate, UINavigationBarDelegate */{

    //单元格的id
    private let filebrocellId = "filebrowsecell";
    //当前文件夹下的文件列表
    private var listOfFile:[FileInfo]?;
    
//    @IBOutlet weak var fileTableView: UITableView!
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        listOfFile = FileBrowseUtil.getInstance()?.getRootFiles();
        tableView.tableFooterView = UIView();
        
//        let returnButton = UIBarButtonItem(barButtonSystemItem: .FastForward, target: self, action: #selector(popAction));
//        self.navigationItem.leftBarButtonItem = returnButton;
        
//        self.navigationController?.navigationBar.delegate = self;
//        self.navigationItem.leftBarButtonItem = UIBarButtonItem(title: "返回", style: UIBarButtonItemStyle.Plain, target: self, action: #selector(popAction));
        
        let addButton = UIBarButtonItem(barButtonSystemItem: .Add, target: self, action: #selector(importFileToPrint));
        self.navigationItem.rightBarButtonItem = addButton;
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    // 返回tableview显示的item个数
    //
    // param tableView: UITableView 控件
    // param numberOfRowsInSection section: Int 相应section的索引
    //
    // return Int 返回相应section的items个数
    override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return (listOfFile?.count)!;
    }
    
    // 返回当前显示tableview的section的个数
    //
    // param tableView UITableView 控件引用
    //
    // return Int 返回section个数
    override func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return 1;
    }
    
    // 返回显示的cell
    //
    // param tableView UITableView 控件索引
    // param cellForRowAtIndexPath indexPath: NSIndexPath 包含当前是第几个section第几个item
    // 
    // return UITableViewCell 返回cell
    override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier(filebrocellId, forIndexPath: indexPath);
        
        let fileInfo = listOfFile![indexPath.row];
        cell.imageView?.image = fileInfo.fileIcon;
        cell.textLabel?.text = fileInfo.fileName;
        
        return cell;
    }
    
    // 点击item委托协议
    //
    // param tableView UITableView 控件引用
    // param didSelectRowAtIndexPath indexPath: NSIndexPath 包含当前是第几个section第几item
    override func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {
        let fileInfo = listOfFile![indexPath.row];
        //如果当前是文件夹，那么获取文件夹下的所有文件
        if fileInfo.isFolder {
            listOfFile = FileBrowseUtil.getInstance()?.getFiles(fileInfo.FileUrl!);
            tableView.reloadData();
        }
        else {
            //如果当前是文件，判断是否是支持的文件
            if Parse.IsAcceptType(fileInfo.fileName!) {
                let mainStoryboard = UIStoryboard(name: "Main", bundle: nil);
                let docPrint = mainStoryboard.instantiateViewControllerWithIdentifier("siDocPrint") as! DocViewController;
                
                let image = UIImage(contentsOfFile: fileInfo.FileUrl!);
                
                let parseLayer = Parse(image: image!);
                docPrint.parseLayer = parseLayer;
                
                self.navigationController?.pushViewController(docPrint, animated: true);
            }
            else {
//                showTipController("不支持此格式文件的解析");
                Util.showTipAlert(self, message: "不支持此文件格式的解析");
            }
        }
    }
    
//    private func showTipController(tip:String){
//        let tipController = UIAlertController(title: "提示", message: tip, preferredStyle: .Alert);
//        let sureAction = UIAlertAction(title: "确定", style: .Destructive, handler: nil);
//        
//        tipController.addAction(sureAction);
//        
//        self.presentViewController(tipController, animated: true, completion: nil);
//    }
    
    /**
     对于私有方法来说，selector需要添加@objc才能被识别到
     */
    @objc private func importFileToPrint(){
        print("importFileToPrint");
        
        let mainStoryboard = UIStoryboard(name: "Main", bundle: nil);
        let httpServerController = mainStoryboard.instantiateViewControllerWithIdentifier("importController");
//        if Util.IsIPad() {
//            httpServerController.modalPresentationStyle = .Popover;
//            httpServerController.popoverPresentationController?.sourceView = self.view;
//            httpServerController.popoverPresentationController?.sourceRect = CGRectZero;
//            
//            self.presentViewController(httpServerController, animated: true, completion: nil);
//            let popoverController = UIPopoverController(contentViewController: httpServerController);
//            let mainFrame = self.view.frame;
//            var origin = CGPoint();
//            let width = mainFrame.width * 0.5;
//            let height = mainFrame.height * 0.5;
//            origin.x = CGFloat(mainFrame.width / 2 - width / 2);
//            origin.y = CGFloat(mainFrame.height / 2 - height / 2);
//            
//            let showFrame = CGRect(origin: origin, size: CGSize(width: width, height: height));
//            popoverController.presentPopoverFromRect(showFrame, inView: self.view, permittedArrowDirections: .Unknown, animated: true);
//        }
//        else{
            self.navigationController?.pushViewController(httpServerController, animated: true);
//        }
    }
    
//    func popAction(){
//        
//        
//    }
//
//    func navigationBar(navigationBar: UINavigationBar, shouldPopItem item: UINavigationItem) -> Bool {
//        print("should pop item");
//        return true;
//    }

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}
