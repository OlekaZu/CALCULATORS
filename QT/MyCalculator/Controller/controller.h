#ifndef CONTROLLER_CONTROLLER_H
#define CONTROLLER_CONTROLLER_H
#include <string>

#include "Model/calculator_model.h"
#include "Model/credit_model.h"
#include "Model/deposit_model.h"

class Controller {
 public:
  Controller();
  ~Controller() {}

  std::pair<double, std::string> PushOnButtonEqual(std::string input,
                                                   double x_argument);
  std::tuple<double, double, double, std::string> CreditCalc(double sum,
                                                             double term,
                                                             double percent,
                                                             size_t method);
  std::tuple<double, double, double, std::string> DepositCalc(
      double sum, double term, double percent, double tax, size_t method,
      double put_flow, double draw_flow);

 private:
  std::unique_ptr<CalculatorModel> calculator_;
  std::unique_ptr<CreditModel> credit_;
  std::unique_ptr<DepositModel> deposit_;
};

#endif  // CONTROLLER_CONTROLLER_H
