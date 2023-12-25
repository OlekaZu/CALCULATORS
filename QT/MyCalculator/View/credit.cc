#include "credit.h"

#include <QLocale>

#include "qvalidator.h"
#include "ui_credit.h"

Credit::Credit(std::shared_ptr<Controller> sender, QWidget *parent)
    : QDialog(parent), ui_(std::make_unique<Ui::Credit>()) {
  ui_->setupUi(this);
  credit_sender_ = sender;
  QDoubleValidator *format_double = new QDoubleValidator(0, INFINITY, 2, this);
  format_double->setLocale(QLocale::c());
  ui_->input_sum->setValidator(format_double);
  ui_->input_percent->setValidator(format_double);
  ui_->input_period->setValidator(new QIntValidator(0, 100, this));
}

Credit::~Credit() {}

void Credit::on_button_exit_clicked() { reject(); }

void Credit::on_button_calc_clicked() {
  double input_sum = (ui_->input_sum->text()).toDouble();
  int input_period = (ui_->input_period->text()).toInt();
  double input_percent = (ui_->input_percent->text()).toDouble();
  size_t method_percent = 0;
  if (ui_->check_annuitet->isChecked()) {
    method_percent = 1;
  } else if (ui_->check_different->isChecked()) {
    method_percent = 2;
  }

  std::tuple<double, double, double, std::string> result =
      credit_sender_->CreditCalc(input_sum, input_period, input_percent,
                                 method_percent);
  if (std::get<3>(result).empty() == true)
    ui_->output_monthpay->setText(
        QString::asprintf("%.0f", (std::get<0>(result))));
  else
    ui_->output_monthpay->setText(QString::fromStdString(std::get<3>(result)));

  ui_->output_creditsum->setText(
      QString::asprintf("%.0f", (std::get<1>(result))));
  ui_->output_total->setText(QString::asprintf("%.0f", (std::get<2>(result))));
}
