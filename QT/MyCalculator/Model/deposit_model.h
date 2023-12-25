#ifndef MODEL_DEPOSITMODEL_H
#define MODEL_DEPOSITMODEL_H
#include <cmath>
#include <locale>

class DepositModel {
 public:
  DepositModel();
  ~DepositModel();
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

#endif  // MODEL_DEPOSITMODEL_H
