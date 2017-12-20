# AppImage Thumbnail Creator for KDE 5

KDE thumbnail plugin that generates small images (thumbnails) for AppImage files,
to be displayed, for example, in Konqueror and Dolphin file managers.

**I should be used alongside with** [appimaged] (https://github.com/AppImage/AppImageKit/releases)

## Dependencies

The following libraries and development packages are needed:
KDE >=5.2.x
QT  >=5.2.x


## Build 
```
cd AppImageThumbs
mkdir build
cd build
cmake -DKDE_INSTALL_USE_QT_SYS_PATHS=ON -DCMAKE_INSTALL_PREFIX=`kf5-config --prefix` ..
make
```

### Install
```
sudo make install
```