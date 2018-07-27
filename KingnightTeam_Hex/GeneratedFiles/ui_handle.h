/********************************************************************************
** Form generated from reading UI file 'handle.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HANDLE_H
#define UI_HANDLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Handle
{
public:

    void setupUi(QWidget *Handle)
    {
        if (Handle->objectName().isEmpty())
            Handle->setObjectName(QStringLiteral("Handle"));
        Handle->resize(400, 300);

        retranslateUi(Handle);

        QMetaObject::connectSlotsByName(Handle);
    } // setupUi

    void retranslateUi(QWidget *Handle)
    {
        Handle->setWindowTitle(QApplication::translate("Handle", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Handle: public Ui_Handle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HANDLE_H
