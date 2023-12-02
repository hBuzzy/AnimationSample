#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void Animate();
    void LerpAnimation();

private:
    void DrawEasingPlot();

    qreal Lerp(qreal a, qreal b, qreal t);

private:
    const qreal kMaxTime = 1.0f;
    const qreal kAnimationDuration = 1500.0f;
    Ui::MainWindow *ui_;
    QTimer *timer_;
    qreal normalizedTtime_ = 0.0f;
};
#endif // MAINWINDOW_H
