#include "./mainwindow.h"

#include "./ui_mainwindow.h"
#include "credit.h"
#include "deposit.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(std::make_unique<Ui::MainWindow>()) {
  count_left_bracket_ = 0;
  count_right_bracket_ = 0;
  count_equal_press_ = 0;
  ui_->setupUi(this);
  connect(ui_->pushButton_0, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_1, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_2, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_3, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_4, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_5, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_6, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_7, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_8, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_9, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_dot, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_add, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_sub, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_mult, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_div, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_pow, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_mod, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_lbracket, SIGNAL(clicked()), this,
          SLOT(read_buttons()));
  connect(ui_->pushButton_rbracket, SIGNAL(clicked()), this,
          SLOT(read_buttons()));
  connect(ui_->pushButton_ln, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_log, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_cos, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_sin, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_tan, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_acos, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_asin, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_atan, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_x, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_pi, SIGNAL(clicked()), this, SLOT(read_buttons()));
  connect(ui_->pushButton_exp_high, SIGNAL(clicked()), this,
          SLOT(read_buttons()));
  connect(ui_->pushButton_exp_low, SIGNAL(clicked()), this,
          SLOT(read_buttons()));
  sender_ = std::make_shared<Controller>();
}

MainWindow::~MainWindow() {}

void MainWindow::read_buttons() {
  if (count_equal_press_) {
    ui_->label_input->clear();
    count_equal_press_ = 0;
  }
  QPushButton *button = (QPushButton *)sender();
  QString input_str_view;
  QString tmp_str = ui_->label_input->text();
  int length = tmp_str.length();

  if (length > 0 &&
      (button->text() == "." || button->text() == "+" ||
       button->text() == "-" || button->text() == "×" ||
       button->text() == "÷" || button->text() == "^") &&
      (!tmp_str.compare(tmp_str[length - 1], ".") ||
       !tmp_str.compare(tmp_str[length - 1], "+") ||
       !tmp_str.compare(tmp_str[length - 1], "×") ||
       !tmp_str.compare(tmp_str[length - 1], "÷") ||
       !tmp_str.compare(tmp_str[length - 1], "-") ||
       !tmp_str.compare(tmp_str[length - 1], "^"))) {
    input_str_view = ui_->label_input->text() + "";
  } else if (button->text() == "sin" || button->text() == "cos" ||
             button->text() == "tan" || button->text() == "acos" ||
             button->text() == "asin" || button->text() == "acos" ||
             button->text() == "atan" || button->text() == "log" ||
             button->text() == "ln" || button->text() == "√") {
    input_str_view = ui_->label_input->text() + button->text() + "(";
    ++count_left_bracket_;
  } else if (button->text() == "Argument X") {
    input_str_view = ui_->label_input->text() + "x";
  } else {
    if (button->text() == "(") ++count_left_bracket_;
    if (button->text() == ")") ++count_right_bracket_;
    input_str_view = ui_->label_input->text() + button->text();
  }
  if (length < 256)
    ui_->label_input->setText(input_str_view);
  else
    ui_->label_result->setText("The maximun size of input is exceeded");
}

QString MainWindow::on_pushButton_equal_clicked() {
  ++count_equal_press_;
  if (count_left_bracket_ > count_right_bracket_) {
    for (int i = (count_left_bracket_ - count_right_bracket_); i != 0; --i)
      ui_->label_input->setText(ui_->label_input->text() + ')');
  }
  if (!(ui_->label_input->text().contains('=')))
    ui_->label_input->setText(ui_->label_input->text() + '=');

  QString input_str = ui_->label_input->text();
  input_str.replace("÷", "/");
  input_str.replace("×", "*");
  input_str.replace("√", "sqrt");
  input_str.replace("π‎", "P");
  input_str.replace("=", "");

  double x = (ui_->lineEdit_x->text()).toDouble();
  std::string input_string = input_str.toStdString();
  std::pair<double, std::string> result =
      sender_->PushOnButtonEqual(input_string, x);
  if (result.second.size())
    ui_->label_result->setText(QString::fromStdString(result.second));
  else
    ui_->label_result->setText(QString::number(result.first, 'g', 12));

  count_left_bracket_ = 0;
  count_right_bracket_ = 0;
  return input_str;
}

void MainWindow::on_pushButton_del_clicked() {
  ui_->label_input->setText("");
  ui_->label_result->setText("");
  count_left_bracket_ = 0;
  count_right_bracket_ = 0;
  count_equal_press_ = 0;
}

void MainWindow::on_pushButton_del_last_clicked() {
  QString tmp_str = ui_->label_input->text();
  int length = tmp_str.length();
  if (length > 0) {
    if (!tmp_str.compare(tmp_str[length - 1], "(") && count_left_bracket_)
      --count_left_bracket_;
    if (!tmp_str.compare(tmp_str[length - 1], ")") && count_right_bracket_)
      --count_right_bracket_;
    tmp_str.resize(length - 1);
  }
  ui_->label_input->setText(tmp_str);
}

void MainWindow::on_pushButton_graph_clicked() {
  graph_window_ = std::make_unique<Graph>();
  QString input_for_graph = on_pushButton_equal_clicked();
  graph_window_->DrawChart(input_for_graph, sender_);
  graph_window_->show();
}

void MainWindow::on_pushButton_credit_clicked() {
  Credit credit_window(sender_);
  credit_window.setModal(true);
  credit_window.exec();
}

void MainWindow::on_pushButton_deposit_clicked() {
  Deposit deposit_window(sender_);
  deposit_window.setModal(true);
  deposit_window.exec();
}
