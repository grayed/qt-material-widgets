#include "mainsheet.h"
#include "qdebug.h"
#include "qevent.h"
#include <QtWidgets>

#include "qtmaterialappbar.h" // check
#include "qtmaterialautocomplete.h"
#include "qtmaterialavatar.h"
#include "qtmaterialbadge.h"
#include "qtmaterialcheckbox.h"
#include "qtmaterialcircularprogress.h"
#include "qtmaterialdialog.h"
#include "qtmaterialdrawer.h" // check
#include "qtmaterialfab.h" // check
#include "qtmaterialflatbutton.h"
#include "qtmaterialiconbutton.h"
#include "qtmaterialpaper.h"
#include "qtmaterialprogress.h"
#include "qtmaterialradiobutton.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialscrollbar.h"
#include "qtmaterialslider.h"
#include "qtmaterialsnackbar.h"
#include "qtmaterialtable.h"
#include "qtmaterialtabs.h"
#include "qtmaterialtextfield.h"
#include "qtmaterialtoggle.h"

MainSheet::MainSheet(QWidget* parent) : QWidget(parent) {
  //this->setAttribute(Qt::WA_TranslucentBackground);
 // setStyleSheet("QWidget { background: white; }");
  this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint |
                       Qt::WindowMinimizeButtonHint);
  installEventFilter(this);
  resize(800, 600);

  // appbar
  auto* appbar = new QtMaterialAppBar(this);
  auto *label = new QLabel("Inbox");
  label->setFont(QFont("Roboto", 18, QFont::Normal));
  auto *button = new QtMaterialIconButton(QtMaterialTheme::icon("navigation", "menu"), appbar);
  button->setColor(Qt::white);
  button->setFixedWidth(42);
  button->setIconSize(QSize(24, 24));
  appbar->appBarLayout()->addWidget(button);
  appbar->appBarLayout()->addWidget(label);
  appbar->appBarLayout()->addStretch(1);

  // drawer
  auto* drawer = new QtMaterialDrawer(this);
  drawer->setClickOutsideToClose(true);
  drawer->setOverlayMode(true);
  auto *drawerLayout = new QVBoxLayout;
  drawer->setDrawerLayout(drawerLayout);
  QVector<QString> labels = { "Motion", "Style", "Layout", "Components", "Patterns", "Growth & communications", "Usability", "Platforms", "Resources" };
  QVector<QString>::iterator it;
  for (it = labels.begin(); it != labels.end(); ++it) {
	  QLabel *label = new QLabel(*it);
	  label->setMinimumHeight(30);
	  label->setFont(QFont("Roboto", 10, QFont::Medium));
	  drawerLayout->addWidget(label);
  }
  drawerLayout->addStretch(3);
  drawer->setContentsMargins(10, 0, 0, 0);

  QObject::connect(button, &QtMaterialIconButton::clicked, [=](bool) {
	  drawer->openDrawer();
  });

  // floating action button
  auto* fab = new QtMaterialFloatingActionButton(QtMaterialTheme::icon("toggle", "star"),this);

  // final layout
  auto* layout = new QVBoxLayout();
  layout->addWidget(appbar);
  //layout->addWidget(tabs);
  layout->addStretch();
  layout->setMargin(0);
  setLayout(layout);
}

MainSheet::~MainSheet() {}

bool MainSheet::eventFilter(QObject* watched, QEvent* evt) {
  static QPoint mousePoint;
  static bool   mousePressed = false;

  QMouseEvent* event = static_cast<QMouseEvent*>(evt);
  if (event->type() == QEvent::MouseButtonPress) {
    if (event->button() == Qt::LeftButton) {
      mousePressed = true;
      mousePoint   = event->globalPos() - this->pos();
      return true;
    } else {
      exit(0);
    }
  } else if (event->type() == QEvent::MouseButtonRelease) {
    mousePressed = false;
    return true;
  } else if (event->type() == QEvent::MouseMove) {
    if (mousePressed && (event->buttons() && Qt::LeftButton)) {
      this->move(event->globalPos() - mousePoint);
      return true;
    }
  }

  return QWidget::eventFilter(watched, event);
}
