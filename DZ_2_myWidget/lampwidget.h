#ifndef LAMPWIDGET_H
#define LAMPWIDGET_H

#include <QObject>
#include <QWidget>

class LampWidget : public QWidget
{
    Q_OBJECT
public:

    LampWidget(QWidget *parent = nullptr, QColor on = Qt::green, QColor off = Qt::darkGray, int m_radius = 40);

public slots:
    void setStatus();

signals:
    void getStatus(int);


    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;

    // QWidget interface
public:
    virtual QSize sizeHint() const override;
    void setColorStatus (QColor on, QColor off);
    int getStatusLamp();
    void setStatusLamp(int);
    void setStatusClick();
    void setSize(int);


private:
    int status = 0;
    int xR;
    int yR;
    QColor colorDefaultOn;
    QColor colorDefaultOff;
    int radius;


    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
};

#endif // LAMPWIDGET_H
