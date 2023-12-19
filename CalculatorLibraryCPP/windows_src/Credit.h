#pragma once

#ifdef MODELLIBRARY_EXPORTS
#define MODELLIBRARY_API __declspec(dllexport)
#else
#define MODELLIBRARY_API __declspec(dllimport)
#endif

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

extern "C" MODELLIBRARY_API s21::CreditCalc* CreateCreditClass();

extern "C" MODELLIBRARY_API void DisposeCreditClass(
    s21::CreditCalc* ptr_object);

extern "C" MODELLIBRARY_API void CallCreditCalculate(
    s21::CreditCalc* ptr_object, double sum, double term, double percent,
    int method);

extern "C" MODELLIBRARY_API double CallCreditTotalSum(
    s21::CreditCalc* ptr_object);

extern "C" MODELLIBRARY_API double CallCreditMonthlyPayment(
    s21::CreditCalc* ptr_object);

extern "C" MODELLIBRARY_API double CallCreditOverpayment(
    s21::CreditCalc* ptr_object);

extern "C" MODELLIBRARY_API const char* CallCreditGetError(
    s21::CreditCalc* ptr_object);
