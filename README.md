# AppImage Thumbnail Creator for KDE 5

KDE thumbnail plugin that generates small images (thumbnails) for AppImage files,
to be displayed, for example, in Konqueror and Dolphin file managers.

![Preview](https://user-images.githubusercontent.com/1138094/37869431-0f0f3a52-2f7d-11e8-859a-7e02a00a8a6a.png)


## Dependencies

The following libraries and development packages are needed:
KDE >=5.2.x
QT  >=5.2.x
LibAppImage >= 1.0


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
