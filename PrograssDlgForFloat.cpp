#include "PrograssDlgForFloat.h"
#include <QApplication>
#include <QProgressBar>
#include <qlabel.h>
PrograssDlgForFloat::PrograssDlgForFloat(QWidget *parent)
    : QProgressDialog{parent},m_bar(nullptr),m_label(nullptr)
{
    m_prescent=0;
    this->setMinimumDuration(5);
    m_bar = new QProgressBar(this);
    this->setBar(m_bar);
    m_bar->setTextVisible(false);

    m_label = new QLabel(this);
    m_label->setAlignment(Qt::AlignCenter);
    this->setLabel(m_label);

    m_strInfo = "已完成:";
}

void PrograssDlgForFloat::setPrescent(qreal value)
{
    if(value<0.0f) value=0.0;
    m_prescent=value;
    updateGrass();
}

void PrograssDlgForFloat::addPrescent(qreal value)
{
    m_prescent+=value;
    updateGrass();
}

void PrograssDlgForFloat::updateGrass()
{
    this->setValue(m_prescent);
    m_label->setText(m_strInfo +QString::number(m_prescent / this->maximum() * 100.0, 'f', 2) + "%");
    QApplication::processEvents();
}
void PrograssDlgForFloat::setInfo(const QString& info, int nSzie) {
    m_strInfo = info;
    m_prescent = 0;
    this->setMaximum(nSzie);
}