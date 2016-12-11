
#ifndef ActivityIndicator_h
#define ActivityIndicator_h

class ActivityIndicator
{
private:
	static int g_nCount;
	
public:
    static void startAnimating();
    static void stopAnimating();
    static void forceStopAnimating();
    static void setPosition(float x, float y);
    
};


#endif
