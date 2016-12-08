//
//  CCBCustomClassLoaderLibrary.h
//  client-vitamin
//
//  Created by 大久保 孝一郎 on 2014/06/26.
//
//

#ifndef __client_vitamin__CCBCustomClassLoaderLibrary__
#define __client_vitamin__CCBCustomClassLoaderLibrary__

#include "spritebuilder/SpriteBuilder.h"


/*!
 * カスタムクラスエントリー構造体
 */
typedef struct {
    const char                *pClassName;       //! クラス名
    spritebuilder::NodeLoader *pCCNodeLoader;    //! 登録するローダーのポインタ
} CustomClassEntry;


/*!
 * カスタムクラス登録
 */
class CCBCustomClassLoaderLibrary {
public:
    
    /*!
     * @brief コンストラクタ
     */
    CCBCustomClassLoaderLibrary();
    
    /*!
     * @brief デストラクタ
     */
    ~CCBCustomClassLoaderLibrary();
    
    /*!
     * @brief カスタムクラス登録
     */
    void registerCustomClassLoader();
    
    /*!
     * @brief カスタムクラス登録解除
     */
    void unregisterCustomClassLoader();
    
    /*!
     * @brief インスタンス取得
     */
    static CCBCustomClassLoaderLibrary * getInstance();
    
    /*!
     * @brief インスタンス解放
     */
    static void purgeSharedCustomClassLoaderLibrary();
    
    /*!
     * @brief 指定した名前のカスタムクラスのローダー登録を変更
     */
    void changeRegisterCustomClassLoader(const char* className, spritebuilder::NodeLoader* loader);
    
private:
    std::vector<CustomClassEntry> m_customClassEntry;
};


#endif /* defined(__client_vitamin__CCBCustomClassLoaderLibrary__) */
