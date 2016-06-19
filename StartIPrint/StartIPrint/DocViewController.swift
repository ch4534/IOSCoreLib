//
//  DocViewController.swift
//  StartIPrint
//
//  Created by lutery on 16/4/4.
//  Copyright © 2016年 lutery. All rights reserved.
//

import UIKit

/// @brief 文档打印预览Controller对象，继承表格委托以及表格视图数据源委托
class DocViewController: UIViewController, UITableViewDelegate, UITableViewDataSource{
    
    //解析对象
    var parseLayer : Parse?;
    //预览视图的id，如果不是在故事版tableview中的cell，还必须要注册后才能使用
    let idpreviewCell = "previewCell";
    
    //弱引用故事版表格控件
    @IBOutlet weak var tableView: UITableView!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        tableView.delegate = self;
        tableView.dataSource = self;
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        if let parse = parseLayer {
            return parse.countPages();
        }
        
        return 0;
    }
    
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1;
    }

    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: idpreviewCell, for: indexPath) as? DocViewPreviewCell;
        cell?.previewImage.image = parseLayer?.getPreviewImage((indexPath as NSIndexPath).row);
        
        return cell!;
    }
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return (parseLayer?.getPreviewImage((indexPath as NSIndexPath).row)?.size.height)!;
    }
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */
    @IBAction func startPrint(_ sender: AnyObject) {
        print("Start To Print");
        let countPage = (parseLayer?.countPages())!;
        for i in 0..<countPage{
            
        }
    }

}
