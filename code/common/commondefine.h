#ifndef COMMONDEFINE
#define COMMONDEFINE
#include <string>


#define kMaxStringLength 64 //字符串长度

//设置字段索引
typedef enum tagEnumSettings
{
    emComimutyName = 0,         //组织名称
    emApplicationName,          //应用名称
    emMainWindowGeometry,       //主窗口几何尺寸
    emRecentOpenedFiles,        //最近打开的文件
    emShowGrid                  //网格线显示
}EnumSettings;

//设置字段
const char chstrSettings[][kMaxStringLength]=
{
    "Software Inc.",
    "Information",
    "geometry",
    "recentFiles",
    "showGrid"
};

#endif // COMMONDEFINE

