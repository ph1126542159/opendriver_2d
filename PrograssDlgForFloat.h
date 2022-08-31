#ifndef PROGRASSDLGFORFLOAT_H
#define PROGRASSDLGFORFLOAT_H

#include <QProgressDialog>
class QProgressBar;
class PrograssDlgForFloat : public QProgressDialog
{
    Q_OBJECT
public:
    explicit PrograssDlgForFloat(QWidget *parent = nullptr);

    void setPrescent(qreal value);

    void addPrescent(qreal value);

    void setInfo(const QString& info,int nSzie);
private:
    void updateGrass();
    qreal m_prescent;
    QProgressBar* m_bar;
    QLabel* m_label;
    QString m_strInfo;
};

#endif // PROGRASSDLGFORFLOAT_H
