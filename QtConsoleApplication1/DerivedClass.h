#pragma once
#include <QObject>
#include <QMetaObject>
#include <QMetaMethod>
#include <QDebug>
class BaseBClass : public QObject
{
	Q_OBJECT
public:
};
class BaseClass : public QObject
{
	Q_OBJECT
public:
	Q_INVOKABLE void doSomething()
	{
		qDebug() << ("BaseClass doing something");
	}
	void reflectMethod(/*QObject* obj*/)
	{
		/*const QMetaObject* metaobj = obj->metaObject();
		QString cname = metaobj->className();

		for (int idx = metaobj->methodOffset(); idx < metaobj->methodCount(); ++idx)
		{
			QMetaMethod oneMethod = metaobj->method(idx);
			qDebug() << "--------begin-------" << "\n";
			qDebug() << " typeName: " << oneMethod.typeName() << "\n";
			qDebug() << " typeName: " << oneMethod.name() << "\n";

			qDebug() << " methodType: " << oneMethod.methodType() << "\n";
			oneMethod.invoke(obj);
			qDebug() << "--------end---------" << "\n";
		}*/

		const QMetaObject* metaobj_1 = this->metaObject();
		QString cname_1 = metaobj_1->className();
		for (int idx = metaobj_1->methodOffset(); idx < metaobj_1->methodCount(); ++idx)
		{
			QMetaMethod oneMethod = metaobj_1->method(idx);
			qDebug() << "--------begin-------" << "\n";
			qDebug() << " typeName: " << oneMethod.typeName() << "\n";
			qDebug() << " typeName: " << oneMethod.name() << "\n";

			qDebug() << " methodType: " << oneMethod.methodType() << "\n";
			oneMethod.invoke(this);

			qDebug() << "--------end---------" << "\n";
		}

	}
};

class DerivedClass : public BaseClass
{
	Q_OBJECT
public:
	Q_INVOKABLE void doSomething()
	{
		qDebug() << ("DerivedClass doing something");
	}

	Q_INVOKABLE void doSomething2()
	{
		qDebug() << ("DerivedClass doing something2");
	}
};