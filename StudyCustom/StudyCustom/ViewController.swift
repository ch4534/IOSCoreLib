//
//  ViewController.swift
//  StudyCustom
//
//  Created by lutery on 16/6/4.
//  Copyright © 2016年 lutery. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        self.configSegment();
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    func configSegment(){
        let segment = StudySegmentView(frame: CGRect(x: 0, y: 0, width: 300, height: 80));
        segment.leftAndRightLineEdge = 20;
        segment.configForTitles(["Main", "More", "Me"]);
        self.view.addSubview(segment);

        segment.baseColor = UIColor(red: 0.63, green: 0.81, blue: 0.20, alpha: 1);
        segment.stintColor = UIColor(red: 1, green: 0.38, blue: 0.43, alpha: 1);
        segment.hasBottomLine = false;
        segment.leftAndRightLineEdge = 20;
        segment.labelFont = UIFont(name: "Futura-CondensedExtraBold", size: 18);
    }
}

