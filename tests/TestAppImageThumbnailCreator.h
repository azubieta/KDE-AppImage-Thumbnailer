//
// Created by alexis on 17/12/17.
//

#ifndef APPIMAGETHUMBS_TESTAPPIMAGETHUMBNAILCREATOR_H
#define APPIMAGETHUMBS_TESTAPPIMAGETHUMBNAILCREATOR_H

#include <QString>
#include <QObject>
#include <QTest>
#include <KIO/PreviewJob>

class TestAppImageThumbnailCreator : public  QObject {
    Q_OBJECT
    QString appimage_file_path;
public:
    TestAppImageThumbnailCreator(QObject *parent = 0);

private slots:
    void testThumbnailPathGeneration();
    void testThumbnailCreation();
    void testInstallation();
    void testPreviewJob();

};


#endif //APPIMAGETHUMBS_TESTAPPIMAGETHUMBNAILCREATOR_H
