/* Copyright (c) 2015 Quentin Bramas
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */




#ifndef UNEWSONGFORM_BROWSE_H
#define UNEWSONGFORM_BROWSE_H

#include <QDialog>
class UFile;

namespace Ui {
    class UNewSongForm_Browse;
}

class UNewSongForm_Browse : public QDialog {
    Q_OBJECT
public:
    UNewSongForm_Browse(QWidget *parent = 0, UFile * file=0);
    ~UNewSongForm_Browse();

public slots:

    void updateFolder(QString s="");
    void edited(QString s=""){ Q_UNUSED(s); _edited = true; }
    void browse(void);
    void browseMp3(void);
    void goNext(void);

protected:
    void changeEvent(QEvent *e);

    QString _baseLocation;
    bool _edited;
    UFile * _file;

private:
    Ui::UNewSongForm_Browse *ui;
};

#endif // UNEWSONGFORM_BROWSE_H
