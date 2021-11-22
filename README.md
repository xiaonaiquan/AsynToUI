### 介绍

利用观察者模式，类对象创建后加入被观察者的类对象和回调函数，在类对象析构时，从观察者的列表中，移除。实现对被观察者的管理。

目前demo中，只支持std::string数据，可以根据自己的需要添加int，shared_ptr，只需要重载

```
void ModuleSubject::asynNotifyObserver(const std::string& keyId, std::string& data)
```

界面库使用duilib，地址为：https://github.com/xiaonaiquan/duilib_xiaonaiquan.git



