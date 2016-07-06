#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitUI();
    GetNovelLists();

    connect(this->m_novel_list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(get_current_chapters()));
    connect(this->m_chaptr_list,SIGNAL(itemSelectionChanged()),this,SLOT(show_chapter_text()));
    connect(this->m_next_chapter_btn,SIGNAL(clicked(bool)),this,SLOT(change_to_next_chapter()));
    connect(this->m_previous_chapter_btn,SIGNAL(clicked(bool)),this,SLOT(change_to_previous_chapter()));

}

void MainWindow::InitUI()
{
 //   ui->menuBar->setVisible(false);
  //  ui->statusBar->setVisible(false);

    ui->mainToolBar->setVisible(false);


    m_novel_list_label = new QLabel;
    m_novel_list = new QListWidget;
    m_writer_novels_label = new QLabel;
    m_writer_novel_list = new QListWidget;

    m_current_novel_textbrowser = new QTextBrowser;
    m_previous_chapter_btn = new QPushButton;
    m_next_chapter_btn = new QPushButton;

    m_previous_chapter_btn->setText("previous chapter");
    m_next_chapter_btn->setText("next chapter");

    m_chaptr_list = new QListWidget;

    m_novel_list_label->setText("lists of novels");
    m_writer_novels_label->setText("the writer's other novels");

    QVBoxLayout * vboxlayout_left = new QVBoxLayout;
    vboxlayout_left->addWidget(m_novel_list_label,1);
    vboxlayout_left->addWidget(m_novel_list,10);
    vboxlayout_left->addWidget(m_writer_novels_label,1);
    vboxlayout_left->addWidget(m_writer_novel_list,5);

    QHBoxLayout *vhboxlayout_mid_buttom = new QHBoxLayout;

    vhboxlayout_mid_buttom->addWidget(m_previous_chapter_btn,1);
    vhboxlayout_mid_buttom->addStretch(2);
    vhboxlayout_mid_buttom->addWidget(m_next_chapter_btn,1);

    QVBoxLayout * vboxlayout_mid = new QVBoxLayout;
    vboxlayout_mid->addWidget(m_current_novel_textbrowser,10);
    vboxlayout_mid->addLayout(vhboxlayout_mid_buttom);

    QVBoxLayout * vboxlayout_right = new QVBoxLayout;
    vboxlayout_right->addWidget(m_chaptr_list);

    QHBoxLayout * hboxlayout = new QHBoxLayout;
    hboxlayout->addLayout(vboxlayout_left,1);
    hboxlayout->addLayout(vboxlayout_mid,3);
    hboxlayout->addLayout(vboxlayout_right,1);

    ui->centralWidget->setLayout(hboxlayout);

    m_current_novel_textbrowser->setText("hlll");






    this->resize(QApplication::desktop()->width()/2,QApplication::desktop()->height()/2);
}

void MainWindow::GetNovelLists()
{
    QString novel_sets_dir = "F:/NOVELS";
    QStringList novel_sets;



    m_novel_list->addItems(get_dir_files(novel_sets_dir));
}
QStringList MainWindow::get_dir_files(QString root_dir_str)
{
    QDir root_dir(root_dir_str);
    QStringList tmp_list;
    if (!root_dir.exists())
    {
        return tmp_list;
    }

    QFileInfoList fileinfo_list = root_dir.entryInfoList();

    QFileInfo fileinfo;

    for(int i = 0;i < fileinfo_list.size();i++)
    {
        fileinfo = fileinfo_list.at(i);

        if(fileinfo.fileName() == "."||fileinfo.fileName() == "..")
            continue;
        tmp_list.push_back(fileinfo.fileName());
    }
    return tmp_list;
}
void MainWindow::get_current_chapters()
{
    this->m_chaptr_list->clear();
    QString novel_name = this->m_novel_list->currentItem()->text();
    QString novel_sets_dir;
    novel_sets_dir = novel_sets_dir + "F:/NOVELS"+"/"+novel_name;
    this->m_chaptr_list->addItems(get_dir_files(novel_sets_dir));

}

void MainWindow::show_chapter_text()
{
    this->m_current_novel_textbrowser->clear();
    QString chapter_name = this->m_chaptr_list->currentItem()->text();
    QString novel_name = this->m_novel_list->currentItem()->text();
    QString chapter_file;
    chapter_file = chapter_file + "F:/NOVELS"+"/"+novel_name + "/" + chapter_name;





    QFile fp(chapter_file);

    if (fp.exists())
    {
        //解决中文乱码问题
        fp.open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream file(&fp);
        QString text = file.readAll();
        this->m_current_novel_textbrowser->setText(text);
        fp.close();
    }

}

void MainWindow::change_to_next_chapter()
{
    int index = this->m_chaptr_list->currentRow();

    int cnt = this->m_chaptr_list->count();
    index = (index + 1) % cnt;


    this->m_chaptr_list->setCurrentRow(index);
   // get_current_chapters();

}

void MainWindow::change_to_previous_chapter()
{
    int index = this->m_chaptr_list->currentRow();

    int cnt = this->m_chaptr_list->count();
    index = (index - 1+ cnt) % cnt;


    this->m_chaptr_list->setCurrentRow(index);
}
MainWindow::~MainWindow()
{
    delete ui;
}
