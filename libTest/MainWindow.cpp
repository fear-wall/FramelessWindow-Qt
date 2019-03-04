/**
 * 自定义无边框窗体、对话框和提示框
 *
 * MainWindow.h
 * 测试用例主要窗口
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#include <QLabel>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTime>
#include <QRandomGenerator>
#include "MainWindow.h"
#include "FramelessWindow_Global.h"
#include "changeskin.h"
#include "ui_MainWindow.h"
#include "ui_AeroClientWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : MuCustomWindow(parent)
    , ui(new Ui::MainWindow)
    , aeroUI(new Ui::AeroCLientWidget)
{
    setWindowTitle("Test Custom Window");
    this->resize(800, 600);

    QWidget *pClientWidget = new QWidget(this);
    ui->setupUi(pClientWidget);

    this->titleBar()->setTitleHeight(50);
    this->titleBar()->setObjectName("titleBar");
    this->titleBar()->titleLabel()->setObjectName("titleLabel");
    this->titleBar()->minimizeButton()->setObjectName("minimizeButton");
    this->titleBar()->maximizeButton()->setObjectName("maximizeButton");
    this->titleBar()->closeButton()->setObjectName("closeButton");

    QPushButton *btn_changeSkin = new QPushButton();
    btn_changeSkin->setParent(this);
    btn_changeSkin->setText("换皮肤");
    btn_changeSkin->move(100,60);
    btn_changeSkin->resize(100,30);
    connect(btn_changeSkin,SIGNAL(clicked()),  this, SLOT(changeStyle()));

    // 设置中心客户区域
    setClientWidget(pClientWidget);

    // 设置messagebox的按钮样式表和标题样式表
    const QString buttonStyle = "QPushButton {  \
                                    border: none; \
                                    background-color: #52baff; \
                                    width: 80px; \
                                    height: 30px; \
                                 } \
                                 QPushButton::pressed { \
                                    background-color: gray; \
                                 }";
    //MuCustomMessageBox::setTitleStyleSheet(QStringLiteral("QLabel { color: black }"));
    MuCustomMessageBox::setButtonStyleSheet(QDialogButtonBox::Ok, buttonStyle);

    connect(ui->dialogBtn, &QPushButton::clicked, this, &MainWindow::onDialogBtnClicked);
    connect(ui->informationBtn, &QPushButton::clicked, this, &MainWindow::onInformationBtnClicked);
    connect(ui->errorBtn, &QPushButton::clicked, this, &MainWindow::onErrorBtnClicked);
    connect(ui->successBtn, &QPushButton::clicked, this, &MainWindow::onSuccessBtnClicked);
    connect(ui->warningBtn, &QPushButton::clicked, this, &MainWindow::onWarningBtnClicked);
#ifdef Q_OS_WIN32
    initAreoWindow();
    connect(ui->aeroBtn, &QPushButton::clicked, m_AeroWindow, &MuWinAeroShadowWindow::show);
#else
    ui->aeroBtn->hide();
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
#ifdef Q_OS_WIN32
    delete m_AeroWindow;
#endif
}
/**
 * @brief generateRandomNumber
 * 获取随机数
 */
int  MainWindow::generateRandomNumber()
{
    QRandomGenerator(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0; i<5 ; i++)
    {
        int test =qrand()%5;
        qDebug()<<test;
        return test;
    }
}
/**
*换肤函数
**/
void MainWindow::changeStyle() {
   QString skinName1 = ":/dark.qss";
   QString skinName2 = ":/black.qss";
   QString skinName3 = ":/white.qss";
   QString skinName4 = ":/style.qss";

   int i = generateRandomNumber();
  // QString skinName =  QString("skinName%1").arg(i);
   QString skinName =  skinName3;
   qDebug()<<"----------------"<<skinName<<"-------------------";
    changeskin::setStyle(skinName);
}


/**
 ** @brief MainWindow::onDialogBtnClicked
 ** @info 指定对话框样式
**/

void MainWindow::onDialogBtnClicked()
{
    MuCustomDialog dialog;
    QLabel label("This is a Custom Dialog!");
    label.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    dialog.titleBar()->setObjectName("dialogTitleBar");
    dialog.titleBar()->titleLabel()->setObjectName("dialogTitleLabel");
    dialog.setModal(true);
    dialog.setWindowTitle("dialog");
    dialog.setClientWidget(&label);
    dialog.exec();
}

/**
 * @brief MainWindow::onInformationBtnClicked
 * 简要方式弹出信息框
 */
void MainWindow::onInformationBtnClicked1()
{
        MuCustomMessageBox::showInformation(nullptr,
                                        QStringLiteral("Information!"),
                                        QStringLiteral("This is a Information MessageBox!"));
}
/**
 * @brief MainWindow::onInformationBtnClicked
 * @指定样式表的信息框
 */
void MainWindow::onInformationBtnClicked(){
    MuCustomMessageBox showInformation;

    QLabel label("This is a Custom Dialog!");
    label.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    showInformation.titleBar()->setObjectName("informationTitleBar");
    showInformation.titleBar()->titleLabel()->setObjectName("informationTitleLabel");
    showInformation.setModal(true);
    showInformation.setWindowTitle("提示信息");
   // showInformation.setText("This is a Information MessageBox!");
   showInformation.setClientWidget(&label);
   showInformation.resize(300,200);
    showInformation.exec();
}
void MainWindow::onErrorBtnClicked()
{
    MuCustomMessageBox::showError(nullptr,
                                  QStringLiteral("Error!"),
                                  QStringLiteral("This is a Error MessageBox!"));
}

void MainWindow::onSuccessBtnClicked()
{
    MuCustomMessageBox::showSuccess(nullptr,
                                    QStringLiteral("Success!"),
                                    QStringLiteral("This is a Success MessageBox!"));
}

void MainWindow::onWarningBtnClicked()
{
    MuCustomMessageBox::showWarning(nullptr,
                                    QStringLiteral("Warning!"),
                                    QStringLiteral("This is a Warning MessageBox!"));
}

#ifdef Q_OS_WIN32
void MainWindow::initAreoWindow()
{
    m_AeroWindow = new MuWinAeroShadowWindow;
    //打开拖动窗体半透明
    m_AeroWindow->setRubberBandOnMove(true);
    //打开橡皮筋特效
    m_AeroWindow->setRubberBandOnResize(true);
    m_AeroWindow->setWindowTitle(QStringLiteral("Test Aero Window"));
    m_AeroWindow->titleBar()->setObjectName("aeroTitleBar");
    QWidget *pClientWidget = new QWidget(m_AeroWindow);
    aeroUI->setupUi(pClientWidget);
    m_AeroWindow->setClientWidget(pClientWidget);
}
#endif

void MainWindow::on_pushButton_2_clicked()
{
    MuCustomMessageBox::showInformation(nullptr,
                                        QStringLiteral("Information!"),
                                        QStringLiteral("This is a Information MessageBox!"));}
