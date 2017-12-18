#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    is_changed = false;
    QToolBar *bar = this->addToolBar("Tools");
    QActionGroup *group = new QActionGroup(bar);
    bar->setBaseSize(20, 20);

    QAction *AddAction = new QAction("Add", bar);
    AddAction->setIcon(QIcon(":/myImage/images/add.png"));
    AddAction->setToolTip(tr("Add a student."));
    AddAction->setStatusTip(tr("Add a student."));
    AddAction->setCheckable(true);
    AddAction->setChecked(true);
    group->addAction(AddAction);
    bar->addAction(AddAction);

    QAction *DeleteAction = new QAction("Delete", bar);
    DeleteAction->setIcon(QIcon(":/myImage/images/delete.png"));
    DeleteAction->setToolTip(tr("delete a student."));
    DeleteAction->setStatusTip(tr("delete a student."));
    DeleteAction->setCheckable(true);
    DeleteAction->setChecked(true);
    group->addAction(DeleteAction);
    bar->addAction(DeleteAction);

    QAction *ModifyAction = new QAction("modify", bar);
    ModifyAction->setIcon(QIcon(":/myImage/images/edit.png"));
    ModifyAction->setToolTip(tr("Modify a student."));
    ModifyAction->setStatusTip(tr("Modify a student."));
    ModifyAction->setCheckable(true);
    ModifyAction->setChecked(true);
    group->addAction(ModifyAction);
    bar->addAction(ModifyAction);

    QAction *SortAction = new QAction("sort", bar);
    SortAction->setIcon(QIcon(":/myImage/images/sort.png"));
    SortAction->setToolTip(tr("学生信息排序"));
    SortAction->setStatusTip(tr("学生信息排序"));
    SortAction->setCheckable(true);
    SortAction->setChecked(true);
    group->addAction(SortAction);
    bar->addAction(SortAction);

    //设置tablewidget为不可编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);  
    //设置tablewidget为整行选取
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置tablewidget的列数
    ui->tableWidget->setColumnCount(info_len); 
    //设置tablewidget的行数
    ui->tableWidget->setRowCount(0);
    //ui->tableWidget->verticalHeader()->setVisible(false);   //隐藏列表头
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"学号"<<"姓名"<<"性别"<<"出生日期"<<"出生地"<<"专业");

    setCentralWidget(ui->horizontalLayoutWidget);
    setWindowIcon(QIcon(":/myImage/images/window.png"));
    setWindowTitle("学生信息管理系统");

    ui->actionNew->setIcon(QIcon(":/myImage/images/file_new.png"));
    ui->actionOpen->setIcon(QIcon(":/myImage/images/file_open.png"));
    ui->actionSave->setIcon(QIcon(":/myImage/images/file_save.png"));
    ui->actionAdd->setIcon(QIcon(":/myImage/images/menu_add.png"));
    ui->actionDelete->setIcon(QIcon(":/myImage/images/menu_delete.png"));
    ui->actionEdit->setIcon(QIcon(":/myImage/images/menu_edit.png"));
    ui->actionSort->setIcon(QIcon(":/myImage/images/menu_sort.png"));
    ui->actionAbout->setIcon(QIcon(":/myImage/images/about.png"));

    QLabel *statusMsg = new QLabel;
    statusBar()->addWidget(statusMsg);

    connect(ui->tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)),
            this, SLOT(ModifyActionTriggered()));

    connect(AddAction, SIGNAL(triggered()),
                    this, SLOT(AddActionTriggered()));

    connect(ModifyAction, SIGNAL(triggered()),
                    this, SLOT(ModifyActionTriggered()));
    connect(DeleteAction, SIGNAL(triggered()),
                    this, SLOT(DeleteActionTriggered()));
    connect(SortAction, SIGNAL(triggered()),
                    this, SLOT(SortActionTriggered()));

    connect(ui->actionOpen, SIGNAL(triggered()),
                    this, SLOT(OpenActionTriggered()));

    connect(ui->actionNew, SIGNAL(triggered()),
                    this, SLOT(NewActionTriggered()));

    connect(ui->actionSave, SIGNAL(triggered()),
                    this, SLOT(SaveActionTriggered()));

    connect(ui->actionAdd, SIGNAL(triggered()),
                    this, SLOT(AddActionTriggered()));
    connect(ui->actionDelete, SIGNAL(triggered()),
                    this, SLOT(DeleteActionTriggered()));
    connect(ui->actionEdit, SIGNAL(triggered()),
                    this, SLOT(ModifyActionTriggered()));
    connect(ui->actionSort, SIGNAL(triggered()),
                    this, SLOT(SortActionTriggered()));

    connect(ui->actionAbout, SIGNAL(triggered()),
                    this, SLOT(AboutActionTriggered()));

    this->resize(600, 500);
    all.ReadRecords("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenActionTriggered()
{
    SaveToFile("在打开新的文件之前是否保存已有文件?");
    QString filename = QFileDialog::getOpenFileName(this, tr("选择打开文件"),
                                                    "/Users/mac", tr("pdf文件(* pdf)"));
    all.ReadRecords(filename);
    LoadTable();
}

void MainWindow::NewActionTriggered()
{
    SaveToFile("在创建新文件之前是否保存已有文件?");

    all.ReadRecords("");
    LoadTable();
}

void MainWindow::SaveActionTriggered()
{
    if(all.GetFile()=="")
    {
        QString filename = QFileDialog::getSaveFileName(this, tr("选择保存文件"), "", tr("All Files (*)"));
        if(filename.isNull())
            return;
        all.SetFile(filename);
    }
    all.WriteRecords();
    is_changed = false;

    QString temp = "文件成功保存到 "+all.GetFile();

    QMessageBox message(QMessageBox::NoIcon, "Success", temp);
    message.setIconPixmap(QPixmap(":/myImage/images/success.png"));
    message.exec();
}

void MainWindow::AddActionTriggered()
{
    is_changed = true;
    QString info[6] = {"输入学号","输入姓名","","","输入出生地","输入专业"};
    NewWindow(info, -1);
    ui->tableWidget->selectRow(all.GetSize());
}

void MainWindow::DeleteActionTriggered()
{
    is_changed = true;
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem());
    QModelIndex index = ui->tableWidget->currentIndex();
    int number = index.row();
    QTableWidgetItem *item = ui->tableWidget->currentItem();

    if(item==Q_NULLPTR || !focus)
    {
        QMessageBox message(QMessageBox::NoIcon, "提示", "你需要选择一行来删除");
        message.setIconPixmap(QPixmap(":/myImage/images/hint.png"));
        message.exec();
        return;
    }

    else
    {
        QMessageBox message(QMessageBox::Warning,"Information","确定要删除这一信息吗？",QMessageBox::Yes|QMessageBox::Cancel,NULL);
        if (message.exec()==QMessageBox::Yes)
        {
            ui->tableWidget->removeRow(item->row());
            all.DeleteRecord(number);
        }
        else
        {
            return;
        }
    }
}

