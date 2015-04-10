/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Quentin Bramas <quentin@bramas.fr> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Quentin Bramas
 *
 * "LICENCE BEERWARE" (Révision 42):
 * Quentin Bramas <quentin@bramas.fr> a créé ce fichier. Tant que vous conservez cet avertissement,
 * vous pouvez faire ce que vous voulez de ce truc. Si on se rencontre un jour et
 * que vous pensez que ce truc vaut le coup, vous pouvez me payer une bière en
 * retour. Quentin Bramas
 * ----------------------------------------------------------------------------
 */


#ifndef UDIALOG_FILEHEADER_H
#define UDIALOG_FILEHEADER_H

#include <QDialog>
class UFile;

namespace Ui {
    class UDialog_fileHeader;
}

class UDialog_fileHeader : public QDialog {
    Q_OBJECT

public slots:
   void accept(void);

public:
    UDialog_fileHeader(QWidget *parent, UFile * file);
    ~UDialog_fileHeader();

protected:
    UFile * _file;
    void changeEvent(QEvent *e);

private:
    Ui::UDialog_fileHeader *ui;
};

#endif // UDIALOG_FILEHEADER_H
