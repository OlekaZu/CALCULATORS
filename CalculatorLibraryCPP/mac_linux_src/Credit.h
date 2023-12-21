#pragma once
#ifndef MODEL_CREDIT_H_
#define MODEL_CREDIT_H_

#define _USE_MATH_DEFINES
#include <cmath>
#include <locale>

namespace s21 {
class CreditCalc {
 public:
  CreditCalc();
  ~CreditCalc();
  void Calculate(double sum, double term, double percent, size_t method);
  double GetTotalSum();
  double GetMonthlyPayment();
  double GetCreditSum();
  std::string GetError();

 private:
  double total_sum_;
  double monthly_payment_;
  double credit_sum_;
  std::string error_;
};

}  // namespace s21

extern "C" s21::CreditCalc* CreateCreditClass();

extern "C" void DisposeCreditClass(s21::CreditCalc* ptr_object);

extern "C" void CallCreditCalculate(s21::CreditCalc* ptr_object, double sum,
                                    double term, double percent, int method);

extern "C" double CallCreditTotalSum(s21::CreditCalc* ptr_object);

extern "C" double CallCreditMonthlyPayment(s21::CreditCalc* ptr_object);

extern "C" double CallCreditOverpayment(s21::CreditCalc* ptr_object);

extern "C" const char* CallCreditGetError(s21::CreditCalc* ptr_object);

#endif  // MODEL_CREDIT_H_