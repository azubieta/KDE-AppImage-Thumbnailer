//
// Created by alexis on 17/12/17.
//

#include <QUrl>
#include <QFile>
#include <QStandardPaths>
#include <QSignalSpy>

#include <KFileItem>

#include "TestAppImageThumbnailCreator.h"
#include "../src/AppImageThumbnailCreator.h"


TestAppImageThumbnailCreator::TestAppImageThumbnailCreator(QObject *parent) : QObject(parent) {
    appimage_file_path = "file://" TEST_DATA_DIR "Echo-x86_64.AppImage";
}

void TestAppImageThumbnailCreator::testThumbnailPathGeneration() {
    AppImageThumbnailCreator c;
    QString path = "/tmp/test";

    QString result = c.getXdgThumbnailPath(path);
    QString expected = QStandardPaths::standardLocations(QStandardPaths::GenericCacheLocation).first();
    expected += "/thumbnails/normal/1fe712c2e25067e4484d12c8aa548f91.png";
    QCOMPARE(expected, result);
}

void TestAppImageThumbnailCreator::testThumbnailCreation() {
    AppImageThumbnailCreator c;

    QString thumbnail_example = TEST_DATA_DIR "thumbnail.png";
    QString thumbnail_destination = AppImageThumbnailCreator::getXdgThumbnailPath(appimage_file_path);
    QFile f(thumbnail_example);

    f.copy(thumbnail_destination);

    QImage thumb;
    bool ok = c.create(appimage_file_path, 48, 48, thumb);
    ok = ok && !thumb.isNull();

    QFile::remove(thumbnail_destination);
    if (!ok)
        QFAIL("The thumbnail wasn't created.");
}


void TestAppImageThumbnailCreator::testInstallation() {
    QStringList plugins = KIO::PreviewJob::availablePlugins();
    qDebug() << plugins;
//    Q_ASSERT(plugins.contains("appimagethumbnail"));
}


void TestAppImageThumbnailCreator::testPreviewJob() {
    QString thumbnail_example = "file://" TEST_DATA_DIR "thumbnail.png";
    QString thumbnail_destination = AppImageThumbnailCreator::getXdgThumbnailPath(appimage_file_path);

    QFile f(thumbnail_example);
    f.copy(thumbnail_destination);

    KFileItemList items;
    items.append(KFileItem(QUrl(thumbnail_example)));
    items.append(KFileItem(QUrl(appimage_file_path)));

    QStringList plugins = {"imagethumbnail", "appimagethumbnail"};
    const QSize size(48, 48);
    KIO::PreviewJob *job = new KIO::PreviewJob(items, size, &plugins);
    qDebug() << plugins;
    connect(job, &KIO::PreviewJob::failed, [=](const KFileItem &item) {
        qWarning() << "Failed to created thumbnail for " << item.name() << item.mimetype();
        qWarning() << job->errorString();
        QFAIL("Job failed to create a thumbnail.");
    });

    connect(job, &KIO::PreviewJob::gotPreview, [=](const KFileItem &item, const QPixmap &preview) {
        if (preview.isNull())
            QFAIL("Empty thumbnail result");
        else
            qDebug() << "Thumbnail created for: " << item.name();
    });

    connect(job, &KJob::infoMessage, [=](KJob *, const QString &plain, const QString &) {
        qDebug() << plain;
    });

    connect(job, &KJob::warning, [=](KJob *, const QString &plain, const QString &) {
        qWarning() << plain;
    });

    bool res = job->exec();
    QFile::remove(thumbnail_destination);

    if (!res)
        QFAIL("There was an error while executing the job");
}


QTEST_MAIN(TestAppImageThumbnailCreator);