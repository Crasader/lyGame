//
//  lyTalkingdata.h
//  ly-client
//	登录管理类，从此调用sdk相关接口
//  Created by loveyur on 2016/11/10
//

#ifndef ly_lyTalkingdata_h
#define ly_lyTalkingdata_h

class lyTalkingdata
{
public:
	lyTalkingdata();
	~lyTalkingdata();
    static lyTalkingdata* getInstance();


private:
	 static lyTalkingdata *m_plyTalkingdata;

};

#endif /* ly_lyTalkingdata_h */