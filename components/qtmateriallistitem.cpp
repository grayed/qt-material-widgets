#include "qtmateriallistitem.h"
#include "qtmateriallistitem_p.h"
#include <QPainter>
#include "lib/qtmaterialstyle.h"

/*!
 *  \class QtMaterialListItemPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialListItemPrivate::QtMaterialListItemPrivate(QtMaterialListItem *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
QtMaterialListItemPrivate::~QtMaterialListItemPrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialListItemPrivate::init()
{
    Q_Q(QtMaterialListItem);

    size           = 48;
    // type           = Material::LetterListItem;
    useThemeColors = true;

    QFont font(q->font());
    font.setPointSizeF(16);
    q->setFont(font);

    QSizePolicy policy(QSizePolicy::MinimumExpanding,
                       QSizePolicy::MinimumExpanding);
    q->setSizePolicy(policy);
}

/*!
 *  \class QtMaterialListItem
 */

QtMaterialListItem::QtMaterialListItem(QWidget *parent)
    : QWidget(parent),
      d_ptr(new QtMaterialListItemPrivate(this))
{
    d_func()->init();
}

QtMaterialListItem::~QtMaterialListItem()
{
}

void QtMaterialListItem::setUseThemeColors(bool value)
{
    Q_D(QtMaterialListItem);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    update();
}

bool QtMaterialListItem::useThemeColors() const
{
    Q_D(const QtMaterialListItem);

    return d->useThemeColors;
}

void QtMaterialListItem::setTextColor(const QColor &color)
{
    Q_D(QtMaterialListItem);

    d->textColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialListItem::textColor() const
{
    Q_D(const QtMaterialListItem);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("canvas");
    } else {
        return d->textColor;
    }
}

void QtMaterialListItem::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialListItem);

    d->backgroundColor = color;
    
    MATERIAL_DISABLE_THEME_COLORS
    update();
}

QColor QtMaterialListItem::backgroundColor() const
{
    Q_D(const QtMaterialListItem);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    } else {
        return d->backgroundColor;
    }
}

/*!
 *  \reimp
 */
QSize QtMaterialListItem::sizeHint() const
{
    Q_D(const QtMaterialListItem);

    return QSize(d->size+2, d->size);
}

void QtMaterialListItem::setSize(int size)
{
    Q_D(QtMaterialListItem);

    d->size = size;

    if (!d->image.isNull()) {
        d->pixmap = QPixmap::fromImage(d->image.scaled(d->size, d->size,
                                                       Qt::IgnoreAspectRatio,
                                                       Qt::SmoothTransformation));
    }

    QFont f(font());
    f.setPointSizeF(size*16/40);
    setFont(f);

    update();
}

int QtMaterialListItem::size() const
{
    Q_D(const QtMaterialListItem);

    return d->size;
}

void QtMaterialListItem::setLetter(const QChar &letter)
{
    Q_D(QtMaterialListItem);

    d->letter = letter;
//    d->type = Material::LetterListItem;
    update();
}

void QtMaterialListItem::setImage(const QImage &image)
{
    Q_D(QtMaterialListItem);

    d->image = image;
//    d->type = Material::ImageListItem;

    d->pixmap = QPixmap::fromImage(image.scaled(d->size, d->size,
                                                Qt::IgnoreAspectRatio,
                                                Qt::SmoothTransformation));
    update();
}

void QtMaterialListItem::setIcon(const QIcon &icon)
{
    Q_D(QtMaterialListItem);

    d->icon = icon;
//    d->type = Material::IconListItem;
    update();
}

Material::ListItemType QtMaterialListItem::type() const
{
    Q_D(const QtMaterialListItem);

    return d->type;
}

/*!
 *  \reimp
 */
void QtMaterialListItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    Q_D(QtMaterialListItem);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect r = rect();
    const qreal hs = d->size/2;

    painter.fillRect( rect(), QColor(0,0,255));

    painter.setPen(textColor());
    painter.setBrush(Qt::NoBrush);
    painter.drawText(r, Qt::AlignLeft + Qt::AlignVCenter, QString(d->letter));
/*
    if (!isEnabled())
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QtMaterialStyle::instance().themeColor("disabled"));
        painter.setPen(Qt::NoPen);
        painter.setBrush(brush);
        painter.drawEllipse(QRectF((width()-d->size)/2, (height()-d->size)/2,
                                   d->size, d->size));
        return;
    }
    */
/*
    if (Material::ImageListItem != d->type)
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(backgroundColor());
        painter.setPen(Qt::NoPen);
        painter.setBrush(brush);
        painter.drawEllipse(QRectF((width()-d->size)/2, (height()-d->size)/2,
                                   d->size, d->size));
    }

    switch (d->type)
    {
    case Material::ImageListItem:
    {
        QPainterPath path;
        path.addEllipse(width()/2-hs, height()/2-hs, d->size, d->size);
        painter.setClipPath(path);

        painter.drawPixmap(QRect(width()/2-hs, height()/2-hs, d->size, d->size),
                           d->pixmap);
        break;
    }
    case Material::IconListItem:
    {
        QRect iconGeometry((width()-hs)/2, (height()-hs)/2, hs, hs);
        QPixmap pixmap = d->icon.pixmap(hs, hs);
        QPainter icon(&pixmap);
        icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
        icon.fillRect(pixmap.rect(), textColor());
        painter.drawPixmap(iconGeometry, pixmap);
        break;
    }
    case Material::LetterListItem:
    {
        painter.setPen(textColor());
        painter.setBrush(Qt::NoBrush);
        painter.drawText(r, Qt::AlignCenter, QString(d->letter));
        break;
    }
    default:
        break;
    }
    */
}
