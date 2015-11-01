#include <QDir>
#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlFileSelector>
#include <QQuickView>
#include <QQmlContext>
#include <QtSql>
#include "npsmodel.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QSqlDatabase gdbNPS ;



    gdbNPS =  QSqlDatabase::addDatabase("QSQLITE");

    gdbNPS.setDatabaseName("/sdcard/Databases/NPS.db");
    bool ok = gdbNPS.open();

    if(false == ok)
    {

        return -1;
    }

    NPSModel model;
    model.ReadfromDB(gdbNPS);

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    if (qgetenv("QT_QUICK_CORE_PROFILE").toInt()) {
        QSurfaceFormat f = view.format();
        f.setProfile(QSurfaceFormat::CoreProfile);
        f.setVersion(4, 4);
        view.setFormat(f);
    }
    view.connect(view.engine(), SIGNAL(quit()), &app, SLOT(quit()));

    QQmlContext *ctxt = view.rootContext();
    ctxt->setContextProperty("npsModel", &model);
    view.setSource(QUrl("qrc:main.qml"));


    view.show();

    return  app.exec();
}

