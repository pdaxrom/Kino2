#ifndef _MISC_H_
#define _MISC_H_

#include <qvariant.h>
#include <qdialog.h>
#include <qcstring.h>
#include <qstringlist.h>
#include <qlineedit.h>
#include <qwhatsthis.h>

class InputDialog : public QDialog
{ 
    Q_OBJECT

public:
    InputDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~InputDialog();
    QString inputText;
    QLineEdit* LineEdit1;
    void setInputText(const QString &); 
private slots:
    void returned();
    
};

#endif
