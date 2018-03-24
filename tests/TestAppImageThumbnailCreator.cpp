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

void TestAppImageThumbnailCreator::testThumbnailCreation() {
    AppImageThumbnailCreator c;

    QImage thumb;
    bool success = c.create(TEST_DATA_DIR "Echo-x86_64.AppImage", 48, 48, thumb);

    QTEST_ASSERT(success);

    QImage expected;
    expected.load(TEST_DATA_DIR "thumbnail.png");
    expected = expected.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QTEST_ASSERT(!thumb.isNull());
    QTEST_ASSERT(!expected.isNull());
    QTEST_ASSERT(expected == thumb);
}


void TestAppImageThumbnailCreator::testInstallation() {
    QStringList plugins = KIO::PreviewJob::availablePlugins();
    Q_ASSERT(plugins.contains("appimagethumbnail"));
}


void TestAppImageThumbnailCreator::testPreviewJob() {
    QString thumbnail_example = "file://" TEST_DATA_DIR "thumbnail.png";

    QFile f(thumbnail_example);

    KFileItemList items;
    items.append(KFileItem(QUrl(thumbnail_example)));
    items.append(KFileItem(QUrl(appimage_file_path)));

    QStringList plugins = {"imagethumbnail", "appimagethumbnail"};
    const QSize size(48, 48);
    KIO::PreviewJob *job = KIO::filePreview(items, size, &plugins);
    qWarning() << "plugins: " << plugins;
    qWarning() << "supported: " << job->supportedMimeTypes();
    connect(job, &KIO::PreviewJob::failed, [=](const KFileItem &item) {
        qWarning() << "Failed to created thumbnail for " << item.url() << item.mimetype();
        QFAIL("Job failed to create a thumbnail.");
    });

    connect(job, &KIO::PreviewJob::gotPreview, [=](const KFileItem &item, const QPixmap &preview) {
        if (preview.isNull())
            QFAIL("Empty thumbnail result");
        else
            qDebug() << "Thumbnail created for: " << item.name();
    });

    connect(job, &KJob::infoMessage, [=](KJob *, const QString &plain, const QString &msg) {
        qWarning() << plain << msg;
    });

    connect(job, &KJob::warning, [=](KJob *, const QString &plain, const QString &msg) {
        qWarning() << plain << msg;
    });

    bool res = job->exec();

    if (!res)
        QFAIL("There was an error while executing the job");
}


QTEST_MAIN(TestAppImageThumbnailCreator);
