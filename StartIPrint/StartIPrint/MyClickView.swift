//
//  MyClickView.swift
//  StartIPrint
//
//  Created by lutery on 16/3/14.
//  Copyright © 2016年 lutery. All rights reserved.
//

import UIKit

//
// @brief 自定义点击View，用于实现块状点击区域
//
class MyClickView: UIView,UIActionSheetDelegate {

    /*
    // Only override drawRect: if you perform custom drawing.
    // An empty implementation adversely affects performance during animation.
    override func drawRect(rect: CGRect) {
        // Drawing code
    }
    */
    
    //
    // @brief 重载初始化函数（构造函数），加入自定义的初始化事件函数，添加点击手势
    //
    // @param frame:CGRect 位置区域
    override init(frame: CGRect) {
        super.init(frame: frame);
        
        self.initEvent();
    }

    //
    // @brief 这个初始化函数时必须重载的，在Storyboard中会调用到这个初始化函数
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder);
        
        self.initEvent();
    }
    
    //
    // @brief 初始化事件，添加点击手势
    func initEvent(){
        self.userInteractionEnabled = true;
        let tapGesture = UITapGestureRecognizer(target: self, action: #selector(MyClickView.handleTapGesture));
        self.addGestureRecognizer(tapGesture);
    }
    
    //
    // @brief 点击手势事件函数
    //
    // @param sender:UIGestureRecognizer 手势变量
    func handleTapGesture(sender:UIGestureRecognizer){
        print("handleTapGesture");
    }

    //
    // @brief 重载开始触摸函数，也可以实现点击响应
    //
    // @param touches: Set<UITouch> 触摸点数
    // @param withEvent event: UIEvent? 触摸事件
    override func touchesBegan(touches: Set<UITouch>, withEvent event: UIEvent?) {
        print("touchesBegan");
        super.touchesBegan(touches, withEvent: event);
    }
}
