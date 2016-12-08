//
//  lyLogin.h
//  ly-client
//	登录管理类，从此调用sdk相关接口
//  Created by loveyur on 2016/11/10
//

#ifndef ly_lyLogin_h
#define ly_lyLogin_h

class lyLogin
{
public:
	lyLogin();
	~lyLogin();
    static lyLogin* getInstance();


private:
	 static lyLogin *m_plyLogin;

};

#endif /* ly_lyLogin_h */