#include "calculator_model.h"

/* --- Public Methods --- */
double CalculatorModel::GetData() { return data_; }

std::string CalculatorModel::GetError() { return error_; }

std::string CalculatorModel::GetInput() { return input_; }

void CalculatorModel::Calculate(const std::string& input, double x_argument) {
  Clear();
  input_ = input;
  if (!input_.empty()) {
    CheckBeforeParsing();
    if (error_.empty()) {
      Parsing();
      if (error_.empty()) {
        CalculateResult(x_argument);
        if (std::isnan(data_)) error_ = "Error";
      }
    }
  } else {
    error_ = "Empty line";
  }
}

/* --- Private Methods --- */
void CalculatorModel::Clear() {
  data_ = 0;
  error_ = "";
  if (RPN_string_.empty() == false) RPN_string_.clear();
  while (save_operators_.empty() == false) save_operators_.pop();
  while (save_result_.empty() == false) save_result_.pop();
}

void CalculatorModel::CheckBeforeParsing() {
  int amount_left_bracket = 0, amount_right_bracket = 0;
  for (size_t i = 0; i < input_.length(); ++i) {
    if (CheckCorrectSymbols(input_[i]) || CheckPointPosition(input_, i) ||
        CheckPointNumber(input_, i) || CheckRepeatOperators(input_, i) ||
        CheckExponentFormat(input_, i))
      error_ = "Incorrect input";
    if (input_[i] == '(') {
      amount_left_bracket += 1;
      if (CheckLeftBracket(input_, i)) error_ = "Incorrect input";
    }
    if (input_[i] == ')') {
      amount_right_bracket += 1;
      if (CheckRightBracket(input_, i, amount_left_bracket))
        error_ = "Incorrect input";
    }
  }
  if (CheckLastElement(input_) || CheckFirstElement(input_))
    error_ = "Incorrect input";

  if (amount_left_bracket > amount_right_bracket) {
    for (int i = (amount_left_bracket - amount_right_bracket); i != 0; --i) {
      input_ += ")";
      ++amount_right_bracket;
    }
  }
  if (CheckBracketsNumber(amount_right_bracket, amount_left_bracket))
    error_ = "Incorrect input";
}

bool CalculatorModel::CheckCorrectSymbols(const char& symbol) {
  return (operators.find(symbol) == std::string::npos &&
          numbers.find(symbol) == std::string::npos &&
          letters.find(symbol) == std::string::npos);
}

bool CalculatorModel::CheckPointPosition(std::string input, size_t i) {
  return (input[i] == 46 &&
          (!i || !isdigit(input[i - 1]) || !isdigit(input[i + 1])));
}

bool CalculatorModel::CheckPointNumber(std::string input, size_t i) {
  size_t count_point = 0;
  if (input[i] == '.') {
    while (i && operators.find(input[i - 1]) == std::string::npos &&
           input[i - 1] != 'd') {
      if (input[i - 1] == '.') ++count_point;
      --i;
    }
  }
  return (count_point > 0);
}

bool CalculatorModel::CheckRepeatOperators(std::string input, size_t i) {
  return (operators_2.find(input[i]) != std::string::npos &&
          operators_2.find(input[i + 1]) != std::string::npos);
}

bool CalculatorModel::CheckLeftBracket(std::string input, size_t i) {
  return ((operators_2.find(input[i + 1]) != std::string::npos &&
           input[i + 1] != '-' && input[i + 1] != '+') ||
          (i > 0 && (isdigit(input[i - 1]) || input[i - 1] == 'x' ||
                     input[i - 1] == 'P')));
}

bool CalculatorModel::CheckRightBracket(std::string input, size_t i,
                                        size_t left) {
  size_t last_index = input.size() - 1;
  return ((i && operators_2.find(input[i - 1]) != std::string::npos) ||
          (i != last_index && (isdigit(input[i + 1]) || input[i + 1] == 'x' ||
                               input[i - 1] == 'P')) ||
          (left == 0));
}

bool CalculatorModel::CheckExponentFormat(std::string input, size_t i) {
  return (input[i] == 'e' && ((input[i + 1] != '-' && input[i + 1] != '+') ||
                              (i && !isdigit(input[i - 1]))));
}

bool CalculatorModel::CheckBracketsNumber(size_t right, size_t left) {
  return (right != left);
}

bool CalculatorModel::CheckLastElement(std::string input) {
  const char& last_element = input.back();
  return (operators_2.find(last_element) != std::string::npos ||
          (letters.find(last_element) != std::string::npos &&
           last_element != 'x' && last_element != 'P'));
}

