/********************************************************************************
** Form generated from reading UI file 'chessboard.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHESSBOARD_H
#define UI_CHESSBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChessBoard
{
public:

    void setupUi(QWidget *ChessBoard)
    {
        if (ChessBoard->objectName().isEmpty())
            ChessBoard->setObjectName(QStringLiteral("ChessBoard"));
        ChessBoard->resize(400, 300);

        retranslateUi(ChessBoard);

        QMetaObject::connectSlotsByName(ChessBoard);
    } // setupUi

    void retranslateUi(QWidget *ChessBoard)
    {
        ChessBoard->setWindowTitle(QApplication::translate("ChessBoard", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class ChessBoard: public Ui_ChessBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHESSBOARD_H
