#ifndef VIEW_MAINWINDOW_H
#define VIEW_MAINWINDOW_H

#include <QMainWindow>

#include "Controller/controller.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
 public slots:
  QString on_pushButton_equal_clicked();

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  std::unique_ptr<Ui::MainWindow> ui_;
  std::shared_ptr<Controller> sender_;
  std::unique_ptr<Graph> graph_window_;
  size_t count_left_bracket_;
  size_t count_right_bracket_;
  size_t count_equal_press_;

 private slots:
  void read_buttons();
  void on_pushButton_del_clicked();
  void on_pushButton_del_last_clicked();
  void on_pushButton_graph_clicked();
  void on_pushButton_credit_clicked();
  void on_pushButton_deposit_clicked();
};
#endif  // VIEW_MAINWINDOW_H
