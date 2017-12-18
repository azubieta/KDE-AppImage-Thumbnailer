//
// Created by alexis on 17/12/17.
//
#include <QString>
#include <QImage>
#include <QStandardPaths>
#include <QMimeType>
#include <QLoggingCategory>


#include "AppImageThumbnailCreator.h"


Q_LOGGING_CATEGORY(LOG_APPIMAGE_THUMBS, "AppImageThumbs")

extern "C"
{
Q_DECL_EXPORT ThumbCreator *new_creator() {
    return new AppImageThumbnailCreator();
}
};

AppImageThumbnailCreator::AppImageThumbnailCreator(QObject *parent) : QObject(parent) {

}

AppImageThumbnailCreator::~AppImageThumbnailCreator() {

}


ThumbCreator::Flags AppImageThumbnailCreator::flags() const {
    return (ThumbCreator::Flags) (ThumbCreator::DrawFrame | ThumbCreator::BlendIcon);
}

bool AppImageThumbnailCreator::create(const QString &path, int w, int h, QImage &thumb) {
    qCDebug(LOG_APPIMAGE_THUMBS) << "Making thumbnail for: " << path;

    QString xdg_thumbnail_path = getXdgThumbnailPath(path);


    qCDebug(LOG_APPIMAGE_THUMBS) << "Opening url:" << xdg_thumbnail_path;

    QImage xdg_thumbnail;
    xdg_thumbnail.load(xdg_thumbnail_path);

    thumb = xdg_thumbnail;
    if (!xdg_thumbnail.isNull()) {
        thumb = xdg_thumbnail.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        qCDebug(LOG_APPIMAGE_THUMBS) << "Done!";
        return true;
    } else {
        qCDebug(LOG_APPIMAGE_THUMBS) << "Failed!";
        return false;
    }
}

bool AppImageThumbnailCreator::isAnAcceptedMimeType(const QString &path) const {
    QMimeType type = db.mimeTypeForFile(path);
    return type.isValid() && type.inherits("applications/x-iso9660-appimage");
}

QString AppImageThumbnailCreator::getXdgThumbnailPath(const QString &path) {
    QString thumbnail_name =
            QCryptographicHash::hash(path.toLocal8Bit(), QCryptographicHash::Md5).toHex() + ".png";


    QString xdg_thumbnail_path = QStandardPaths::standardLocations(QStandardPaths::GenericCacheLocation).first();

    xdg_thumbnail_path += "/thumbnails/normal/" + thumbnail_name;
    return xdg_thumbnail_path;
}
