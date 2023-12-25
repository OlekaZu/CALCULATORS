#ifndef MODEL_CREDITMODEL_H
#define MODEL_CREDITMODEL_H
#include <cmath>
#include <locale>

class CreditModel {
 public:
  CreditModel();
  ~CreditModel();
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

#endif  // MODEL_CREDITMODEL_H
