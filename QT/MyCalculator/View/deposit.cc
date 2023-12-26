#include "deposit.h"

#include <QLocale>

#include "qvalidator.h"
#include "ui_deposit.h"

Deposit::Deposit(std::shared_ptr<Controller> sender, QWidget *parent)
    : QDialog(parent), ui_(std::make_unique<Ui::Deposit>()) {
  ui_->setupUi(this);
  deposit_sender_ = sender;
  QDoubleValidator *format_double = new QDoubleValidator(0, INFINITY, 2, this);
  format_double->setLocale(QLocale::c());
  ui_->input_sum->setValidator(format_double);
  ui_->input_percent->setValidator(format_double);
  ui_->input_period->setValidator(new QIntValidator(0, 100, this));
  ui_->put_sum->setValidator(format_double);
  ui_->draw_sum->setValidator(format_double);
}

Deposit::~Deposit() {}

void Deposit::on_button_exit_clicked() { reject(); }

void Deposit::on_button_calc_clicked() {
  double input_sum = (ui_->input_sum->text()).toDouble();
  int input_period = (ui_->input_period->text()).toInt();
  double input_percent = (ui_->input_percent->text()).toDouble();
  double put_flow = 0;
  double draw_flow = 0;
  if (ui_->check_put->isChecked()) put_flow = (ui_->put_sum->text()).toDouble();
  if (ui_->check_draw->isChecked())
    draw_flow = (ui_->draw_sum->text()).toDouble();
  size_t method_capital = 0;
  if (ui_->capital_month->isChecked())
    method_capital = 1;
  else if (ui_->capital_quarter->isChecked())
    method_capital = 2;
  else if (ui_->capital_month->isChecked())
    method_capital = 3;
  double tax_rate = (ui_->input_tax_rate->text()).toDouble();

  std::tuple<double, double, double, std::string> result =
      deposit_sender_->DepositCalc(input_sum, input_period, input_percent,
                                   tax_rate, method_capital, put_flow,
                                   draw_flow);
  if (std::get<3>(result).empty() == true)
    ui_->output_percentsum->setText(
        QString::asprintf("%.0f", (std::get<0>(result))));
  else
    ui_->output_percentsum->setText(
        QString::fromStdString(std::get<3>(result)));

  ui_->output_tax->setText(QString::asprintf("%.0f", (std::get<1>(result))));
  ui_->output_total->setText(QString::asprintf("%.0f", (std::get<2>(result))));
}
