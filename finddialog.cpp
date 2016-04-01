#include "finddialog.h"
#include "QtGui"

finddialog::finddialog(QWidget *parent):QDialog(parent)
{
    /*定位功能控件*/
    label = new QLabel(tr("Find &what")); //创建、设置名称
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);     //设置快捷键

    caseCheckBox = new QCheckBox(tr("Match &case")); //设置名称为Match case
    backwardCheckBox = new QCheckBox(tr("Search &backford"));//同上

    findButton = new QPushButton(tr("&Find")); //设置按键的名称为Find
    findButton->setDefault(true);       //设置该按钮为推动按钮，在对话框中按下回车键，将代表按下这个按钮
    findButton->setEnabled(false);      //将按键的初始状态设置为不启用

    closeButton = new QPushButton(tr("Close"));

    /*绑定信号槽*/
    connect(lineEdit,SIGNAL(textChanged(const QString&)),this,SLOT(enableFindButton(const QString&)));
    connect(findButton,SIGNAL(clicked(bool)),this,SLOT(findClicked()));
    connect(closeButton,SIGNAL(clicked(bool)),this,SLOT(close()));


    /*界面布局*/
    QHBoxLayout *topleftlayout = new QHBoxLayout;  //布局方向 横
    topleftlayout->addWidget(label);
    topleftlayout->addWidget(lineEdit);

    QVBoxLayout *leftlayout = new QVBoxLayout; //布局方向 垂直
    leftlayout->addLayout(topleftlayout);
    leftlayout->addWidget(caseCheckBox);
    leftlayout->addWidget(backwardCheckBox);

    QVBoxLayout *rightlayout = new QVBoxLayout;//布局方向 垂直
    rightlayout->addWidget(findButton);
    rightlayout->addWidget(closeButton);
    rightlayout->addStretch();

    QHBoxLayout *mainlayout = new QHBoxLayout;//布局方向 横
    mainlayout->addLayout(leftlayout);
    mainlayout->addLayout(rightlayout);
    setLayout(mainlayout);

    setWindowTitle(tr("Find"));//设置窗口名称 为Find
    setFixedHeight(sizeHint().height());//设置窗口大小为其需要使用大小
}

finddialog::~finddialog()
{

}

/*private slots: 的编写*/
void finddialog::findClicked()
{
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs = caseCheckBox->isChecked()?Qt::CaseInsensitive:Qt::CaseSensitive;

    if (backwardCheckBox->isChecked())
        emit findPrevious(text,cs);
    else
        emit findNext(text,cs);
}

void finddialog::enableFindButton(const QString &text)
{
    findButton->setEnabled(!text.isEmpty());
}
