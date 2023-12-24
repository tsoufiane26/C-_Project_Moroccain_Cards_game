// CarteItem.h
#ifndef CARTEITEM_H
#define CARTEITEM_H

#include <QGraphicsPixmapItem>

class CarteItem : public QGraphicsPixmapItem {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    CarteItem(const QPixmap& image, QGraphicsItem* parent = nullptr);
    // Ajoutez des méthodes pour manipuler la carte, par exemple, pour effectuer des animations.
};

#endif // CARTEITEM_H
