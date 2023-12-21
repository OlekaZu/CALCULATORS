#include "Credit.h"

namespace s21 {
/* --- Public Methods --- */
CreditCalc::CreditCalc() : total_sum_(0), monthly_payment_(0), credit_sum_(0) {}
CreditCalc::~CreditCalc() {}

void CreditCalc::Calculate(double sum, double term, double percent,
                           size_t method) {
  double percent_monthly = percent / 12 / 100;
  double temp_creditsum = sum * percent_monthly;
  double sum_reminder = sum;
  if (method == 1) {
    monthly_payment_ =
        round(sum * (percent_monthly +
                     percent_monthly / (pow(1 + percent_monthly, term) - 1)));

    for (int i = 1; i < term; i++) {
      temp_creditsum += (sum_reminder - (monthly_payment_ - temp_creditsum)) *
                        percent_monthly;
      sum_reminder -= monthly_payment_;
    }
    sum_reminder = sum_reminder - (monthly_payment_ - temp_creditsum);

    credit_sum_ = round(temp_creditsum - sum_reminder);
    total_sum_ = sum + credit_sum_;
  } else if (method == 2) {
    double debt_monthpayment = round(sum / term);
    for (int i = 1; i < term; i++) {
      sum_reminder -= debt_monthpayment;
      temp_creditsum += sum_reminder * percent_monthly;
    }
    monthly_payment_ =
        round(sum_reminder * percent_monthly + debt_monthpayment);
    credit_sum_ = round(temp_creditsum);
    total_sum_ = sum + credit_sum_;
  } else {
    error_ = "Input percent metnod!";
  }
}

double CreditCalc::GetTotalSum() { return total_sum_; }
double CreditCalc::GetMonthlyPayment() { return monthly_payment_; }
double CreditCalc::GetCreditSum() { return credit_sum_; }
std::string CreditCalc::GetError() { return error_; }

const char* ConvertCreditErrorString(s21::CreditCalc* ptr_object) {
  std::string res;
  if (ptr_object) {
    res = ptr_object->GetError();
  } else {
    res = "Object isn't exist.";
  }
  char* buf = const_cast<char*>(res.c_str());
  return buf;
}

}  // namespace s21

s21::CreditCalc* CreateCreditClass() { return new s21::CreditCalc(); }

void DisposeCreditClass(s21::CreditCalc* ptr_object) {
  if (ptr_object != NULL) {
    delete ptr_object;
    ptr_object = NULL;
  }
}

void CallCreditCalculate(s21::CreditCalc* ptr_object, double sum, double term,
                         double percent, int method) {
  if (ptr_object != NULL) {
    ptr_object->Calculate(sum, term, percent, method);
  }
}

double CallCreditTotalSum(s21::CreditCalc* ptr_object) {
  double res = 0;
  if (ptr_object != NULL) {
    res = ptr_object->GetTotalSum();
  }
  return res;
}

double CallCreditMonthlyPayment(s21::CreditCalc* ptr_object) {
  double res = 0;
  if (ptr_object != NULL) {
    res = ptr_object->GetMonthlyPayment();
  }
  return res;
}

double CallCreditOverpayment(s21::CreditCalc* ptr_object) {
  double res = 0;
  if (ptr_object != NULL) {
    res = ptr_object->GetCreditSum();
  }
  return res;
}

const char* CallCreditGetError(s21::CreditCalc* ptr_object) {
  return s21::ConvertCreditErrorString(ptr_object);
}
