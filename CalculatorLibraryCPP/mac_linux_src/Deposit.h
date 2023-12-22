#pragma once

#ifndef MODEL_DEPOSIT_H_
#define MODEL_DEPOSIT_H_

#define _USE_MATH_DEFINES
#include <cmath>
#include <locale>

namespace s21 {
class DepositCalc {
 public:
  DepositCalc();
  ~DepositCalc();
  void Calculate(double sum, double term, double percent, double tax,
                 size_t method, double put_flow, double draw_flow);
  double GetPercentSum();
  double GetTaxSum();
  double GetTotalSum();
  std::string GetError();

 private:
  const double kRateTaxBegin = 0.18;
  double percent_sum_;
  double tax_sum_;
  double total_sum_;
  std::string error_;
};

}  // namespace s21

extern "C" s21::DepositCalc* CreateDepositClass();

extern "C" void DisposeDepositClass(s21::DepositCalc* ptr_object);

extern "C" void CallDepositCalculate(s21::DepositCalc* ptr_object, double sum,
                                     double term, double percent, double tax,
                                     int method, double put_flow,
                                     double draw_flow);

extern "C" double CallDepositPercentSum(s21::DepositCalc* ptr_object);

extern "C" double CallDepositTaxSum(s21::DepositCalc* ptr_object);

extern "C" double CallDepositTotalSum(s21::DepositCalc* ptr_object);

extern "C" const char* CallDepositGetError(s21::DepositCalc* ptr_object);

#endif  // MODEL_DEPOSIT_H_
