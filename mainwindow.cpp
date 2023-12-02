#include "mainwindow.h"
#include "easingfunctions.h"
#include "ui_mainwindow.h"

#include <QAnimationGroup>
#include <QLabel>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QTimer>

#include <QtCharts/QtCharts>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow) {

    ui_->setupUi(this);

    timer_ = new QTimer;
    timer_->setInterval(1);

    connect(ui_->startAnimationButton, &QPushButton::clicked, this, &MainWindow::Animate);

    connect(timer_, &QTimer::timeout, this, &MainWindow::LerpAnimation);

    DrawEasingPlot();
}

MainWindow::~MainWindow() {
    delete ui_;
}

void MainWindow::Animate() {
    //Создаем анимацию для свойста geometry
    QPropertyAnimation *moveAnimation = new QPropertyAnimation(ui_->animatedButton, "geometry");

    QSize buttonSize = ui_->animatedButton->size();
    int pathWidth = ui_->scene->rect().width() - buttonSize.width();

    QPoint startPosition(0, ui_->animatedButton->pos().y());
    QPoint endPosition(pathWidth, startPosition.y());

    //Указываем начальное значение, если не указано, берется текущее значение свойство
    moveAnimation->setStartValue(QRect(startPosition, buttonSize));
    //Устанавливаем конечное значение анимации
    moveAnimation->setEndValue(QRect(endPosition, buttonSize));
    //Устанавливаем время анимации в мс
    moveAnimation->setDuration(2000);
    //Устанавливаем функции плавности
    moveAnimation->setEasingCurve(QEasingCurve::InBounce);
    //moveAnimation->start();

    //Создаем анимацию для собственного свойства Q_PROPERTY color
    QPropertyAnimation *colorAnimation = new QPropertyAnimation(ui_->animatedButton, "color");

    colorAnimation->setEndValue(QColor(50, 100, 50));
    colorAnimation->setDuration(2000);
    colorAnimation->setEasingCurve(QEasingCurve::OutElastic);
    //colorAnimation->start();

    //Паралллельное выполнение анимаций в группе
    QAnimationGroup *group = new QParallelAnimationGroup;

    //Очередное выполнение анимаций в группе (по мере того, как они были добавлены)
    //QAnimationGroup *group = new QSequentialAnimationGroup;

    group->addAnimation(moveAnimation);
    group->addAnimation(colorAnimation);

    //Устанавливаем кол-во повторений, где -1 - бесконечно.
    group->setLoopCount(-1);
    //Запускаем все анимации в группе
    group->start();

    //Запускаем анимацию с помощью таймера
    //timer_->start();
}

void MainWindow::LerpAnimation() {
    int pathWidth = ui_->scene->rect().width() - ui_->animatedButton->width();

    //std::Lerp() c++ 20+ Если ваша версия с++ ниже, используйте свой метод Lerp
    qreal lerpedX = std::lerp(0, pathWidth, EasingFunctions::CountSmoothSquared(normalizedTtime_));
    /*qreal lerpedX = Lerp(0, uwidgetWidth - buttonWidth,
                         LinearEasing(time));*/

    QPoint nextPoint(lerpedX, ui_->animatedButton->pos().y());

    ui_->animatedButton->move(nextPoint);

    if (normalizedTtime_ > kMaxTime) {
        timer_->stop();
        normalizedTtime_ = 0;
        return;
    }

    normalizedTtime_ += timer_->interval() / kAnimationDuration;
}

/*Рисуем график используемой функции плавности*/
void MainWindow::DrawEasingPlot() {
    //Создаем набор данных
    QSplineSeries *series = new QSplineSeries();

    qreal threshold = 1.0f;
    qreal step = 0.05f;
    qreal i = 0.0f;

    //Заполняем набор данных
    while (i < threshold) {
        *series << QPointF(i, EasingFunctions::CountSmoothSquared(i));
        i += step;
    }

    //Создаем модель графика
    QChart *chart = new QChart();
    //Добавляем данные в модель
    chart->addSeries(series);
    //Скрываем легенду
    chart->legend()->hide();

    //Создаем представление и добавляем в него модель
    QChartView *chartView = new QChartView(chart);
    //Включаем сглаживаение
    chartView->setRenderHint(QPainter::Antialiasing);

    // Настройка осей графика
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("x");
    axisX->setTickCount(1);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("y");
    axisY->setTickCount(1);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    //Добавляем график на виджет
    ui_->verticalLayout_2->addWidget(chartView);
}

//"Своя" реализация std::Lerp, если ваша версия с++ ниже 20-ой
qreal MainWindow::Lerp(qreal a, qreal b, qreal t) {
    return a + t * (b - a);
}
