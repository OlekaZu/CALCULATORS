#ifndef MODEL_CALCULATORMODEL_H
#define MODEL_CALCULATORMODEL_H
#include <cmath>
#include <locale>
#include <stack>
#include <string>
#include <vector>

class CalculatorModel {
 public:
  CalculatorModel() : input_(""), data_(0), error_("") {}
  CalculatorModel(const CalculatorModel&) = delete;
  CalculatorModel& operator=(const CalculatorModel&) = delete;
  ~CalculatorModel() {}
  void Calculate(const std::string& input, double x_argument);
  double GetData();
  std::string GetError();
  std::string GetInput();

 private:
  const std::string operators = "^*/+-()";
  const std::string operators_2 = "^*/+-";
  const std::string numbers = "0123456789.";
  const std::string letters = "acdgilmnoqrstxeP";

  enum PriorityOperators {
    kFunction = 1,
    kDegree = 2,
    kMulDivMod = 3,
    kAddSub = 4,  // ~ unary minus, p unary plus
    kBracketLeft = 5,
    kBracketRight = 6,
  };

  std::string input_;
  double data_;
  std::string error_;
  std::vector<std::string> RPN_string_;
  std::stack<std::pair<char, PriorityOperators>> save_operators_;
  std::stack<double> save_result_;

  void Clear();
  void CheckBeforeParsing();
  void Parsing();
  void CalculateResult(double x_argument);

  /* --- CheckBeforeParsing Helping Methods --- */
  // check if all symbols are right
  bool CheckCorrectSymbols(const char& symbol);
  // check if points(.) don't repeat
  // not point between letters, not point at the beginning
  bool CheckPointPosition(std::string input, size_t i);
  // check if digit.digit.digit
  bool CheckPointNumber(std::string input, size_t i);
  // check if operators_2 (^, *, /, +, -) doesn't repeat
  bool CheckRepeatOperators(std::string input, size_t i);
  // not good: digit( or x( or (*
  bool CheckLeftBracket(std::string input, size_t i);
  // not good: *) or )67 or )x
  bool CheckRightBracket(std::string input, size_t i, size_t left);
  // check for exponent format
  bool CheckExponentFormat(std::string input, size_t i);
  // check if amount of brackets is odd number
  bool CheckBracketsNumber(size_t right, size_t left);
  // check if letter or operator_2 are in the end
  bool CheckLastElement(std::string input);
  // check for first element of the stroke
  bool CheckFirstElement(std::string input);

  /* --- Parsing Helping Methods --- */
  void ParceSymbolOperator(std::string input, size_t i);
  void ParceNumber(std::string input, size_t* i);
  void ParceArgumentX(std::string input, size_t i);
  void ParceArgumentPi(std::string input, size_t i);
  void ParceAcosAsinAtan(std::string input, size_t* i);
  void ParceCos(std::string input, size_t* i);
  void ParceLnLog(std::string input, size_t* i);
  void ParceMod(std::string input, size_t* i);
  void ParceSinSqrt(std::string input, size_t* i);
  void ParceTan(std::string input, size_t* i);

  /* --- CalculateResult Helping Methods --- */
  void calc_pow();
  void calc_mult();
  void calc_div();
  void calc_add();
  void calc_sub();
  void calc_inversion();
  void calc_acos();
  void calc_asin();
  void calc_atan();
  void calc_cos();
  void calc_ln();
  void calc_log();
  void calc_mod();
  void calc_sin();
  void calc_sqrt();
  void calc_tan();
  double top_and_pop();
};

#endif  // MODEL_CALCULATORMODEL_H
