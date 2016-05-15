#ifndef FLATBUTTON_INTERNAL_H
#define FLATBUTTON_INTERNAL_H

#include <QStateMachine>
#include <QColor>

class FlatButton;

class FlatButtonDelegate : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal backgroundOpacity WRITE setBackgroundOpacity READ backgroundOpacity)
    Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)

public:
    FlatButtonDelegate(FlatButton *parent);
    ~FlatButtonDelegate();

    void setBackgroundOpacity(qreal opacity);
    qreal backgroundOpacity() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

private:
    Q_DISABLE_COPY(FlatButtonDelegate)

    FlatButton *const button;
    qreal  _backgroundOpacity;
    QColor _backgroundColor;
};

#endif // FLATBUTTON_INTERNAL_H