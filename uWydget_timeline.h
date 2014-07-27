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


#ifndef UWYDGET_TIMELINE_H
#define UWYDGET_TIMELINE_H

#include "uDialog_fileheader.h"

class UWydget_Timeline : public QWidget
{
    Q_OBJECT

signals:

    void gapModified(double);

public:
    UWydget_Timeline();
    void setMin(int in) { min = in; update(); };
    void setMax(int in) { max = in; update(); };
    void setBpm(int n) { _bpm = n; };
    void setGap(int n) { _lastGap = _gap = n; };

protected:
    int min, max;
    float _bpm;
    float _gap;
     void paintEvent(QPaintEvent * event);
     void mousePressEvent(QMouseEvent * event);
     void mouseReleaseEvent(QMouseEvent * event);
     void mouseMoveEvent(QMouseEvent * event);
     bool _gapSelected;
     float _lastGap;

};

#endif // UEDITOR_TIMELINE_H
