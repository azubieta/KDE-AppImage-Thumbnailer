//
// Created by alexis on 17/12/17.
//

#include <QStandardPaths>

#include "TestAppImageThumbnailCreator.h"
#include "AppImageThumbnailCreator.h"


TestAppImageThumbnailCreator::TestAppImageThumbnailCreator(QObject *parent ) : QObject(parent){

}

void TestAppImageThumbnailCreator::testThumbnailPathGeneration() {
    AppImageThumbnailCreator c;
    QString path = "/tmp/test";

    QString result = c.getXdgThumbnailPath(path);
    QString expected = QStandardPaths::standardLocations(QStandardPaths::GenericCacheLocation).first();
    expected += "/thumbnails/normal/d1309ac1e2719cdf777c0d6e936fc92b.png";
    QCOMPARE(expected, result);
}


QTEST_MAIN(TestAppImageThumbnailCreator);