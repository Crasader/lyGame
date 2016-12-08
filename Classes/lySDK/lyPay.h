//
//  lyPay.h
//  ly-client
//	登录管理类，从此调用sdk相关接口
//  Created by loveyur on 2016/11/10
//

#ifndef ly_lyPay_h
#define ly_lyPay_h

class lyPay
{
public:
	lyPay();
	~lyPay();
    static lyPay* getInstance();


private:
	 static lyPay *m_plyPay;

};

#endif /* ly_lyPay_h */