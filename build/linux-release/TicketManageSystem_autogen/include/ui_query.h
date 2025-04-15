/********************************************************************************
** Form generated from reading UI file 'query.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUERY_H
#define UI_QUERY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_query
{
public:
    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *query)
    {
        if (query->objectName().isEmpty())
            query->setObjectName("query");
        query->resize(400, 86);
        gridLayout = new QGridLayout(query);
        gridLayout->setObjectName("gridLayout");
        lineEdit = new QLineEdit(query);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setClearButtonEnabled(true);

        gridLayout->addWidget(lineEdit, 0, 0, 1, 1);

        pushButton = new QPushButton(query);
        pushButton->setObjectName("pushButton");

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);


        retranslateUi(query);

        QMetaObject::connectSlotsByName(query);
    } // setupUi

    void retranslateUi(QDialog *query)
    {
        query->setWindowTitle(QCoreApplication::translate("query", "Dialog", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("query", "\346\220\234\347\264\242\342\200\246", nullptr));
        pushButton->setText(QCoreApplication::translate("query", "\346\220\234\347\264\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class query: public Ui_query {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUERY_H
