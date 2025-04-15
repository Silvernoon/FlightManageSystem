/********************************************************************************
** Form generated from reading UI file 'sell.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELL_H
#define UI_SELL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_sell
{
public:
    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QPushButton *book;
    QPushButton *refund;

    void setupUi(QDialog *sell)
    {
        if (sell->objectName().isEmpty())
            sell->setObjectName("sell");
        sell->resize(200, 124);
        gridLayout = new QGridLayout(sell);
        gridLayout->setObjectName("gridLayout");
        lineEdit = new QLineEdit(sell);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setClearButtonEnabled(true);

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        book = new QPushButton(sell);
        book->setObjectName("book");

        gridLayout->addWidget(book, 3, 1, 1, 1);

        refund = new QPushButton(sell);
        refund->setObjectName("refund");

        gridLayout->addWidget(refund, 4, 1, 1, 1);


        retranslateUi(sell);

        QMetaObject::connectSlotsByName(sell);
    } // setupUi

    void retranslateUi(QDialog *sell)
    {
        sell->setWindowTitle(QCoreApplication::translate("sell", "Dialog", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("sell", "\345\210\227\350\275\246\345\217\267", nullptr));
        book->setText(QCoreApplication::translate("sell", "\350\256\242\347\245\250", nullptr));
        refund->setText(QCoreApplication::translate("sell", "\351\200\200\347\245\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sell: public Ui_sell {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELL_H
