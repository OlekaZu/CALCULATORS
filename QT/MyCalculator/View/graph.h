#ifndef VIEW_GRAPH_H_
#define VIEW_GRAPH_H_

#include <QDialog>
#include <QVector>
#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>

#include "Controller/controller.h"

namespace Ui {
class Graph;
}

class Graph : public QDialog {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

  void DrawChart(QString input, std::shared_ptr<Controller> sender);

 private:
  std::unique_ptr<Ui::Graph> ui_;
  std::shared_ptr<Controller> graph_sender_;
  std::unique_ptr<QChart> chart_view_;
  std::unique_ptr<QScatterSeries> dot_;
  std::unique_ptr<QLineSeries> series_;
  std::unique_ptr<QValueAxis> axe_x_;
  std::unique_ptr<QValueAxis> axe_y_;
  QString graph_input_;
  QVector<std::pair<double, double>> coordinates_;
  void FindCoordinates(std::string input, double x_min, double x_max,
                       double y_min, double y_max, double step);
  double FindStepValue(double min, double max);

 private slots:
  void on_pushButton_calculate_clicked();
};

#endif  // VIEW_GRAPH_H_
