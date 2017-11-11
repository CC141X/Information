## Study Notes 
- **QMessageBox**

Header: `#include <QMessageBox>`

qmake: `QT += widgets`

`QMessageBox::information(parent, title, message, buttons);`

`QMessageBox::question(parent, title, message, buttons);`

`QMessageBox::warning(parent, title, message, buttons);`

`QMessageBox::critical(parent, title, message, buttons);`

- **QFileDialog**

Header:	`#include <QFileDialog>`

qmake:	 `QT += widgets`

- **Log**

日志级别逐次增加；`__DATE__`插入日期；`__FUNCTION__`插入函数名

`qDebug(const char * message, ...)`

`qWarning(const char * message, ...)`

`qCritical(const char * message, ...)`

`qFatal(const char * message, ...)`

- **Dialog**

`show()`非模态显示，`setModal()`设置模态显示，直接调用`exec()`模态显示
