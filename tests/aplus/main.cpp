// Copyright (C) 2015 Ilya Lyubimov
//
// This file is part of qpromise.
//
//  Qpromise is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  Qpromise is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with qpromise.  If not, see <http://www.gnu.org/licenses/>.

#include <QCoreApplication>

#include <QPromise/QDeferred>

namespace AplusplusTests {

namespace Adapter {

template <typename F> void setTimeout(F&& f, int msec) { QTimer::singleShot(msec, f); }

QVariant value("dummy");
QPromiseException reason;

typedef const decltype(value)& Value;
typedef const decltype(reason)& Reason;

// TODO: move from adapter
void nullResolved(const QVariant&) {}

QDeferred deferred() noexcept { return QDeferred(); }
QPromise resolved(const QVariant& v) noexcept { return Q::resolve(v); }
QPromise rejected(const QPromiseException& r) noexcept { return Q::reject(r); }
}
}

#include <aplusplus-tests/all.h>

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	QCoreApplication app(argc, argv);

	QTimer::singleShot(0, []() {
		int r = RUN_ALL_TESTS();
		QCoreApplication::instance()->exit(r);
	});

	return app.exec();
}
