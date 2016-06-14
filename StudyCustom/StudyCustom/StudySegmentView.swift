//
//  StudySegmentView.swift
//  StudyCustom
//
//  Created by lutery on 16/6/4.
//  Copyright © 2016年 lutery. All rights reserved.
//

import UIKit

class StudySegmentView: UIView {

    var number:Int = 0;
    var labelTag = 0;
    var selected = 0;
    var idx:UInt = 0;
    var leftAndRightLineEdge:CGFloat = 0.0;
    private var _selectView:UIView? = nil;
    var selectView:UIView?{
        get{
            if _selectView == nil {
                _selectView = UIView(frame: CGRectMake(0, 0, 100, 2));
                self.addSubview(_selectView!);
                _selectView?.backgroundColor = self.tintColor;
            }
            
            return _selectView;
        }
    }
    private var _baseColor:UIColor? = nil;
    var baseColor:UIColor?{
        get{
            if _baseColor == nil {
                _baseColor = UIColor();
            }
            
            return _baseColor;
        }
        
        set(newValue){
            _baseColor = newValue;
        }
    }
    
    private var _labelFont:UIFont? = nil;
    var labelFont:UIFont?{
        get{
            return _labelFont;
        }
        
        set(newValue){
            _labelFont = newValue;
            
            for child in self.subviews {
                if child is UILabel{
                    let label = child as! UILabel;
                    label.font = _labelFont!;
                }
            }
        }
    }
    
    private var _hasBottomLine:Bool = false;
    var hasBottomLine:Bool{
        get{
            return _hasBottomLine;
        }
        
        set(newValue){
            _hasBottomLine = newValue;
        }
    }
    
    public var stintColor: UIColor!{
        get{
            return self.tintColor;
        }
        
        set(newValue){
            self.tintColor = newValue;
            self.selectView?.backgroundColor = newValue;
        }
    }
    
    /*
    // Only override drawRect: if you perform custom drawing.
    // An empty implementation adversely affects performance during animation.
    override func drawRect(rect: CGRect) {
        // Drawing code
    }
    */

    func configForTitles(titles:[NSString]){
        self.cleanAll();
        labelTag = 1000;
        self.number = titles.count;
        
        for title in titles {
            let la = self.standLabel();
            la.text = title as String;
            la.backgroundColor = UIColor.clearColor();
            self.addSubview(la);
            la.tag = labelTag;
            labelTag += 1;
        }
    }
    
    private func cleanAll(){
        let childs = self.subviews.enumerate();
        
        for child in childs{
            if child.element is UILabel{
                child.element.removeFromSuperview();
            }
        }
    }
    
    private func standLabel()->UILabel{
        let label = UILabel(frame: CGRectMake(0, 0, 100, 50));
        label.font = UIFont.systemFontOfSize(14);
        label.textColor = self.tintColor;
        return label;
    }
    
    private func boundsWithLabel(label:UILabel)->CGRect{
        return (label.text! as NSString).boundingRectWithSize(CGSizeMake(CGFloat.max, label.frame.size.height), options: .UsesFontLeading, attributes: [NSFontAttributeName:label.font], context: nil);
    }
    
    override func layoutSubviews() {
        super.layoutSubviews();
        
        for child in self.subviews{
            if child is UILabel{
                let label = child as! UILabel;
                let rect = self.boundsWithLabel(label);
                label.frame = CGRectMake(0, 0, rect.size.width, rect.size.height);
                label.center = CGPointMake(self.frame.size.width / ((CGFloat)(self.number * 2))  * ((((CGFloat)(label.tag)) - 1000) * 2 + 1), self.frame.size.height / 2);
                
            }
        }
    }
    
    override func touchesBegan(touches: Set<UITouch>, withEvent event: UIEvent?) {
        super.touchesBegan(touches, withEvent: event);
    }
    
    override func touchesEnded(touches: Set<UITouch>, withEvent event: UIEvent?) {
        super.touchesEnded(touches, withEvent: event);
        
        let touch = touches.first;
        let point = touch?.locationInView(self);
        let detla = self.frame.size.width / CGFloat(self.number);
        let touchNumber = (point?.x)! / detla;
        self.selected = Int(touchNumber);
        self.setSelectItemAtIndex(UInt(selected), animate: true);
    }
    
    func setSelectItemAtIndex(idx:UInt, animate:Bool){
        self.idx = idx;
        for child in self.subviews{
            if child is UILabel{
                let label = child as! UILabel;
                if self.selected + 1000 == label.tag{
                    label.textColor = self.tintColor;
                }
                else{
                    label.textColor = self.baseColor;
                }
            }
        }
        
        UIView.animateWithDuration(0.2, animations: {() in
            let label = self.viewWithTag(Int(idx) + 1000);
            self.selectView?.frame = CGRectMake((label?.frame.origin.x)! - self.leftAndRightLineEdge, (label?.frame.size.height)! + (label?.frame.origin.y)! + 10, (label?.frame.size.width)! + self.leftAndRightLineEdge, 2)
        })
    }
}
