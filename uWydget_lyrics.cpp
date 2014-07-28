/****************************************************************************
**
** Author & Contact: Quentin BRAMAS ( contact@bramas.fr )
**
** This file is part of Ultratools.
**
** GNU General Public License Usage
** ExUlt is free software: you can redistribute it and/or modify it under the
** terms of General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.txt included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** ExUlt is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** If you have questions regarding the use of this file, please contact
** Quentin BRAMAS (contact@bramas.fr).
**
****************************************************************************/


#include "uWydget_lyrics.h"
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <QPainter>
#include "uInputManager.h"

#define MAX_HEIGHT 40
#define UTF8_WORDS_SEPARATOR 0x02D2
#define UTF8_SENTENCE_SEPARATOR 0x02FD //02C4

UWydget_Lyrics::UWydget_Lyrics()
{
_selectedTextFirstIndex=-1; _selectedTextLastIndex=-1;
    QTimer *timer = new QTimer(this);
      connect(timer, SIGNAL(timeout()), this, SLOT(update()));
_brutText="ouéé";
_listWords = NULL;
 _lay = new QHBoxLayout();
 this->setMaximumWidth(200);
 this->setMinimumWidth(200);

 this->setLayout(_lay);
/*QSpacerItem * space = new QSpacerItem(200,50);
_lay->addSpacerItem(space);

space = new QSpacerItem(200,50);
_lay->addSpacerItem(space);

_lay->addStretch(2);
_lay->addStretch(2);
*/

 _maxHeight = MAX_HEIGHT;
_cursorPosition= 0;

_fontSize = 6;
_lineEdit = NULL;
_isEditing = false;

connect(&UInputManager::Instance, SIGNAL(keyPressEvent(QKeyEvent*)),this, SLOT(onKeyPress(QKeyEvent*)));

update();

}

void UWydget_Lyrics::setWords(QList<Word*>* listWords)
{
    _listWords = listWords;

    update();
}

void UWydget_Lyrics::onKeyPress(QKeyEvent *e)
{

    if(e->key() == Qt::Key_Enter || e->key()+1 == Qt::Key_Enter)
        saveChange();
};

void UWydget_Lyrics::saveChange()
{

    if(_lineEdit)
    {
        updateChange();
        _lay->removeWidget(_lineEdit);
        delete _lineEdit;
        _lineEdit = NULL;
    }

}

void UWydget_Lyrics::updateChange()
{
    if(!_lineEdit)
    {
        return;
    }
    QString regex = "[";
    regex.append(QChar(UTF8_WORDS_SEPARATOR));
    regex.append(QChar(UTF8_SENTENCE_SEPARATOR));
    regex.append("]");

    QStringList strList = _lineEdit->text().split(
            QRegExp(regex));

    QString str;

    while(strList.count() < _listWords->count())
    {
        _listWords->first()->getParent()->moveLeft(_listWords->first());
        _listWords->pop_back();

    }
    if(!_listWords->empty())
    while(strList.count() > _listWords->count())
    {
        _listWords->push_back(

                _listWords->first()->getParent()->moveRight(
                        _listWords->first(),_listWords->count()
                        )

                );

    }

    if(strList.count() == _listWords->count())
    {
        qDebug()<<"MEME NOMBRE";
        int k=0;
        foreach(str,strList)
        {
            _listWords->at(k++)->setText(str);
        }

    }



}

void UWydget_Lyrics::mousePressEvent(QMouseEvent *event)
{

    if(_lineEdit)
    {
        _lay->removeWidget(_lineEdit);
        delete _lineEdit;
        _lineEdit = NULL;
    }


    if(!_listWords)
    {
        return;
    }
    QString text = "";

    Word * w;
    Word * lastW = NULL;
    foreach(w,*_listWords)
    {

        if(w->isSeparator())
        {
            text.remove(-1,1);
            text.append(QChar(UTF8_SENTENCE_SEPARATOR));
            continue;
        }
        text.append(w->getText()+QChar(UTF8_WORDS_SEPARATOR));//02FD));
        lastW = w;
    }
    text.remove(-1,1);
    _lineEdit = new QLineEdit(text,this);

    connect(_lineEdit,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(cursorPositionChanged(int,int)));
    //connect(_lineEdit,SIGNAL(),this,SLOT(cursorPositionChanged(int,int)));


    _lay->insertWidget(0,_lineEdit);

    QFont font;

    font.setFamily("Verdana");
    font.setPixelSize(_fontSizeEdit);

    _lineEdit->setFont(font);


    _isEditing=true;

}