void MainWindow::ModifyActionTriggered()
{
    is_changed = true;
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem());
    QModelIndex index = ui->tableWidget->currentIndex();
    int number = index.row();
    QTableWidgetItem *item = ui->tableWidget->currentItem();

    if(item==Q_NULLPTR || !focus)
    {
        QMessageBox message(QMessageBox::NoIcon, "提示", "你需要选择一行以进行修改");
        message.setIconPixmap(QPixmap(":/myImage/images/hint.png"));
        message.exec();
        return;
    }

    QList<Student> temp = all.GetList();

    QString *info = temp[number].info;
    NewWindow(info, number);
    ui->tableWidget->selectRow(number);
}


void MainWindow::SortActionTriggered()
{
    QWidget *w = new QWidget;
    w->setFixedSize(300, 250);
    QFormLayout *form = new QFormLayout;

    QComboBox *sortline = new QComboBox;
    sortline->insertItem(0, "学号");
    sortline->insertItem(1, "姓名");
    mainsortline = sortline;

   QComboBox *orderline = new QComboBox;
   orderline->insertItem(0, "升序排列");
   orderline->insertItem(1, "降序排列");
   mainorderline = orderline;

    //确认按钮
    QPushButton *buttonOk=new QPushButton("排序");
    connect(buttonOk,SIGNAL(pressed()),w,SLOT(close()));
    connect(buttonOk, SIGNAL(pressed()), this, SLOT(SortInfo()));

    //取消按钮
    QPushButton *buttonCancel=new QPushButton("取消");
    connect(buttonCancel,SIGNAL(pressed()),w,SLOT(close()));

    //确认，取消按钮布局
    QHBoxLayout *buttonLayout=new QHBoxLayout();
    //buttonLayout->setSizeConstraint(QLayout::SetFixedSize);
    buttonLayout->addWidget(buttonOk);
    buttonLayout->addWidget(buttonCancel);

    //formlayout布局
    form->addRow("&选择排序方式:  ", sortline);
    form->addRow("&选择排序次序:  ", orderline);
    form->addRow(buttonLayout);

    w->setLayout(form);
    w->setWindowModality(Qt::ApplicationModal);
    w->show();
}

void MainWindow::AddInfo()
{
    QString info[info_len];
    info[0] = mainnoline->text();
    info[1] = mainnameline->text();
    info[2] = mainsexline->currentText();
    info[3] = maindateline->text();
    info[4] = mainplaceline->text();
    info[5] = mainmajorline->text();
    Student s(info);

    all.AddRecord(s);
    LoadTable();
}

void MainWindow::ModifyInfo()
{
    QModelIndex index = ui->tableWidget->currentIndex();
    int lineno = index.row();

    QString info[info_len];
    info[0] = mainnoline->text();
    info[1] = mainnameline->text();
    info[2] = mainsexline->currentText();
    info[3] = maindateline->text();
    info[4] = mainplaceline->text();
    info[5] = mainmajorline->text();
    Student s(info);

    all.ModifyRecord(lineno, s);
    LoadTable();
}

