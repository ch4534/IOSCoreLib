//
//  ViewController.swift
//  StartIPrint
//
//  Created by lutery on 16/3/8.
//  Copyright © 2016年 lutery. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UIImagePickerControllerDelegate, UINavigationControllerDelegate {

    //弱引用导航条
    @IBOutlet weak var _navigationBar: UINavigationItem!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        self.title = "StartIPrint";
        
//        let starImage = UIImage.init(named: "bmp");
//        let width = starImage!.size.width;
//        let height = starImage!.size.height;
//        let array = NSBundle.mainBundle().pathsForResourcesOfType("png", inDirectory: "iconres");
//        for ico in array{
//            print(ico);
//        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    //拍照按钮动作
    @IBAction func takePhotoAction(_ sender: AnyObject) {
        //判断相机是否可用
        if UIImagePickerController.isSourceTypeAvailable(.camera){
            let picker = UIImagePickerController();
            picker.delegate = self;
            picker.sourceType = UIImagePickerControllerSourceType.camera;
            picker.cameraDevice = UIImagePickerControllerCameraDevice.rear;
            present(picker, animated: true, completion: nil);
        }
    }

    //图库按钮动作
    @IBAction func selectPhotoAction(_ sender: AnyObject) {
        //对于ios来说，图库一定存在，那么就不需要进行判断
        let picker = UIImagePickerController();
        picker.delegate = self;
        picker.sourceType = UIImagePickerControllerSourceType.photoLibrary;
        present(picker, animated: true, completion: nil);
    }
    
    //拍照/图库图片获取函数回调
    //picker:图库选取控制器
    //info:包含原图以及修剪图的引用
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [String : AnyObject]) {
        //取消图像选择控制器的显示
        picker.dismiss(animated: true, completion: nil);
        
        //获取原始图像
        let originalImage:UIImage? = info[UIImagePickerControllerOriginalImage] as? UIImage;
        //从故事版中实例化一个Controller
        let mainStoryboard = UIStoryboard(name: "Main", bundle: nil);
        let docPrint = mainStoryboard.instantiateViewController(withIdentifier: "siDocPrint") as! DocViewController;
        
        //如果原始图像不为空，那么执行if语句
        if originalImage != nil{
//            //将原始图像保存早临时缓存文件夹
//            let imagedata = UIImageJPEGRepresentation(originalImage!, 1.0);
//            let paths = NSTemporaryDirectory();
//            let tempFilePath = paths.stringByAppendingString("tempImage");
//            imagedata?.writeToFile(tempFilePath, atomically: true);
//            
//            //获取屏幕的尺寸，创建临时图像，传入解析层
//            let screenSize = Util.getScreenSize();
//            let tempImage = TempImage();
//            tempImage.width =  Int(Float((originalImage?.size.width)!));
//            tempImage.height = Int(Float((originalImage?.size.height)!));
//            tempImage.originImagePath = tempFilePath;
//            tempImage.scaleImage = Util.resizeImage(originalImage!, newSize: screenSize);
//            let parselayer = Parse(image: tempImage);
            let parseLayer = Parse(image: originalImage!);
            
            docPrint.parseLayer = parseLayer;
        }
        
        //导航到指定的控制器对象
        self.navigationController?.pushViewController(docPrint, animated: true);
    }
}

