#include "Deposit.h"

namespace s21 {
/* --- Public Methods --- */
DepositCalc::DepositCalc() : percent_sum_(0), tax_sum_(0), total_sum_(0) {}
DepositCalc::~DepositCalc() {}

void DepositCalc::Calculate(double sum, double term, double percent, double tax,
                            size_t method, double put_flow, double draw_flow) {
  double percent_monthly = percent / 100 / 12;
  double percent_quarter = percent / 100 / 4;
  double tax_rate = tax / 100;
  double max_tax_free = 0;
  double put_sum = 0;
  double draw_sum = 0;
  if (method == 1) {
    double put_flow_percent =
        round(put_flow * (pow(1 + percent_monthly, term / 2) - 1) * term);
    double draw_flow_percent =
        round(draw_flow * (pow(1 + percent_monthly, term / 2) - 1) * term);
    percent_sum_ = round(sum * (pow((1 + percent_monthly), term) - 1)) +
                   put_flow_percent - draw_flow_percent;
    max_tax_free = round(sum * (pow((1 + kRateTaxBegin / 12), term) - 1));
    put_sum = put_flow * (term - 1);
    draw_sum = draw_flow * (term - 1);
  } else if (method == 2) {
    double put_flow_percent = round(
        put_flow * (pow(1 + percent_quarter, term / 3 / 2) - 1) * term / 3);
    double draw_flow_percent = round(
        draw_flow * (pow(1 + percent_quarter, term / 3 / 2) - 1) * term / 3);
    percent_sum_ = round(sum * (pow((1 + percent_quarter), term / 3) - 1)) +
                   put_flow_percent - draw_flow_percent;
    max_tax_free = round(sum * (pow((1 + kRateTaxBegin / 4), term / 3) - 1));
    put_sum = put_flow * ceil(term / 3);
    draw_sum = draw_flow * ceil(term / 3);
  } else if (method == 3) {
    double new_sum = sum;
    for (int i = 0; i < term; i++) {
      percent_sum_ += (new_sum * percent_monthly);
      max_tax_free += round(kRateTaxBegin / 12 * new_sum);
      new_sum = new_sum + put_flow - draw_flow;
    }
    percent_sum_ = round(percent_sum_);
    put_sum = put_flow * (term - 1);
    draw_sum = draw_flow * (term - 1);
  } else {
    error_ = "Input capitalization or Check percent drawing";
  }

  if (percent_sum_ > max_tax_free)
    tax_sum_ = round((percent_sum_ - max_tax_free) * tax_rate);
  total_sum_ = round(sum + percent_sum_ - tax_sum_ + put_sum - draw_sum);
}

double DepositCalc::GetPercentSum() { return percent_sum_; }
double DepositCalc::GetTaxSum() { return tax_sum_; }
double DepositCalc::GetTotalSum() { return total_sum_; }
std::string DepositCalc::GetError() { return error_; }

const char* ConvertDepositErrorString(s21::DepositCalc* ptr_object) {
  std::string res;
  if (ptr_object) {
    res = ptr_object->GetError();
  } else {
    res = "Object isn't exist.";
  }
  char* buf = _strdup(res.c_str());
  return buf;
}

}  // namespace s21

s21::DepositCalc* CreateDepositClass() { return new s21::DepositCalc(); }

void DisposeDepositClass(s21::DepositCalc* ptr_object) {
  if (ptr_object != NULL) {
    delete ptr_object;
    ptr_object = NULL;
  }
}

void CallDepositCalculate(s21::DepositCalc* ptr_object, double sum, double term,
                          double percent, double tax, int method,
                          double put_flow, double draw_flow) {
  if (ptr_object != NULL) {
    ptr_object->Calculate(sum, term, percent, tax, method, put_flow, draw_flow);
  }
}

double CallDepositPercentSum(s21::DepositCalc* ptr_object) {
  double res = 0;
  if (ptr_object != NULL) {
    res = ptr_object->GetPercentSum();
  }
  return res;
}

double CallDepositTaxSum(s21::DepositCalc* ptr_object) {
  double res = 0;
  if (ptr_object != NULL) {
    res = ptr_object->GetTaxSum();
  }
  return res;
}

double CallDepositTotalSum(s21::DepositCalc* ptr_object) {
  double res = 0;
  if (ptr_object != NULL) {
    res = ptr_object->GetTotalSum();
  }
  return res;
}

const char* CallDepositGetError(s21::DepositCalc* ptr_object) {
  return s21::ConvertDepositErrorString(ptr_object);
}
