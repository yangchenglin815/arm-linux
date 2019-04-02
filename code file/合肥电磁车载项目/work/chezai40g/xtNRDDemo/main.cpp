#include <QtGui/QApplication>
#include <QTextCodec>
#include "xtnrddemo.h"
#include "xtconfig.h"

int main(int argc, char *argv[])
{
    system("rm -f /var/lock/LCK..ttyUSB*;sync;");
    QApplication a(argc, argv);

    //Arrow Cursor
#if defined(CONFIG_QT_NO_CURSOR)
    QApplication::setOverrideCursor(Qt::BlankCursor);
#endif
    // Codec & Font
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QFont font;
    font.setPointSize(16);
    font.setFamily("fzhei-b01s");
    a.setFont(font);

    XtNRDDemo w;
    w.show();
    
    return a.exec();
}
