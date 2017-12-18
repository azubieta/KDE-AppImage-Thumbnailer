//
// Created by alexis on 17/12/17.
//

#ifndef APPIMAGETHUMBS_TESTAPPIMAGETHUMBNAILCREATOR_H
#define APPIMAGETHUMBS_TESTAPPIMAGETHUMBNAILCREATOR_H

#include <QObject>
#include <QTest>

class TestAppImageThumbnailCreator : public  QObject {
    Q_OBJECT
public:
    TestAppImageThumbnailCreator(QObject *parent = 0);

private slots:
    void testThumbnailPathGeneration();
};


#endif //APPIMAGETHUMBS_TESTAPPIMAGETHUMBNAILCREATOR_H