bool CalculatorModel::CheckFirstElement(std::string input) {
  const char& first_element = input.front();
  return (first_element == 'e' || first_element == '*' ||
          first_element == '/' || first_element == '^');
}

void CalculatorModel::Parsing() {
  for (size_t i = 0; i < input_.length(); ++i) {
    if (operators.find(input_[i]) != std::string::npos) {
      ParceSymbolOperator(input_, i);
    } else if (numbers.find(input_[i]) != std::string::npos) {
      // here exponent format too
      ParceNumber(input_, &i);
    } else if (input_[i] == 'x') {
      ParceArgumentX(input_, i);
      if (error_ == "Incorrect input") break;
    } else if (input_[i] == 'P') {
      ParceArgumentPi(input_, i);
      if (error_ == "Incorrect input") break;
    } else if (input_[i] == 'a') {
      ParceAcosAsinAtan(input_, &i);
      if (error_ == "Incorrect input") break;
    } else if (input_[i] == 'c') {
      ParceCos(input_, &i);
      if (error_ == "Incorrect input") break;
    } else if (input_[i] == 'l') {
      ParceLnLog(input_, &i);
      if (error_ == "Incorrect input") break;
    } else if (input_[i] == 'm') {
      ParceMod(input_, &i);
      if (error_ == "Incorrect input") break;
    } else if (input_[i] == 's') {
      ParceSinSqrt(input_, &i);
      if (error_ == "Incorrect input") break;
    } else if (input_[i] == 't') {
      ParceTan(input_, &i);
      if (error_ == "Incorrect input") break;
    } else {
      error_ = "Incorrect input";
      break;
    }
  }
  // if stack isn't empty after parsing cycle
  // and no error was appeared
  while (error_.empty() && save_operators_.size()) {
    char element = save_operators_.top().first;
    std::string char_in_str(1, element);
    RPN_string_.push_back(char_in_str);
    save_operators_.pop();
  }
}

void CalculatorModel::ParceSymbolOperator(std::string input, size_t i) {
  PriorityOperators priority_value;
  switch (input[i]) {
    case '^':
      priority_value = kDegree;
      break;
    case '*':
      priority_value = kMulDivMod;
      break;
    case '/':
      priority_value = kMulDivMod;
      break;
    case '+':
      priority_value = kAddSub;
      break;
    case '-':
      priority_value = kAddSub;
      break;
    case '(':
      priority_value = kBracketLeft;
      break;
    case ')':
      priority_value = kBracketRight;
      break;
  }
  // unary minus
  if (input[i] == '-' && (!i || input[i - 1] == '(' || input[i - 1] == 'd'))
    input[i] = '~';
  // unary plus
  if (input[i] == '+' && (!i || input[i - 1] == '(' || input[i - 1] == 'd'))
    input[i] = 'p';
  if (input[i] != 'p') {
    // left bracket is pushed to the stack at once
    if (save_operators_.size() && priority_value != kBracketLeft) {
      PriorityOperators last_operator_priority = save_operators_.top().second;
      if (priority_value == kBracketRight) {
        while (last_operator_priority != kBracketLeft) {
          char element = save_operators_.top().first;
          std::string char_in_str(1, element);
          save_operators_.pop();
          RPN_string_.push_back(char_in_str);
          last_operator_priority = save_operators_.top().second;
        }
        // delete unnecessary left bracket
        save_operators_.pop();
      } else if (priority_value >= last_operator_priority) {
        while (last_operator_priority <= priority_value &&
               save_operators_.size()) {
          // for this 2^3^4
          if (last_operator_priority == kDegree && priority_value == kDegree)
            break;
          char element = save_operators_.top().first;
          std::string char_in_str(1, element);
          save_operators_.pop();
          RPN_string_.push_back(char_in_str);
          if (save_operators_.size())
            last_operator_priority = save_operators_.top().second;
        }
      }
    }
    if (priority_value != kBracketRight)
      save_operators_.push(std::make_pair(input[i], priority_value));
  }
}

void CalculatorModel::ParceNumber(std::string input, size_t* i) {
  size_t last_index = input.size() - 1;
  std::string catch_number;
  while (
      (numbers.find(input[*i]) != std::string::npos ||
       (input[*i] == 'e' && (input[*i + 1] == '-' || input[*i + 1] == '+')) ||
       ((input[*i] == '-' || input[*i] == '+') && input[*i - 1] == 'e' &&
        *i)) &&
      *i <= last_index) {
    catch_number.push_back(input[*i]);
    *i += 1;
  }
  *i -= 1;
  if (operators.find(input[*i + 1]) != std::string::npos || *i == last_index ||
      input[*i + 1] == 'm')
    RPN_string_.push_back(catch_number);
  else
    error_ = "Incorrect input";
}

