#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QStringList>
#include <QTextBrowser>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void InitUI();
    void GetNovelLists();
    QStringList get_dir_files(QString root_dir);
private slots:
    void get_current_chapters();
    void show_chapter_text();
    void change_to_next_chapter();
    void change_to_previous_chapter();

private:
    Ui::MainWindow *ui;
    QLabel * m_novel_list_label;
    QListWidget * m_novel_list;
    QLabel * m_writer_novels_label;
    QListWidget * m_writer_novel_list;
    QTextBrowser * m_current_novel_textbrowser;
    QListWidget * m_chaptr_list;
    QPushButton * m_previous_chapter_btn;
    QPushButton * m_next_chapter_btn;
};

#endif // MAINWINDOW_H
