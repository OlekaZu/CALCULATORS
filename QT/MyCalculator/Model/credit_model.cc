#include "credit_model.h"

/* --- Public Methods --- */
CreditModel::CreditModel()
    : total_sum_(0), monthly_payment_(0), credit_sum_(0) {}
CreditModel::~CreditModel() {}

void CreditModel::Calculate(double sum, double term, double percent,
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

double CreditModel::GetTotalSum() { return total_sum_; }
double CreditModel::GetMonthlyPayment() { return monthly_payment_; }
double CreditModel::GetCreditSum() { return credit_sum_; }
std::string CreditModel::GetError() { return error_; }
