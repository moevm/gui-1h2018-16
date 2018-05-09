#ifndef RECORDSFORM_H
#define RECORDSFORM_H

#include <QDialog>

namespace Ui {
class RecordsForm;
}

class RecordsForm : public QDialog
{
    Q_OBJECT

public:
    explicit RecordsForm(QWidget *parent = 0);
    ~RecordsForm();

private:
    Ui::RecordsForm *ui;
};

#endif // RECORDSFORM_H
