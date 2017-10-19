#!bash/sh
#for i in $(seq 1 9)
#do
#	mv Documents/lecnote/ex$i* Documents/lecnote/ex$i\/
#	mv Documents/lecnote/*0$i* Documents/lecnote/ex$i\/
#	mv Documents/lecnote/*y$i* Documents/lecnote/ex$i\/
#done
sudo add-apt-repository ppa:levi-armstrong/qt-libraries-trusty
sudo add-apt-repository ppa:levi-armstrong/ppa  
sudo apt-get update && sudo apt-get install qt57creator-plugin-ros
