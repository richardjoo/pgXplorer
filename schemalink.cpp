/*
  LICENSE AND COPYRIGHT INFORMATION - Please read carefully.

  Copyright (c) 2011-2012, davyjones <davyjones@github>

  Permission to use, copy, modify, and/or distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include <QPainter>
#include "schemalink.h"
#include "database.h"
#include "schema.h"
#include "mainwin.h"
#include <math.h>

SchemaLink::SchemaLink(Database *source_node, Schema *destination_node)
{
    database = source_node;
    schema = destination_node;
    database->addEdge(this);
    schema->addEdge(this);
    setParentItem(source_node);
    setFlag(QGraphicsItem::ItemStacksBehindParent);
    setZValue(-100);
    adjust();
}

void SchemaLink::adjust()
{
    QLineF line(0, 0, schema->x(), schema->y());
    prepareGeometryChange();
    database_point = line.p1();
    schema_point = line.p2();
}

QRectF SchemaLink::boundingRect() const
{
    return QRectF(database_point, QSizeF(schema_point.x() - database_point.x(),
                                      schema_point.y() - database_point.y()))
        .normalized().adjusted(-.5, -.5, .5, .5);
}

void SchemaLink::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QLineF line(database_point, schema_point);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;
    painter->setPen(QPen(QColor(200,200,200), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
}
