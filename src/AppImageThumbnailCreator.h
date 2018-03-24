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
    explicit AppImageThumbnailCreator(QObject *parent = 0);
    ~AppImageThumbnailCreator() override;
    bool create(const QString &path, int w, int h, QImage &thumb) override;
    Flags flags() const override;

    bool isAnAcceptedMimeType(const QString &path) const;

private:
    QString removeProtocolPrefixIfNeeded(const QString &path);
    QString appendProtocolPrefixIfNeeded(const QString &path);

};


#endif //APPIMAGESKDETHUMNAILER_APPIMAGETHUMBNAILCREATOR_H
