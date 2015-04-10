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

#ifndef UNEWSONGFORM_LYRICS_H
#define UNEWSONGFORM_LYRICS_H


#include "uNewSongForm_Browse.h"

namespace Ui {
    class UNewSongForm_Lyrics;
}

class UNewSongForm_Lyrics : public QDialog {
    Q_OBJECT
public:
    UNewSongForm_Lyrics(QWidget *parent = 0);
    ~UNewSongForm_Lyrics();

    QString getText(void);


protected:
    void changeEvent(QEvent *e);

private:
    Ui::UNewSongForm_Lyrics *ui;
};

#endif // UNEWSONGFORM_LYRICS_H