void MainWindow::SortInfo()
{
    QString sortway = mainsortline->currentText();
    QString sortorder = mainorderline->currentText();

    int way;
    bool order;
    if(sortway=="学号")
        way = 0;
    else
        way = 1;

    if(sortorder=="升序")
        order=true;
    else
        order=false;

    all.SortRecords(way, order);

    LoadTable();
}

void MainWindow::NewWindow(QString *info, int lineno)
{
    QWidget *w = new QWidget;
    w->setFixedSize(350, 320);
    QFormLayout *form = new QFormLayout;
    QString notext=info[0], nametext=info[1], sextext=info[2],
            datetext=info[3], placetext=info[4], majortext=info[5];

    //输入学号行
    QLineEdit *noline = new QLineEdit(notext);
    mainnoline = noline;

    //输入姓名行
    QLineEdit *nameline = new QLineEdit(nametext);
    mainnameline = nameline;

    //选择性别行
    QComboBox *sexline = new QComboBox;
    sexline->insertItem(0, QIcon(":/myImage/images/male.png"), "男");
    sexline->insertItem(1, QIcon(":/myImage/images/female.png"), "女");
    if(sextext=="女")
        sexline->setCurrentIndex(1);
    mainsexline = sexline;

    //选择日期行
    QDateEdit *dateline = new QDateEdit;
    dateline->setDisplayFormat("yyyy-MM-dd");
    if(datetext=="")
        dateline->setDateTime(QDateTime::currentDateTime());
    else
    {
        QDateTime datetime = QDateTime::fromString(datetext, "yyyy-MM-dd");
        dateline->setDateTime(datetime);
    }
    maindateline = dateline;

    //输入地点行
    QLineEdit *placeline = new QLineEdit(placetext);
    mainplaceline = placeline;

    //输入专业行
    QLineEdit *majorline = new QLineEdit(majortext);
    mainmajorline = majorline;

    //确认按钮
    QPushButton *buttonOk=new QPushButton("确认");
    connect(buttonOk,SIGNAL(pressed()),w,SLOT(close()));
    if(lineno==-1)
        connect(buttonOk, SIGNAL(pressed()), this, SLOT(AddInfo()));
    else
        connect(buttonOk, SIGNAL(pressed()), this, SLOT(ModifyInfo()));

    //取消按钮
    QPushButton *buttonCancel=new QPushButton("取消");
    connect(buttonCancel,SIGNAL(pressed()),w,SLOT(close()));

    //确认，取消按钮布局
    QHBoxLayout *buttonLayout=new QHBoxLayout();
    //buttonLayout->setSizeConstraint(QLayout::SetFixedSize);
    buttonLayout->addWidget(buttonOk);
    buttonLayout->addWidget(buttonCancel);

    //formlayout布局
    form->addRow("&学号:  ", noline);
    form->addRow("&姓名:  ", nameline);
    form->addRow("&性别:  ", sexline);
    form->addRow("出生&日期:  ", dateline);
    form->addRow("出&生地:  ", placeline);
    form->addRow("&专业:  ", majorline);
    form->addRow(buttonLayout);

    w->setLayout(form);
    w->setWindowModality(Qt::ApplicationModal);
    w->show();
}

void MainWindow::LoadTable()
{
    QList<Student> temp = all.GetList();

    ui->tableWidget->setRowCount(temp.size());

    for(int i=0; i<temp.size();i++)
        for(int j=0; j<info_len; j++)
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(temp[i].info[j]));

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    SaveToFile("在关闭程序之前是否保存已有文件?");
}

void MainWindow::SaveToFile(const char *Log)
{
    if(is_changed==false)
        return;

    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Question"),
                                                  tr(Log),
                                                  QMessageBox::Yes | QMessageBox::No,
                                                  QMessageBox::Yes))
    {
        if(all.GetFile()=="")
        {
            QString filename = QFileDialog::getSaveFileName(this, tr("选择保存文件"), "", tr("All Files (*)"));
            if(filename.isNull())
                return;

            all.SetFile(filename);
        }
        all.WriteRecords();
        QString temp = "文件成功保存到 "+all.GetFile();
        QMessageBox message(QMessageBox::NoIcon, "Success", temp);
        message.setIconPixmap(QPixmap(":/myImage/images/success.png"));
        message.exec();
    }

    is_changed = false;
}

void MainWindow::AboutActionTriggered()
{
    QMessageBox message(QMessageBox::NoIcon, "关于", "这是一款学生信息管理系统，功能包括：\n(1) 学生信息的增加\n"
                                                  "(2) 学生信息的删除\n(3) 学生信息的修改\n(4) 从文件读取和用文件保存学生信息\n"
                                                  "此外还支持排序功能\n"
                                                  "开始使用吧！");
    message.setIconPixmap(QPixmap(":/myImage/images/about.png"));
    message.exec();
}