void CalculatorModel::ParceArgumentX(std::string input, size_t i) {
  std::string char_in_str(1, input[i]);
  if ((operators.find(input[i + 1]) == std::string::npos &&
       input[i + 1] != 'm' && i != input.size() - 1) ||
      (i > 0 && operators.find(input[i - 1]) == std::string::npos &&
       input[i - 1] != 'd'))
    error_ = "Incorrect input";
  else
    RPN_string_.push_back(char_in_str);
}

void CalculatorModel::ParceArgumentPi(std::string input, size_t i) {
  std::string char_in_str(1, input[i]);
  if ((operators.find(input[i + 1]) == std::string::npos &&
       input[i + 1] != 'm' && i != input.size() - 1) ||
      (i > 0 && operators.find(input[i - 1]) == std::string::npos &&
       input[i - 1] != 'd'))
    error_ = "Incorrect input";
  else
    RPN_string_.push_back(char_in_str);
}

void CalculatorModel::ParceAcosAsinAtan(std::string input, size_t* i) {
  std::string acos = "acos(";
  std::string asin = "asin(";
  std::string atan = "atan(";
  if (input.size() > 6 && input.compare(*i, 5, acos) == 0) {
    save_operators_.push(std::make_pair('a', kFunction));
    save_operators_.push(std::make_pair('(', kBracketLeft));
  } else if (input.size() > 6 && input.compare(*i, 5, asin) == 0) {
    save_operators_.push(std::make_pair('b', kFunction));
    save_operators_.push(std::make_pair('(', kBracketLeft));
  } else if (input.size() > 6 && input.compare(*i, 5, atan) == 0) {
    save_operators_.push(std::make_pair('d', kFunction));
    save_operators_.push(std::make_pair('(', kBracketLeft));
  } else {
    error_ = "Incorrect input";
  }
  *i += 4;
}

void CalculatorModel::ParceCos(std::string input, size_t* i) {
  std::string cos = "cos(";
  if (input.size() > 5 && input.compare(*i, 4, cos) == 0) {
    save_operators_.push(std::make_pair('c', kFunction));
    save_operators_.push(std::make_pair('(', kBracketLeft));
  } else {
    error_ = "Incorrect input";
  }
  *i += 3;
}

void CalculatorModel::ParceLnLog(std::string input, size_t* i) {
  std::string ln = "ln(";
  std::string log = "log(";
  if (input.size() > 4 && input.compare(*i, 3, ln) == 0) {
    save_operators_.push(std::make_pair('e', kFunction));
    save_operators_.push(std::make_pair('(', kBracketLeft));
    *i += 2;
  } else if (input.size() > 5 && input.compare(*i, 4, log) == 0) {
    save_operators_.push(std::make_pair('l', kFunction));
    save_operators_.push(std::make_pair('(', kBracketLeft));
    *i += 3;
  } else {
    error_ = "Incorrect input";
  }
}

void CalculatorModel::ParceMod(std::string input, size_t* i) {
  std::string mod = "mod";
  if (input.compare(*i, 3, mod) == 0 && *i &&
      (isdigit(input[*i - 1]) || input[*i - 1] == 'P' || input[*i - 1] == 'x' ||
       input[*i - 1] == ')') &&
      (isdigit(input[*i + 3]) || input[*i + 3] == 'P' || input[*i + 3] == 'x' ||
       input[*i + 3] == '(' ||
       (input[*i + 3] == '-' && isdigit(input[*i + 4]))))
    save_operators_.push(std::make_pair('m', kMulDivMod));
  else
    error_ = "Incorrect input";
  if ((input[*i + 3] == '-' && isdigit(input[*i + 4])))
    *i += 3;
  else
    *i += 2;
}

void CalculatorModel::ParceSinSqrt(std::string input, size_t* i) {
  std::string sin = "sin(";
  std::string sqrt = "sqrt(";
  if (input.size() > 5 && input.compare(*i, 4, sin) == 0) {
    save_operators_.push(std::make_pair('s', kFunction));
    save_operators_.push(std::make_pair('(', kBracketLeft));
    *i += 3;
  } else if (input.size() > 6 && input.compare(*i, 5, sqrt) == 0) {
    save_operators_.push(std::make_pair('q', kFunction));
    save_operators_.push(std::make_pair('(', kBracketLeft));
    *i += 4;
  } else {
    error_ = "Incorrect input";
  }
}

