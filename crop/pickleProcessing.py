import cv2
import os
import torchvision.transforms as transforms
import pickle
import numpy as np

class imgNetDataManager:
    def __init__(self, loaded_path=None, random_crop=True, type_flag=True):
        self.num_channels = 3
        self.img_size = 64
        self.type_flag = type_flag
        self.num = 0

    def _convert_images(self, raw):
        images = raw.reshape([-1, self.num_channels, self.img_size, self.img_size])
        # Reorder the indices of the array.
        images = images.transpose([0, 2, 3, 1])
        return images

    def mkFolder(self, outFolder):
        self.outFolder = outFolder
        if not os.path.isdir(self.outFolder):
            os.mkdir(self.outFolder)

    def mkClassFolderDict(self):
        self.classDict = {}
        for idx in range(1000):
            self.classDict[idx+1] = os.path.join(self.outFolder, str(idx+1))
            if not os.path.isdir(self.classDict[idx+1]):
                os.mkdir(self.classDict[idx+1])

    def iterFile(self, loaded_path):
        fileList = os.listdir(loaded_path)
        for filename in fileList:
            file = open(os.path.join(loaded_path, filename), mode='rb')
            data = pickle.load(file, encoding='bytes')
            print(filename)
            raw_images = data['data']
            self.cls = data['labels']
            self.images = self._convert_images(raw_images)
            for idx in range(self.images.shape[0]):
                cv2.imwrite(os.path.join(self.classDict[self.cls[idx]], filename + '_' + str(idx)+'.jpg'), cv2.cvtColor(np.uint8(self.images[idx]), cv2.COLOR_BGR2RGB))

if __name__ == '__main__':
    dm = imgNetDataManager()
    dm.mkFolder('/run/user/1020/gvfs/dav:host=urobot.synology.me,port=5006,ssl=true,user=cpark/ResearchServer/dataset/ImageNet/downsampled/64/train')
    dm.mkClassFolderDict()
    trainFolders = ['/run/user/1020/gvfs/dav:host=urobot.synology.me,port=5006,ssl=true,user=cpark/ResearchServer/dataset/ImageNet/downsampled/64/Imagenet64_train_part2', '/run/user/1020/gvfs/dav:host=urobot.synology.me,port=5006,ssl=true,user=cpark/ResearchServer/dataset/ImageNet/downsampled/64/Imagenet64_train_part1']
    for trainFolder in trainFolders:
        dm.iterFile(trainFolder)
