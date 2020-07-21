//
//  ViewController.swift
//  app
//
//  Created by shimeng on 2020/7/18.
//  Copyright © 2020 shimeng. All rights reserved.
//

import Cocoa
import AVFoundation

class ViewController: NSViewController {

  override func viewDidLoad() {
    super.viewDidLoad()
    
    // Do any additional setup after loading the view.
    self.view.setFrameSize(NSSize(width: 320, height: 420));
    
    let btn = NSButton.init(title: "button", target: nil, action: nil);
    btn.title = "Hello";
    btn.frame = NSRect(x: 320/2 - 40, y: 420/2 - 15, width: 80, height: 30);
    btn.bezelStyle = .rounded;
    btn.setButtonType(.pushOnPushOff);
    btn.target = self;
    btn.action = #selector(myfunc);
    self.view.addSubview(btn);
  }

  @objc
  func myfunc() {
    rec_audio();
  }
  override var representedObject: Any? {
    didSet {
    // Update the view, if already loaded.
    }
  }


}

