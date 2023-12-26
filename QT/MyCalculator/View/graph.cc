#include "graph.h"

#include <QLocale>

#include "qvalidator.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent)
    : QDialog(parent),
      ui_(std::make_unique<Ui::Graph>()),
      chart_view_(std::make_unique<QChart>()),
      dot_(std::make_unique<QScatterSeries>()),
      series_(std::make_unique<QLineSeries>()),
      axe_x_(std::make_unique<QValueAxis>()),
      axe_y_(std::make_unique<QValueAxis>()),
      graph_input_("") {
  ui_->setupUi(this);
  ui_->xmin->setText("-10");
  ui_->xmax->setText("10");
  ui_->ymin->setText("-10");
  ui_->ymax->setText("10");
  QIntValidator *format = new QIntValidator(-1000000, 1000000, this);
  format->setLocale(QLocale::c());
  ui_->xmin->setValidator(format);
  ui_->xmax->setValidator(format);
  ui_->ymin->setValidator(format);
  ui_->ymax->setValidator(format);
}

Graph::~Graph() {}

void Graph::DrawChart(QString input, std::shared_ptr<Controller> sender) {
  graph_input_ = input;
  graph_sender_ = sender;
  ui_->label->setText("y=");
  ui_->label->setText(ui_->label->text() + input);

  double x_min = (ui_->xmin->text()).toDouble();
  double x_max = (ui_->xmax->text()).toDouble();
  double y_min = (ui_->ymin->text()).toDouble();
  double y_max = (ui_->ymax->text()).toDouble();
  double step = FindStepValue(x_min, x_max);
  std::string input_string = input.toStdString();

  FindCoordinates(input_string, x_min, x_max, y_min, y_max, step);

  // Add coordinates to QChart object
  chart_view_->addSeries(series_.get());
  chart_view_->addSeries(dot_.get());
  chart_view_->legend()->hide();
  chart_view_->setTitle(input);
  dot_->setMarkerShape(QScatterSeries::MarkerShapeCircle);
  dot_->setMarkerSize(2.0);
  dot_->setBorderColor(455);
  dot_->setColor(455);
  series_->setOpacity(0.5);
  series_->setColor(QColorConstants::LightGray);

  // Adjusting the Axes of the Graph
  axe_x_->setTitleText("x");
  axe_x_->setLabelFormat("%.2f");
  axe_x_->setMax(x_max);
  axe_x_->setMin(x_min);
  axe_x_->setTickAnchor(0);
  QPen line(22);
  axe_x_->setLinePen(line);
  chart_view_->addAxis(axe_x_.get(), Qt::AlignBottom);
  dot_->attachAxis(axe_x_.get());
  series_->attachAxis(axe_x_.get());

  axe_y_->setTitleText("y");
  axe_y_->setLabelFormat("%.2f");
  axe_y_->setTickAnchor(0);
  axe_y_->setMax(y_max);
  axe_y_->setMin(y_min);
  axe_y_->setLinePen(line);
  chart_view_->addAxis(axe_y_.get(), Qt::AlignLeft);
  dot_->attachAxis(axe_y_.get());
  series_->attachAxis(axe_y_.get());

  // Show the graph in QChartView widget
  ui_->graphicsView->setChart(chart_view_.get());
}

void Graph::FindCoordinates(std::string input, double x_min, double x_max,
                            double y_min, double y_max, double step) {
  double argument = x_min;
  size_t flag_infinity = 0;
  while (argument <= x_max) {
    std::pair<double, std::string> result =
        graph_sender_->PushOnButtonEqual(input, argument);
    if (result.second.empty()) {
      if (flag_infinity && result.first < 0 &&
          (input.find("ln") != std::string::npos ||
           input.find("log") != std::string::npos))
        coordinates_.push_back(std::make_pair(argument, y_min));
      if (flag_infinity && result.first > 0 &&
          (input.find("ln") != std::string::npos ||
           input.find("log") != std::string::npos))
        coordinates_.push_back(std::make_pair(argument, y_max));
      coordinates_.push_back(std::make_pair(argument, result.first));
      flag_infinity = 0;
    } else {
      flag_infinity = 1;
    }
    argument = argument + step;
  }

  while (coordinates_.size()) {
    dot_->append(coordinates_.back().first, coordinates_.back().second);
    series_->append(coordinates_.back().first, coordinates_.back().second);
    coordinates_.pop_back();
  }
}

double Graph::FindStepValue(double min, double max) {
  double step = 0.0;
  double lag = max - min;
  step = lag / 1000;
  return step;
}

void Graph::on_pushButton_calculate_clicked() {
  dot_ = std::make_unique<QScatterSeries>();
  series_ = std::make_unique<QLineSeries>();
  axe_x_ = std::make_unique<QValueAxis>();
  axe_y_ = std::make_unique<QValueAxis>();
  DrawChart(graph_input_, graph_sender_);
}
