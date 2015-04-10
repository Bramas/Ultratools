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
