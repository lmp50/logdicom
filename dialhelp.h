#ifndef DIALHELP_H
#define DIALHELP_H

#include <QDialog>

namespace Ui {
class DialHelp;
}

class DialHelp : public QDialog
{
    Q_OBJECT

public:
    explicit DialHelp(QWidget *parent = 0);
    ~DialHelp();

private:
    Ui::DialHelp *ui;

private slots:
    void slotTreeClicked(const QModelIndex &index);

};

#endif // DIALHELP_H
