//
// Created by alexis on 17/12/17.
//
#include <QString>
#include <QImage>
#include <QStandardPaths>
#include <QMimeType>
#include <QLoggingCategory>
#include <QUrl>
#include <QFile>
#include <QDir>
#include <appimage/appimage.h>
#include <QTemporaryFile>

#include "AppImageThumbnailCreator.h"


Q_LOGGING_CATEGORY(LOG_APPIMAGE_THUMBS, "AppImageThumbs")

extern "C"
{
Q_DECL_EXPORT ThumbCreator *new_creator() {
    return new AppImageThumbnailCreator();
}
}

AppImageThumbnailCreator::AppImageThumbnailCreator(QObject *parent) : QObject(parent) {

}

AppImageThumbnailCreator::~AppImageThumbnailCreator() {

}


ThumbCreator::Flags AppImageThumbnailCreator::flags() const {
    return ThumbCreator::None;
}

bool AppImageThumbnailCreator::create(const QString &path, int w, int h, QImage &thumb) {
    qCDebug(LOG_APPIMAGE_THUMBS) << "Making thumbnail for: " << path;
    auto newPath = removeProtocolPrefixIfNeeded(path);

    QString tmpPath = QDir::tempPath() + "/appimage_thumbnailer_XXXXXX";
    QFile file("/tmp/log");
    bool succesed = false;

    file.write(newPath.toLocal8Bit());
    file.write(tmpPath.toLocal8Bit());
    appimage_extract_file_following_symlinks(newPath.toStdString().c_str(), ".DirIcon",
                                             tmpPath.toStdString().c_str());

    succesed = thumb.load(tmpPath);
    thumb = thumb.scaled(w, h);

    QFile::remove(tmpPath);

    return succesed;

}

bool AppImageThumbnailCreator::isAnAcceptedMimeType(const QString &path) const {
    QMimeType type = db.mimeTypeForFile(path);
    return type.isValid() &&
           (type.inherits("application/x-iso9660-appimage") || type.inherits("application/vnd.appimage"));
}

QString AppImageThumbnailCreator::removeProtocolPrefixIfNeeded(const QString &path) {
    QString correctPath = path;
    if (path.startsWith("file://"))
        correctPath = correctPath.replace("file://", "", Qt::CaseInsensitive);

    return correctPath;
}

QString AppImageThumbnailCreator::appendProtocolPrefixIfNeeded(const QString &path) {
    QString correctPath;
    if (path.startsWith("/"))
        correctPath = "file://" + path;
    else
        correctPath = path;

    return correctPath;
}
