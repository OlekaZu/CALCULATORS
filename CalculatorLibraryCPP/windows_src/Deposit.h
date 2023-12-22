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

extern "C" MODELLIBRARY_API s21::DepositCalc* CreateDepositClass();

extern "C" MODELLIBRARY_API void DisposeDepositClass(
    s21::DepositCalc* ptr_object);

extern "C" MODELLIBRARY_API void CallDepositCalculate(
    s21::DepositCalc* ptr_object, double sum, double term, double percent,
    double tax, int method, double put_flow, double draw_flow);

extern "C" MODELLIBRARY_API double CallDepositPercentSum(
    s21::DepositCalc* ptr_object);

extern "C" MODELLIBRARY_API double CallDepositTaxSum(
    s21::DepositCalc* ptr_object);

extern "C" MODELLIBRARY_API double CallDepositTotalSum(
    s21::DepositCalc* ptr_object);

extern "C" MODELLIBRARY_API const char* CallDepositGetError(
    s21::DepositCalc* ptr_object);
