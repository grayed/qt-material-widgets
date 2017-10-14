#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class MainSheet : public QWidget {
  Q_OBJECT

 public:
  explicit MainSheet(QWidget* parent = 0);
  ~MainSheet();

 protected:
  bool eventFilter(QObject* watched, QEvent* evt);
};

#endif  // WIDGET_H
