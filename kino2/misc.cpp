#include <qmessagebox.h>
#include <qstringlist.h>
#include <qfile.h>
#include <qcstring.h>
#include <qlineedit.h>
#include <qmultilineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>

#include "misc.h"

InputDialog::InputDialog( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
        setName( "InputDialog" );
    resize( 234, 50 ); 
    setMaximumSize( QSize( 240, 50 ) );
    setCaption( tr(name ) );

    LineEdit1 = new QLineEdit( this, "LineEdit1" );
    LineEdit1->setGeometry( QRect( 10, 10, 216, 22 ) );
    LineEdit1->setFocus();
    LineEdit1->setFocus();
    connect(LineEdit1,SIGNAL(returnPressed()),this,SLOT(returned() ));
}

InputDialog::~InputDialog() {
    inputText = LineEdit1->text();
}

void InputDialog::setInputText(const QString &string) {
    LineEdit1->setText( string);
}

void InputDialog::returned() {
    inputText = LineEdit1->text();
    this->accept();
}
