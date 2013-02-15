#ifndef LOG_H
#define LOG_H

#include <QDebug>

//TODO use different log fuctions
#ifdef QT_DEBUG
	#define DEBUG(X) qDebug() << X
	#define TRACE(X) qDebug() << X
	#define FATAL(X) qDebug() << X
#else
	#define DEBUG(X)
	#define TRACE(X)
	#define FATAL(X)
#endif

#define LOG(X) qDebug() << X

#endif // LOG_H
