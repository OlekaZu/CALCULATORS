#ifndef VIEW_CREDIT_H_
#define VIEW_CREDIT_H_

#include <QDialog>

#include "Controller/controller.h"

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(std::shared_ptr<Controller> sender,
                  QWidget *parent = nullptr);
  ~Credit();

 private:
  std::unique_ptr<Ui::Credit> ui_;
  std::shared_ptr<Controller> credit_sender_;

 private slots:
  void on_button_exit_clicked();
  void on_button_calc_clicked();
};

#endif  // VIEW_CREDIT_H_
