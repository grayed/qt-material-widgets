#include "mainsheet.h"
#include <QtWidgets>
#include "qdebug.h"
#include "qevent.h"

#include "qtmaterialappbar.h"            // check
#include "qtmaterialautocomplete.h"      // check
#include "qtmaterialavatar.h"            // check
#include "qtmaterialbadge.h"             // check
#include "qtmaterialcheckbox.h"          // check
#include "qtmaterialcircularprogress.h"  // check
#include "qtmaterialdialog.h"            // check
#include "qtmaterialdrawer.h"            // check
#include "qtmaterialfab.h"               // check
#include "qtmaterialflatbutton.h"        // check
#include "qtmaterialiconbutton.h"        // check
#include "qtmaterialpaper.h"
#include "qtmaterialprogress.h"      // check
#include "qtmaterialradiobutton.h"   // check
#include "qtmaterialraisedbutton.h"  // check
#include "qtmaterialscrollbar.h"     // check
#include "qtmaterialslider.h"        // check
#include "qtmaterialsnackbar.h"      // check
#include "qtmaterialtable.h"
#include "qtmaterialtabs.h"       // check
#include "qtmaterialtextfield.h"  // check
#include "qtmaterialtoggle.h"     // check

MainSheet::MainSheet(QWidget* parent) : QWidget(parent) {
  // this->setAttribute(Qt::WA_TranslucentBackground);
  // setStyleSheet("QWidget { background: white; }");
  this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint |
                       Qt::WindowMinimizeButtonHint);
  installEventFilter(this);
  resize(800, 600);

  // appbar
  auto* appbar = new QtMaterialAppBar(this);
  auto* label  = new QLabel("QtMaterial");
  label->setFont(QFont("Roboto", 18, QFont::Normal));
  auto* button = new QtMaterialIconButton(
      QtMaterialTheme::icon("navigation", "menu"), appbar);
  button->setColor(Qt::white);
  button->setFixedWidth(42);
  button->setIconSize(QSize(24, 24));

  auto* ibutton_close = new QtMaterialIconButton(
      QtMaterialTheme::icon("navigation", "menu"), appbar);
  auto* tabs = new QtMaterialTabs(appbar);
  tabs->addTab("Google");
  tabs->addTab("QtMaterial");

  auto* avtar =
      new QtMaterialAvatar(QImage(":/images/assets/sikh.jpg"), appbar);
  QVBoxLayout* alayout = new QVBoxLayout;
  alayout->setContentsMargins(0, 0, 0, 0);
  alayout->addWidget(avtar);
  alayout->setAlignment(avtar, Qt::AlignCenter);
  auto* badge = new QtMaterialBadge(avtar);
  badge->setRelativePosition(10, 10);
  badge->setText("3");

  appbar->appBarLayout()->addWidget(button);
  appbar->appBarLayout()->addWidget(label);
  appbar->appBarLayout()->addStretch(3);
  appbar->appBarLayout()->addWidget(tabs);
  appbar->appBarLayout()->addStretch(5);
  appbar->appBarLayout()->addWidget(ibutton_close);
  appbar->appBarLayout()->addStretch(1);
  appbar->appBarLayout()->addLayout(alayout);

  // snakbar
  auto* snackbar = new QtMaterialSnackbar(this);
  QObject::connect(avtar, &QtMaterialAvatar::clicked, [=](bool) {
    snackbar->addMessage(QString("You have 3 comming calls."));
  });

  // drawer
  auto* drawer = new QtMaterialDrawer(this);
  drawer->setClickOutsideToClose(true);
  drawer->setOverlayMode(true);
  auto* drawerLayout = new QVBoxLayout;
  drawer->setDrawerLayout(drawerLayout);
  QVector<QString> labels = {"Motion", "Style", "Layout", "Components",
      "Patterns", "Growth & communications", "Usability", "Platforms",
      "Resources"};
  QVector<QString>::iterator it;
  for (it = labels.begin(); it != labels.end(); ++it) {
    QLabel* label = new QLabel(*it);
    label->setMinimumHeight(30);
    label->setFont(QFont("Roboto", 10, QFont::Medium));
    drawerLayout->addWidget(label);
  }
  drawerLayout->addStretch(3);
  drawer->setContentsMargins(10, 0, 0, 0);
  QObject::connect(button, &QtMaterialIconButton::clicked,
      [=](bool) { drawer->openDrawer(); });

  // main sheet
  auto* center     = new QStackedWidget(this);
  auto* sheet_area = new QScrollArea(center);
  sheet_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  sheet_area->setBackgroundRole(QPalette::Window);
  sheet_area->setFrameShadow(QFrame::Plain);
  sheet_area->setFrameShape(QFrame::NoFrame);
  sheet_area->setWidgetResizable(true);
  auto* sheet_a = new QWidget(sheet_area);
  sheet_area->setWidget(sheet_a);
  auto* layout_a = new QVBoxLayout();
  sheet_a->setLayout(layout_a);
  layout_a->setAlignment(Qt::AlignBottom);
  layout_a->setSizeConstraint(QLayout::SetMinAndMaxSize);
  layout_a->setSpacing(30);
  auto* sheet_b  = new QWidget(center);
  auto* layout_b = new QVBoxLayout();
  sheet_b->setLayout(layout_b);
  center->addWidget(sheet_area);
  center->addWidget(sheet_b);
  QObject::connect(tabs, &QtMaterialTabs::currentChanged, [=](int index) {
    if (index > 1) { return; }
    center->setCurrentIndex(index);
  });

  // progress
  auto* probar = new QtMaterialProgress(sheet_a);
  probar->setValue(20);
  layout_a->addWidget(probar);
  layout_a->addSpacing(80);

  // toggle
  auto* toggle = new QtMaterialToggle(sheet_b);
  toggle->setText("This is a toggle");
  layout_b->addWidget(toggle);
  layout_b->addSpacing(80);

  // slider
  auto* slider = new QtMaterialSlider(sheet_a);
  layout_a->addWidget(slider);
  layout_a->addSpacing(80);

  // radio button
  auto* radioButton1 = new QtMaterialRadioButton(sheet_a);
  auto* radioButton2 = new QtMaterialRadioButton(sheet_a);
  auto* radioButton3 = new QtMaterialRadioButton(sheet_a);
  auto* radioButton4 = new QtMaterialRadioButton(sheet_a);
  auto* radioButton5 = new QtMaterialRadioButton(sheet_a);
  auto* radioButton6 = new QtMaterialRadioButton(sheet_a);
  radioButton1->setText("Coffee");
  radioButton2->setText("Tea");
  radioButton3->setText("Algebraic Topology");
  radioButton4->setText("Coffee");
  radioButton5->setText("Tea");
  radioButton6->setText("Algebraic Topology");
  layout_a->addWidget(radioButton1);
  layout_a->addWidget(radioButton2);
  layout_a->addWidget(radioButton3);
  layout_a->addWidget(radioButton4);
  layout_a->addWidget(radioButton5);
  layout_a->addWidget(radioButton6);
  layout_a->addSpacing(80);

  // QtMaterialCircularProgress
  auto* circular_prog = new QtMaterialCircularProgress(sheet_a);
  circular_prog->setValue(20);
  layout_a->addWidget(circular_prog);
  layout_a->addSpacing(80);

  // auto complete
  auto* autocomplete = new QtMaterialAutoComplete(sheet_a);
  autocomplete->setDataSource({ "Alabama", "Alaska", "American Samoa", "Arizona",
	  "Arkansas", "California", "Colorado", "Connecticut", "Delaware",
	  "District of Columbia", "Florida", "Georgia", "Guam", "Hawaii", "Idaho",
	  "Illinois", "Indiana", "Iowa", "Kansas", "Kentucky", "Louisiana", "Maine",
	  "Maryland", "Massachusetts", "Michigan", "Minnesota", "Mississippi",
	  "Missouri", "Montana", "Nebraska", "Nevada", "New Hampshire",
	  "New Jersey", "New Mexico", "New York", "North Carolina", "North Dakota",
	  "Northern Marianas Islands", "Ohio", "Oklahoma", "Oregon", "Pennsylvania",
	  "Puerto Rico", "Rhode Island", "South Carolina", "South Dakota",
	  "Tennessee", "Texas", "Utah", "Vermont", "Virginia", "Virgin Islands",
	  "Washington", "West Virginia", "Wisconsin", "Wyoming" });
  layout_a->addWidget(autocomplete);

  // QtMaterialCheckBox
  auto* check_box = new QtMaterialCheckBox(sheet_a);
  check_box->setText("hello meterial");
  layout_a->addWidget(check_box);
  layout_a->addSpacing(80);

  // QtMaterialFlatButton
  auto* flat_button = new QtMaterialFlatButton("Flat Button", sheet_a);
  layout_a->addWidget(flat_button);

  // scroll bar
  auto* scrollbar = new QtMaterialScrollBar();
  scrollbar->setHideOnMouseOut(false);
  sheet_area->setVerticalScrollBar(scrollbar);

  // center final
  layout_b->addStretch();
  // layout_a->addStretch();

  // final layout
  auto* layout = new QVBoxLayout();
  layout->addWidget(appbar);
  layout->addWidget(center);
  layout->setMargin(0);
  setLayout(layout);

  // floating action button
  auto* fab = new QtMaterialFloatingActionButton(
      QtMaterialTheme::icon("toggle", "star"), this);

  // dialog
  auto* dialog             = new QtMaterialDialog(this);
  auto* dialogLayout       = new QVBoxLayout;
  auto* dialogWidget       = new QWidget();
  auto* dialogWidgetLayout = new QVBoxLayout;
  auto* rbutton            = new QtMaterialRaisedButton("Close", dialogWidget);
  auto* label2             = new QLabel("Tell As About you");
  label2->setFont(QFont("Roboto", 18, QFont::Normal));
  auto* textfield_name    = new QtMaterialTextField(dialogWidget);
  auto* textfield_address = new QtMaterialTextField(dialogWidget);
  textfield_name->setLabel("What's your name ?");
  textfield_address->setLabel("Where are you living ?");
  rbutton->setUseThemeColors(true);

  dialogWidgetLayout->addWidget(label2);
  dialogWidgetLayout->addSpacing(30);
  dialogWidgetLayout->addWidget(textfield_name);
  dialogWidgetLayout->addWidget(textfield_address);
  dialogWidgetLayout->addSpacing(30);
  dialogWidgetLayout->addWidget(rbutton);
  dialogWidget->setLayout(dialogWidgetLayout);
  dialogLayout->addWidget(dialogWidget);
  dialog->setWindowLayout(dialogLayout);

  dialogWidgetLayout->setAlignment(rbutton, Qt::AlignBottom | Qt::AlignRight);

  connect(rbutton, SIGNAL(pressed()), dialog, SLOT(hideDialog()));
  QObject::connect(fab, &QtMaterialFloatingActionButton::clicked,
      [=](bool) { dialog->showDialog(); });
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
