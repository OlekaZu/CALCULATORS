#ifndef VIEW_DEPOSIT_H_
#define VIEW_DEPOSIT_H_

#include <QDialog>

#include "Controller/controller.h"

namespace Ui {
class Deposit;
}

class Deposit : public QDialog {
  Q_OBJECT

 public:
  explicit Deposit(std::shared_ptr<Controller> sender,
                   QWidget *parent = nullptr);
  ~Deposit();

 private:
  std::unique_ptr<Ui::Deposit> ui_;
  std::shared_ptr<Controller> deposit_sender_;

 private slots:
  void on_button_exit_clicked();
  void on_button_calc_clicked();
};

#endif  // VIEW_DEPOSIT_H_
