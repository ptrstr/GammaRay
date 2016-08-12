/*
  enumpropertytest.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2016 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Volker Krause <volker.krause@kdab.com>

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <core/util.h>

#include <QtTest/qtest.h>
#include <QFrame>
#include <QObject>

using namespace GammaRay;

class EnumPropertyTest : public QObject
{
    Q_OBJECT
public:
    EnumPropertyTest(QObject *parent = Q_NULLPTR) :
        QObject(parent),
        m_widget(new QFrame)
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        qRegisterMetaType<QFrame*>();
        qRegisterMetaType<QFrame::Shadow>();
#endif
    }
private:
    QScopedPointer<QWidget> m_widget;

private slots:
    void testEnumToString_data()
    {
        QTest::addColumn<QVariant>("variant");
        QTest::addColumn<QByteArray>("name");
        QTest::addColumn<QObject*>("obj");
        QTest::addColumn<QString>("result");

        QObject *nullObj = Q_NULLPTR;
        QTest::newRow("null") << QVariant() << QByteArray() << nullObj << QString();

#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        // global enum
        QTest::newRow("global enum as int, QMO/name") << QVariant::fromValue<int>(Qt::LeftToRight) << QByteArray("Qt::LayoutDirection") << (QObject*)m_widget.data() << QStringLiteral("LeftToRight");
        QTest::newRow("global enum as int, name") << QVariant::fromValue<int>(Qt::LeftToRight) << QByteArray("Qt::LayoutDirection") << nullObj << QStringLiteral("LeftToRight");
        QTest::newRow("global enum, QMO/name") << QVariant::fromValue<Qt::LayoutDirection>(Qt::LeftToRight) << QByteArray("Qt::LayoutDirection") << (QObject*)m_widget.data() << QStringLiteral("LeftToRight");
        QTest::newRow("global enum, QMO") << QVariant::fromValue<Qt::LayoutDirection>(Qt::LeftToRight) << QByteArray() << (QObject*)m_widget.data() << QStringLiteral("LeftToRight");
        QTest::newRow("global enum, name") << QVariant::fromValue<Qt::LayoutDirection>(Qt::LeftToRight) << QByteArray("Qt::LayoutDirection") << nullObj << QStringLiteral("LeftToRight");
        QTest::newRow("global enum") << QVariant::fromValue<Qt::LayoutDirection>(Qt::LeftToRight) << QByteArray() << nullObj << QStringLiteral("LeftToRight");

        // global flag
        // TODO

        // object-local enum
        QTest::newRow("local enum as int, QMO/name") << QVariant::fromValue<int>(QFrame::Sunken) << QByteArray("QFrame::Shadow") << (QObject*)m_widget.data() << QStringLiteral("Sunken");
        QTest::newRow("local enum as int, name, registered") << QVariant::fromValue<int>(QFrame::Sunken) << QByteArray("QFrame::Shadow") << nullObj << QStringLiteral("Sunken");
        QTest::newRow("local enum as int, name, parent registered") << QVariant::fromValue<int>(QFrame::Box) << QByteArray("QFrame::Shape") << nullObj << QStringLiteral("Box");
        QTest::newRow("local enum, QMO/name") << QVariant::fromValue<QFrame::Shadow>(QFrame::Sunken) << QByteArray("QFrame::Shadow") << (QObject*)m_widget.data() << QStringLiteral("Sunken");
        QTest::newRow("local enum, QMO") << QVariant::fromValue<QFrame::Shadow>(QFrame::Sunken) << QByteArray() << (QObject*)m_widget.data() << QStringLiteral("Sunken");
        QTest::newRow("local enum, name") << QVariant::fromValue<QFrame::Shadow>(QFrame::Sunken) << QByteArray("QFrame::Shadow") << nullObj << QStringLiteral("Sunken");
        QTest::newRow("local enum") << QVariant::fromValue<QFrame::Shadow>(QFrame::Sunken) << QByteArray() << nullObj << QStringLiteral("Sunken");

        // object-local flag
        // TODO

        // gadget-local enum
        // TODO

        // gadget-local flag
        // TODO
#endif
    }

    void testEnumToString()
    {
        QFETCH(QVariant, variant);
        QFETCH(QByteArray, name);
        QFETCH(QObject*, obj);
        QFETCH(QString, result);

        auto str = Util::enumToString(variant, name, obj);
        if (str.isEmpty())
            str = variant.toString(); // normally this would be VariantHandler::displayString, but that might interfere too much for testing
        QCOMPARE(str, result);
    }

};

QTEST_MAIN(EnumPropertyTest)

#include "enumpropertytest.moc"

