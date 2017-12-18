//
// Created by alexis on 17/12/17.
//

#ifndef APPIMAGESKDETHUMNAILER_APPIMAGETHUMBNAILCREATOR_H
#define APPIMAGESKDETHUMNAILER_APPIMAGETHUMBNAILCREATOR_H

#include <QCryptographicHash>
#include <QMimeDatabase>
#include <QObject>

#include <kio/thumbcreator.h>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(LOG_APPIMAGE_THUMBS)

class AppImageThumbnailCreator : public QObject, public ThumbCreator {
Q_OBJECT
    QMimeDatabase db;
public:
    AppImageThumbnailCreator(QObject *parent = 0);
    virtual ~AppImageThumbnailCreator();
    virtual bool create(const QString &path, int w, int h, QImage &thumb);
    virtual Flags flags() const;

    QString getXdgThumbnailPath(const QString &path);
    bool isAnAcceptedMimeType(const QString &path) const;
};


#endif //APPIMAGESKDETHUMNAILER_APPIMAGETHUMBNAILCREATOR_H
