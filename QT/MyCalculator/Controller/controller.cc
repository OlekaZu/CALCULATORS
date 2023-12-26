#include "controller.h"

Controller::Controller() : calculator_(std::make_unique<CalculatorModel>()) {}

std::pair<double, std::string> Controller::PushOnButtonEqual(
    std::string input, double x_argument) {
  calculator_->Calculate(input, x_argument);
  return std::make_pair(calculator_->GetData(), calculator_->GetError());
}

std::tuple<double, double, double, std::string> Controller::CreditCalc(
    double sum, double term, double percent, size_t method) {
  credit_ = std::make_unique<CreditModel>();
  credit_->Calculate(sum, term, percent, method);
  return std::make_tuple(credit_->GetMonthlyPayment(), credit_->GetCreditSum(),
                         credit_->GetTotalSum(), credit_->GetError());
}

std::tuple<double, double, double, std::string> Controller::DepositCalc(
    double sum, double term, double percent, double tax, size_t method,
    double put_flow, double draw_flow) {
  deposit_ = std::make_unique<DepositModel>();
  deposit_->Calculate(sum, term, percent, tax, method, put_flow, draw_flow);
  return std::make_tuple(deposit_->GetPercentSum(), deposit_->GetTaxSum(),
                         deposit_->GetTotalSum(), deposit_->GetError());
}