void UWydget_Lyrics::onScroll()
{

    saveChange();
    update();
}


void UWydget_Lyrics::ondoubleClick(int s)
{
     mousePressEvent(new QMouseEvent(QEvent::FocusIn,QPoint(0,0),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier));

     if(s==-1 || !_lineEdit || !_lineEdit->text().length())
     {
         return;
     }

     QString str = "[";
     str.append(QChar(UTF8_WORDS_SEPARATOR));
     str.append(QChar(UTF8_SENTENCE_SEPARATOR));
     str.append("]");


     QRegExp reg(str);


     if(_lineEdit->text().count(reg)<s-1)
     {
         return;
     }

     int last = 0;
     for(int i=0;i<s;++i)
     {
         last = _lineEdit->text().indexOf(reg,last)+1;
     }
     int end = _lineEdit->text().indexOf(reg,last);
     if(end == -1) end = _lineEdit->text().count();

    _lineEdit->setSelection(last,end-last);
    _lineEdit->setFocus();

}

void UWydget_Lyrics::paintEvent(QPaintEvent * event)
{



    if(!_listWords)
    {
        return;
    }
    _brutText = "";

    Word * w;

    QString sepAjout = "";

    QString _selectedText,_textBeforeSelectedText;


    int k=0;
    foreach(w,*_listWords)
    {
        _brutText.append(w->getText());
        sepAjout.append(QChar(UTF8_WORDS_SEPARATOR));

        if(k<_selectedTextFirstIndex)
        {
            _textBeforeSelectedText.append(w->getText());
        }
        else
        if(k<=_selectedTextLastIndex)
        {
            _selectedText.append(w->getText());
        }
        k++;
    }



     QPainter * painter = new QPainter(this);

     painter->setPen(QPen::QPen(QColor::QColor(0,0,0,170)));
      painter->setBrush(QBrush::QBrush(QColor::QColor(0,173,232,170)));
        QFont font;


        font.setFamily("Verdana");






      int textWidthInPixels ,textWidthInPixelsEdit;


_fontSize = _fontSizeEdit = 6;

                font.setPixelSize(_fontSize);

//qDebug()<<"\n\n\n\n\n\n\n";
             while(1)
             {
                 QFontMetrics fm(font);
                 textWidthInPixels = fm.width(_brutText);
                 textWidthInPixelsEdit = fm.width(_brutText+sepAjout);
                 //qDebug()<<_fontSize<<" : "<<fm.width(_brutText)<<"px  tw: "<<width();


                 if(textWidthInPixelsEdit<width())
                 {
                     ++_fontSizeEdit;
                 }


                 if(textWidthInPixels>width())
                 {
                     font.setPixelSize(--_fontSize);
                     break;
                 }

                 if(fm.height()>_maxHeight)
                 {
                     font.setPixelSize(--_fontSize);
                        break;
                 }

                 font.setPixelSize(++_fontSize);
             }


             painter->setFont(font);
--_fontSizeEdit;

        //int textHeightInPixels = fm.height();



    painter->drawText(0,0,width(),height(),Qt::TextSingleLine,_brutText);


    painter->setPen(QPen::QPen(QColor::QColor(0,0,255,255)));
     painter->setBrush(QBrush::QBrush(QColor::QColor(0,0,255,255)));





    QFontMetrics fm(font);

    painter->drawText( fm.width(_textBeforeSelectedText) ,0,fm.width(_selectedText),height(),Qt::TextSingleLine,_selectedText);




}

void UWydget_Lyrics::separeOnSelect()
{
    //QMessageBox::warning(NULL,"","lol");
    if(!_lineEdit) return;

    QString temp = _lineEdit->text();

    temp.insert(_cursorPosition,QChar(UTF8_WORDS_SEPARATOR));
    _lineEdit->setText(temp);
}

void UWydget_Lyrics::cursorPositionChanged(int old,int pos){

    if(pos<_lineEdit->text().length())
        _cursorPosition = pos;

}
void UWydget_Lyrics::onSelectionChange(int s, int f)
{
    _selectedTextFirstIndex=s;
    _selectedTextLastIndex=f;
    update();
}