void CalculatorModel::ParceTan(std::string input, size_t* i) {
  std::string tan = "tan(";
  if (input.size() > 5 && input.compare(*i, 4, tan) == 0) {
    save_operators_.push(std::make_pair('t', kFunction));
    save_operators_.push(std::make_pair('(', kBracketLeft));
  } else {
    error_ = "Incorrect input";
  }
  *i += 3;
}

void CalculatorModel::CalculateResult(double x_argument) {
  for (auto it = RPN_string_.begin(); it != RPN_string_.end(); ++it) {
    if (*it == "^")
      calc_pow();
    else if (*it == "*")
      calc_mult();
    else if (*it == "/")
      calc_div();
    else if (*it == "+")
      calc_add();
    else if (*it == "-")
      calc_sub();
    else if (*it == "~")
      calc_inversion();
    else if (*it == "a")
      calc_acos();
    else if (*it == "b")
      calc_asin();
    else if (*it == "d")
      calc_atan();
    else if (*it == "c")
      calc_cos();
    else if (*it == "e")
      calc_ln();
    else if (*it == "l")
      calc_log();
    else if (*it == "m")
      calc_mod();
    else if (*it == "s")
      calc_sin();
    else if (*it == "q")
      calc_sqrt();
    else if (*it == "t")
      calc_tan();
    else if (*it == "x")
      save_result_.push(x_argument);
    else if (*it == "P")
      save_result_.push(M_PI);
    else
      save_result_.push(std::stod(*it));
  }
  if (save_result_.size()) data_ = top_and_pop();
}

void CalculatorModel::calc_pow() {
  double num_2 = top_and_pop();
  double num_1 = top_and_pop();
  double result = pow(num_1, num_2);
  save_result_.push(result);
}

void CalculatorModel::calc_mult() {
  double num_2 = top_and_pop();
  double num_1 = top_and_pop();
  double result = num_1 * num_2;
  save_result_.push(result);
}

void CalculatorModel::calc_div() {
  double num_2 = top_and_pop();
  double num_1 = top_and_pop();
  double result = num_1 / num_2;
  save_result_.push(result);
}

void CalculatorModel::calc_add() {
  double num_2 = top_and_pop();
  double num_1 = top_and_pop();
  double result = num_1 + num_2;
  save_result_.push(result);
}

void CalculatorModel::calc_sub() {
  double num_2 = top_and_pop();
  double num_1 = top_and_pop();
  double result = num_1 - num_2;
  save_result_.push(result);
}

void CalculatorModel::calc_inversion() {
  double num_1 = top_and_pop();
  double result = num_1 * (-1);
  save_result_.push(result);
}

void CalculatorModel::calc_acos() {
  double num_1 = top_and_pop();
  double result = acos(num_1);
  save_result_.push(result);
}

void CalculatorModel::calc_asin() {
  double num_1 = top_and_pop();
  double result = asin(num_1);
  save_result_.push(result);
}

void CalculatorModel::calc_atan() {
  double num_1 = top_and_pop();
  double result = atan(num_1);
  save_result_.push(result);
}

void CalculatorModel::calc_cos() {
  double num_1 = top_and_pop();
  double result = cos(num_1);
  save_result_.push(result);
}

void CalculatorModel::calc_ln() {
  double num_1 = top_and_pop();
  double result = log(num_1);
  save_result_.push(result);
}

void CalculatorModel::calc_log() {
  double num_1 = top_and_pop();
  double result = log10(num_1);
  save_result_.push(result);
}

void CalculatorModel::calc_mod() {
  double num_2 = top_and_pop();
  double num_1 = top_and_pop();
  double result = fmod(num_1, num_2);
  save_result_.push(result);
}

void CalculatorModel::calc_sin() {
  double num_1 = top_and_pop();
  double result = sin(num_1);
  save_result_.push(result);
}

void CalculatorModel::calc_sqrt() {
  double num_1 = top_and_pop();
  double result = sqrt(num_1);
  save_result_.push(result);
}

void CalculatorModel::calc_tan() {
  double num_1 = top_and_pop();
  if (num_1 > (M_PI / 2) && num_1 < (-M_PI / 2)) {
    num_1 = fmod(num_1, M_PI);
  }
  if (fabs(num_1) == M_PI / 2) error_ = "Error";
  double result = tan(num_1);
  save_result_.push(result);
}

double CalculatorModel::top_and_pop() {
  if (save_result_.empty())
    throw std::out_of_range("Stack is empty, nothing can be top");
  double result = save_result_.top();
  save_result_.pop();
  return result;
}
