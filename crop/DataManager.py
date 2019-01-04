import os
import random

import pandas as pd
import numpy as np

import cv2
from PIL import Image

from torch.utils.data import Dataset
import torchvision.transforms as transforms

class VideoFile:
    def set_video_file(self, video_path):
        '''
        :param video_path: a path of a video file
        :return: set path and video capture in this module
        '''
        self.video_path = video_path
        self.video_capture = cv2.VideoCapture(self.video_path)

    def release_video(self):
        '''
        :return: release video capture
        '''
        self.video_capture.release()

    def read_video(self):
        '''
        :return: set and return frame number and video image
        '''
        self.frame_number = self.video_capture.get(cv2.CAP_PROP_POS_FRAMES)
        self.success, self.frame_image = self.video_capture.read()
        return self.success, self.frame_image

class AnnotationFile:
    def set_annotation_file(self, annotation_path):
        '''
        :param annotation_path: a path of an annotation file

        :return: set path and file descriptor in this module
        '''
        # open CSV file encoding type euc-kr
        # return reader and csv_file for closing
        self.annotation_path = annotation_path
        self.csv_pd = pd.read_csv(self.annotation_path, encoding='euc-kr')

class TorchTransformModule(Dataset):
    def set_transforms_variables(self, random_crop=True):
        self.input_transform = transforms.Compose(
            [
                transforms.Resize(size=(32, 32)),
                transforms.Resize(size=(64, 64)),
                transforms.ToTensor(),
                transforms.Normalize(mean=[0, 0, 0],
                                     std=[0.5, 0.5, 0.5])
            ]
        )

        self.target_transform = transforms.Compose(
            [
                transforms.Resize(size=(64, 64)),
                transforms.ToTensor(),
                transforms.Normalize(mean=[0, 0, 0],
                                     std=[0.5, 0.5, 0.5])
            ]
        )

        self.resize_transform = transforms.Compose(
            [
                transforms.Resize(size=(32, 32)),
                transforms.Resize(size=(64, 64)),
                transforms.ToTensor(),
                transforms.Normalize(mean=[0, 0, 0],
                                     std=[0.5, 0.5, 0.5])
            ]
        )

        self.restore = transforms.Compose(
            [
                transforms.Normalize(mean=[0, 0, 0],
                                     std=[2, 2, 2]),
            ]
        )

        if random_crop:
            self.transform = transforms.Compose(
                [
                    transforms.Resize(size=(256, 256)),
                    transforms.RandomHorizontalFlip(),
                    transforms.RandomRotation((-90, 90)),
                    # transforms.ToTensor(),
                    # transforms.Normalize(mean=[0, 0, 0],
                    #                      std=[0.5, 0.5, 0.5])
                ]
            )
        else:
            self.transform = transforms.Compose(
                [
                    transforms.Resize(size=(256, 256)),
                    # transforms.ToTensor(),
                    # transforms.Normalize(mean=[0, 0, 0],
                    #                      std=[0.5, 0.5, 0.5])
                ]
            )

        self.sr_transform = transforms.Compose(
            [
                transforms.Resize(size=(64, 64)),
                transforms.ToTensor(),
                transforms.Normalize(mean=[0, 0, 0],
                                     std=[0.5, 0.5, 0.5])
            ]
        )

        self.cls_transform = transforms.Compose(
            [
                transforms.ToTensor(),
                transforms.Normalize(mean=[0, 0, 0],
                                     std=[0.5, 0.5, 0.5])
            ]
        )

class SR_DataManager(TorchTransformModule):
    def __init__(self):
        self.set_transforms_variables()

    def initialize_manager(self, data_folder_path):
        self.data_folder_path = data_folder_path
        self.data_list = os.listdir(self.data_folder_path)
        self.data_number = len(self.data_list)

        assert self.data_number > 0

        print('Data path : %s' % (self.data_folder_path))
        print('Dataset size : %d' % (self.data_number))

    def __len__(self):
        return self.data_number

    def __getitem__(self, idx):
        data_path = os.path.join(self.data_folder_path, self.data_list[idx])

        img = Image.open(data_path)

        input_img = self.input_transform(img)
        target_img = self.target_transform(img)
        bicubic_img = self.resize_transform(img)

        sample = {'input_img': input_img, 'target_img': target_img, 'bicubic_img': bicubic_img}

        return sample


class Cls_DataManager(TorchTransformModule):
    def __init__(self, loaded_path, className=['bicycle', 'bus', 'human', 'sedan', 'truck'], random_crop=True):
        self.set_transforms_variables(random_crop)
        self.loaded_path = loaded_path
        self.list_classes = listdir(loaded_path)
        self.className = className
        self.train_img = []
        self.train_label = []
        self.num = 0
        # for class_path in self.list_classes:
        for clsIdx, class_path in enumerate(className):
            list_img_per_class = listdir(os.path.join(self.loaded_path, class_path))
            # train img : list of img directories
            # train label : corresponding class of train img[idx]
            self.train_img += [img_name for img_name in list_img_per_class]
            self.train_label += [clsIdx for _ in range(len(list_img_per_class))]
            #num : total number of samples
            self.num += len(list_img_per_class)

        assert self.num > 0
        assert (len(self.train_img) == len(self.train_label))

        print('Content root : %s' % (self.loaded_path))
        print('Number of images : %d' % (self.num))

    def __len__(self):
        return self.num

    def __getitem__(self, idx):
        label = self.train_label[idx]
        img_path = os.path.join(self.loaded_path, self.className[label], self.train_img[idx])
        img = Image.open(img_path)
        img = self.transform(img)
        img_sr_input = self.sr_transform(img)
        img_cls_input = self.cls_transform(img)

        return img_cls_input, img_sr_input, label

class imgNetDataManager(TorchTransformModule):
    def __init__(self, loaded_path, random_crop=True, type_flag=True):
        self.set_transforms_variables(random_crop)

        self.loaded_path = loaded_path
        self.list_classes = listdir(loaded_path)
        self.num = 0
        self.train_img = []
        self.train_label = []
        self.type_flag = type_flag

       # for class_path in self.list_classes:
        for clsIdx in range(1000):
            clsIdx += 1
            list_img_per_class = listdir(os.path.join(self.loaded_path, str(clsIdx)))
            # train img : list of img directories
            # train label : corresponding class of train img[idx]
            self.train_img += [img_name for img_name in list_img_per_class]
            self.train_label += [clsIdx for _ in range(len(list_img_per_class))]
            #num : total number of samples
            self.num += len(list_img_per_class)

        assert self.num > 0
        assert (len(self.train_img) == len(self.train_label))

        self.num_list = self.num
        print('Content root : %s' % (self.loaded_path))
        print('Number of images : %d' % (self.num))

    def __len__(self):
        return self.num

    def __getitem__(self, idx):
        ### type_flag True means sr datamanager
        label = self.train_label[idx]
        img_path = os.path.join(self.loaded_path, str(label), self.train_img[idx])
        img = Image.open(img_path)

        if self.type_flag:
            img = self.transform(img)
            img_sr_input = self.sr_transform(img)
            img_cls_input = self.cls_transform(img)

            return img_cls_input, img_sr_input, label
        else:
            input_img = self.input_transform(img)
            target_img = self.target_transform(img)
            bicubic_img = self.resize_transform(img)

            sample = {'input_img': input_img, 'target_img': target_img, 'bicubic_img': bicubic_img}

            return sample














class HeatmapDataManager:
    def __init__(self, dataDir, batch_size, input_size, output_size, class_num=5, crop_size=[1, 2], framestep=5, shuffle=True):
        self.dataDir = dataDir
        self.batch_size = batch_size
        self.input_size = input_size    # image size
        self.output_size = output_size  # heatmap size
        self.class_num = class_num
        self.crop_size = crop_size
        self.framestep = framestep

        self.frame = None
        self.annos = []
        self.heatmap = None

        self.frameBuffer = []
        self.heatmapBuffer = []

        self.batch_imgs = []
        self.batch_labels = []

        self.startFrame = 0
        self.count = 0

    def setVideo(self, video_directory):
        self.video_name = video_directory
        self.vidcap = cv2.VideoCapture(self.video_name)

    def setCSV(self, csv_directory):
        self.csv_name = csv_directory
        self.csv_pd = pd.read_csv(self.csv_name, delimiter = ',', encoding = 'euc-kr')

        maxframe = np.max(self.csv_pd['FrameNum'])
        # self.frameIdx = list(range(0, maxframe-framestep))
        self.frameIdx = np.arange(0, maxframe - self.framestep)
        random.shuffle(self.frameIdx)

    def getStartEndPointsList(self):
        tmpHeight = int(self.frame.shape[0] / self.crop_size[0])
        tmpWidth = int(self.frame.shape[1] / self.crop_size[1])
        tmpLength = tmpHeight
        startEndPointsList = []
        for yy in range(self.crop_size[0]):
            for xx in range(self.crop_size[1]):
                startPointYY = (yy + 1) * tmpHeight - tmpLength
                if startPointYY < 0:
                    startPointYY = 0
                endPointYY = startPointYY + tmpLength
                startPointXX = (xx + 1) * tmpWidth - tmpLength
                if startPointXX < 0:
                    startPointXX = 0
                endPointXX = startPointXX + tmpLength
                startEndPointsList.append({'startPointX':startPointXX,'startPointY':startPointYY,'endPointX':endPointXX,'endPointY':endPointYY})
        return startEndPointsList

    def getFrame(self, frame_number):
        total_frames = self.vidcap.get(cv2.CAP_PROP_POS_FRAMES)
        self.vidcap.set(cv2.CAP_PROP_POS_FRAMES, frame_number)
        success, self.frame = self.vidcap.read()

    def getAnnotations(self, frame_number):
        frame_list_in_csv = self.csv_pd['FrameNum']
        # line = csv_pd.loc[frame_number, : ]
        index_list = self.csv_pd.index[frame_list_in_csv == frame_number].tolist()
        self.annos = self.csv_pd.loc[index_list, :]

    def getDividedFrameList(self, frameNum, startEndPointsList):
        tmpImageList = []
        for sePoints in startEndPointsList:
            tmpImageList.append(self.frame[sePoints['startPointY']:sePoints['endPointY'], sePoints['startPointX']:sePoints['endPointX'], :])
        return tmpImageList

    def getAnnotationsList(self, frameNum, startEndPointsList):
        tmpAnnotationList = []
        for sePoints in startEndPointsList:
            tmpAnnotations = []
            for i in range(0, len(self.annos)):
                center_X = int(self.annos['CenterX'].iloc[i])
                center_Y = int(self.annos['CenterY'].iloc[i])
                if center_X >= sePoints['startPointX'] and center_X <= sePoints['endPointX'] and center_Y >= sePoints['startPointY'] and center_Y <= sePoints['endPointY']:
                    tmpA = self.annos.iloc[i].copy()
                    tmpA['CenterX'] = self.annos['CenterX'].iloc[i] - sePoints['startPointX']
                    tmpA['CenterY'] = self.annos['CenterY'].iloc[i] - sePoints['startPointY']
                    tmpA['LLX'] = self.annos['LLX'].iloc[i] - sePoints['startPointX']
                    tmpA['LLY'] = self.annos['LLY'].iloc[i] - sePoints['startPointY']
                    tmpA['URX'] = self.annos['URX'].iloc[i] - sePoints['startPointX']
                    tmpA['URY'] = self.annos['URY'].iloc[i] - sePoints['startPointY']

                    tmpAnnotations.append(tmpA)
                tmpAnnotationList.append(tmpAnnotations)
        return tmpAnnotationList

    def parseData(self, frameNum):
        self.getFrame(frameNum)
        self.getAnnotations(frameNum)
        startEndPointsList = self.getStartEndPointsList()
        return self.getDividedFrameList(frameNum, startEndPointsList), self.getAnnotationsList(frameNum, startEndPointsList)

    def drawBoundingBox(self):
        for i in range(0, len(self.annos)):
            ll_X = int(self.annos['LLX'].iloc[i])
            ll_Y = int(self.annos['LLY'].iloc[i])
            ur_X = int(self.annos['URX'].iloc[i])
            ur_Y = int(self.annos['URY'].iloc[i])

            self.frame = cv2.rectangle(self.frame, (ur_X, ur_Y), (ll_X, ll_Y), (0, 0, 255), 2)

    def make_gaussian(self, size, fwhm=3, center=None):
        x = np.arange(0, size, 1, float)
        y = x[:, np.newaxis]

        if center is None:
            x0 = y0 = size // 2
        else:
            x0 = center[0]
            y0 = center[1]

        return np.exp(-((x - x0) ** 2 + (y - y0) ** 2) / 2.0 / fwhm / fwhm)

    def drawHeatmaps(self):
        height, width, channels = self.frame.shape
        heatmaps = np.zeros(shape=(width, width, 1))
        for i in range(0, len(self.annos)):
            center_X = int(self.annos['CenterX'].iloc[i])
            center_Y = int(self.annos['CenterY'].iloc[i])
            ll_X = int(self.annos['LLX'].iloc[i])
            ll_Y = int(self.annos['LLY'].iloc[i])
            ur_X = int(self.annos['URX'].iloc[i])
            ur_Y = int(self.annos['URY'].iloc[i])

            length_X = ur_X - ll_X
            length_Y = ll_Y - ur_Y
            if (length_X > length_Y):
                radius = length_Y/2
            else:
                radius = length_X/2

            radius *= 0.8
            heatmaps[:, :, 0] = np.maximum(heatmaps[:, :, 0], self.make_gaussian(width, radius, [center_X, center_Y]))

        self.heatmap = cv2.applyColorMap((heatmaps * 255).astype(np.uint8), cv2.COLORMAP_JET)

    def drawHeatmap(self, image, annos, heatmapSize, class_num=5):
        height, width, channels = image.shape
        heatmaps = np.zeros(shape=(heatmapSize, heatmapSize, class_num))
        for i in range(0, len(annos)):
            center_X = int(self.annos['CenterX'].iloc[i])
            center_Y = int(self.annos['CenterY'].iloc[i])
            ll_X = int(self.annos['LLX'].iloc[i])
            ll_Y = int(self.annos['LLY'].iloc[i])
            ur_X = int(self.annos['URX'].iloc[i])
            ur_Y = int(self.annos['URY'].iloc[i])

            classString = self.annos[i]['ObjectType']
            classIdx = 0
            if (classString == '자전거'):
                classIdx = 0
            elif (classString == '버스'):
                classIdx = 1
            elif (classString == '사람'):
                classIdx = 2
            elif (classString == '세단'):
                classIdx = 3
            elif (classString == '트럭'):
                classIdx = 4

            length_X = ur_X - ll_X
            length_Y = ur_Y - ll_Y
            if (length_X > length_Y):
                radius = length_Y / 2
            else:
                radius = length_X / 2

            radius *= 0.5
            heatmaps[:, :, classIdx] = np.maximum(heatmaps[:, :, classIdx], self.make_gaussian(heatmapSize, radius, [center_X, center_Y]))
        return heatmaps
        # self.heatmap = cv2.applyColorMap((heatmaps * 255).astype(np.uint8), cv2.COLORMAP_JET)

    def convertHeatmapCoordinate(self, image, annos, heatmapSize):
        height, width, _ = image.shape

        scale_x = width / heatmapSize
        scale_y = height / heatmapSize

        reloc_x = int(annos['x'] / scale_x)
        reloc_y = int(annos['y'] / scale_y)


    def _get_next_batch(self):
        del self.batch_imgs[:]
        del self.batch_labels[:]

        cur_batch_size = 0

        for startFrame in self.frameIdx[self.count:]:
            # self.getInformations(startFrame)
            images, annos = self.parseData(startFrame)

            for i in range(2):
                if (len(annos[i]) > 0):
                    height, width, _ = images[i].shape

                    scale_x = width / self.output_size
                    scale_y = height / self.output_size

                    relocAnno = {}
                    relocAnno['CenterX'] = int(self.annos['CenterX'].iloc[i] / scale_x)
                    relocAnno['CenterY'] = int(self.annos['CenterY'].iloc[i] / scale_y)
                    relocAnno['LLX'] = int(self.annos['LLX'].iloc[i] / scale_x)
                    relocAnno['LLY'] = int(self.annos['LLY'].iloc[i] / scale_y)
                    relocAnno['URX'] = int(self.annos['URX'].iloc[i] / scale_x)
                    relocAnno['URY'] = int(self.annos['URY'].iloc[i] / scale_y)

                    # heatmaps = np.zeros(shape=(self.output_size, self.output_size, self.class_num))
                    heatmaps = self.drawHeatmap(images[i], relocAnno, heatmapSize=self.output_size)

                    # Create background map
                    output_background_map = np.ones((self.output_size, self.output_size)) - np.amax(heatmaps, axis=2)
                    heatmaps = np.concatenate((heatmaps, output_background_map.reshape((self.output_size, self.output_size, 1))), axis=2)

                    self.batch_imgs.append(input_image)
                    self.batch_labels.append(heatmaps)

                    cur_batch_size += 1

                    if (cur_batch_size == self.batch_size):
                        break

                else:
                    self.count += 1
                    continue

        if (self.count == len(self.frameIdx)):
            self.count = 0

        batchImages = np.asarray(self.batch_imgs, dtype=np.float32)
        batchImages = batchImages / 255.0 - 0.5
        batchLabels = np.asarray(self.batch_labels, dtype=np.float32)
        return batchImages, batchLabels

class DataReader:
    def __init__(self, dataClass = ['bus', 'sedan', 'bicycle','human', 'truck'], dirDepth=None):
        self.dataClass = dataClass
        self.dirDepth = dirDepth
        self.dataFolders = []

    def insertDirPath(self, dirPath):
        self.dirPath = dirPath

    def mkFileNameCarrier(self):
        self.totalFileName = {}
        for name in self.dataClass:
            self.totalFileName[name] = []

    def mkImageCarrier(self):
        self.totalImage_list = []
        self.totalLabel_list = []


    def readFileName(self):
        self.mkFileNameCarrier()
        dataFolders = os.listdir(self.dirPath)

        for dataFolder in dataFolders:
            dataFolderPath = os.path.join(self.dirPath, dataFolder)

            for className in self.dataClass:
                classFolderPath = os.path.join(dataFolderPath, className)
                imageFiles = os.listdir(classFolderPath)

                for imageFile in imageFiles:
                    imageFilePath = os.path.join(classFolderPath, imageFile)
                    self.totalFileName[className].append(imageFilePath)
    def flushDataFolders(self):
        self.dataFolders = []

    def setDataFolders(self, folder_path):
        self.dataFolders.append(folder_path)

    def readImages(self):
        self.mkImageCarrier()


        for dataFolder in self.dataFolders:
            for className in self.dataClass:
                classFolderPath = os.path.join(dataFolder, className)
                imageFiles = os.listdir(classFolderPath)

                if imageFiles: #check folder is empty or not
                    for imageFile in imageFiles:
                        imageFilePath = os.path.join(classFolderPath, imageFile)
                        image = cv2.imread(imageFilePath)
                        if image is None: #check whther file is None or not
                            continue
                        self.totalImage_list.append(image)
                        self.totalLabel_list.append(self.dataClass.index(className))

        return self.totalImage_list, self.totalLabel_list



import cv2
import numpy as np
import pandas as pd
import os

class YoloDataManager:
    def __init__(self, dataDir=None, frameStep=5):
        self.dataDir = dataDir

        self.frameStep = frameStep

        self.classes = {'자전거':0, '버스':1, '사람':2, '세단':3, '트럭':4,
                           'bike':0, 'none':1, 'person':2, 'sedan':3, 'truck':4}


        self.frame = None
        self.annos = []
        self.heatmap = None

        self.frameBuffer = []

        self.readSuccess = True

        self.nameCount = 0

        self.boundingBoxsz = {'max':[0, 0], 'min':[1000, 1000]}

        self.frameNum = 0
        self.trueFrameNum = 0

    def getStartEndPointsList(self):
        tmpHeight = int(self.frame.shape[0] / self.crop_size[0])
        tmpWidth = int(self.frame.shape[1] / self.crop_size[1])
        tmpLength = tmpHeight
        startEndPointsList = []
        for yy in range(self.crop_size[0]):
            for xx in range(self.crop_size[1]):
                startPointYY = (yy + 1) * tmpHeight - tmpLength
                if startPointYY < 0:
                    startPointYY = 0
                endPointYY = startPointYY + tmpLength
                startPointXX = (xx + 1) * tmpWidth - tmpLength
                if startPointXX < 0:
                    startPointXX = 0
                endPointXX = startPointXX + tmpLength
                startEndPointsList.append({'startPointX':startPointXX,'startPointY':startPointYY,'endPointX':endPointXX,'endPointY':endPointYY})
        return startEndPointsList

    def getDividedFrameList(self, startEndPointsList):
        tmpImageList = []
        for sePoints in startEndPointsList:
            tmpImageList.append(self.frame[sePoints['startPointY']:sePoints['endPointY'], sePoints['startPointX']:sePoints['endPointX'], :])
        return tmpImageList

    def getAnnotationsList(self, startEndPointsList):
        tmpAnnotationList = []
        for sePoints in startEndPointsList:
            tmpAnnotations = []
            for i in range(0, len(self.annos)):
                center_X = int(self.annos['CenterX'].iloc[i])
                center_Y = int(self.annos['CenterY'].iloc[i])
                if center_X >= sePoints['startPointX'] and center_X <= sePoints['endPointX'] and center_Y >= sePoints['startPointY'] and center_Y <= sePoints['endPointY']:
                    tmpA = self.annos.iloc[i].copy()
                    tmpA['CenterX'] = self.annos['CenterX'].iloc[i] - sePoints['startPointX']
                    tmpA['CenterY'] = self.annos['CenterY'].iloc[i] - sePoints['startPointY']
                    tmpA['LLX'] = self.annos['LLX'].iloc[i] - sePoints['startPointX']
                    tmpA['LLY'] = self.annos['LLY'].iloc[i] - sePoints['startPointY']
                    tmpA['URX'] = self.annos['URX'].iloc[i] - sePoints['startPointX']
                    tmpA['URY'] = self.annos['URY'].iloc[i] - sePoints['startPointY']

                    tmpAnnotations.append(tmpA)
                tmpAnnotationList.append(tmpAnnotations)
        return tmpAnnotationList

    def parseData(self, frameNum=None):
        self.getFrame(frameNum)
        self.getAnnotations(frameNum)
        startEndPointsList = self.getStartEndPointsList()
        return self.getDividedFrameList(startEndPointsList), self.getAnnotationsList(startEndPointsList)

    def setVideo(self, video_directory):
        self.videoName = video_directory
        self.vidcap = cv2.VideoCapture(self.videoName)

    def getFrame(self, frameNum=None):
        if frameNum is not None:
            self.vidcap.set(cv2.CAP_PROP_POS_FRAMES, frameNum)
        self.trueFrameNum = self.vidcap.get(cv2.CAP_PROP_POS_FRAMES)
        self.readSuccess, self.frame = self.vidcap.read()

    def setCSV(self, csv_directory):
        self.csvName = csv_directory
        self.csvPd = pd.read_csv(self.csvName, delimiter = ',', encoding = 'euc-kr')

    def getAnnotations(self, frameNum=None):
        if frameNum is None:
            annoIdxList = self.csvPd.loc[self.csvPd['FrameNum']==self.frameNum].index.tolist()
        else:
            annoIdxList = self.csvPd.loc[self.csvPd['FrameNum']==frameNum].index.tolist()
        self.annos = self.csvPd.loc[annoIdxList, :]
        if len(self.annos) == 0:
            return True

    def parseAnnotations(self):
        for idx in range(0, len(self.annos)):
            dw = 1. / self.frame.shape[1]
            dh = 1. / self.frame.shape[0]
            # x = self.annos['CenterX'].iloc[idx]
            # y = self.annos['CenterY'].iloc[idx]
            x = abs(self.annos['LLX'].iloc[idx] + self.annos['URX'].iloc[idx]) / 2.0 - 1
            y = abs(self.annos['LLY'].iloc[idx] + self.annos['URY'].iloc[idx]) / 2.0 - 1
            w = abs(self.annos['LLX'].iloc[idx] - self.annos['URX'].iloc[idx])
            h = abs(self.annos['LLY'].iloc[idx] - self.annos['URY'].iloc[idx])
            # if self.boundingBoxsz['min'][0] > w:
            #     self.boundingBoxsz['min'][0] = w
            # if self.boundingBoxsz['min'][1] > h:
            #     self.boundingBoxsz['min'][1] = h
            # if self.boundingBoxsz['max'][0] < w:
            #     self.boundingBoxsz['max'][0] = w
            # if self.boundingBoxsz['max'][1] < h:
            #     self.boundingBoxsz['max'][1] = h
            x = x * dw
            w = w * dw
            y = y * dh
            h = h * dh
            clsId = self.classes[(self.annos['ObjectType'].iloc[idx])]
            self.outFile.write(str(clsId) + " " + " ".join([str(x), str(y), str(w), str(h)]) + '\n')

    def mkAnnotationText(self, fileName=None):
        if fileName is not None:
            self.currAnnotName = os.path.join(self.annotFolderName,fileName + '_' + str(self.nameCount).zfill(5) + '.txt')
        else:
            self.currAnnotName = os.path.join(self.annotFolderName, str(self.nameCount).zfill(5) + '.txt')

    def openAnnotationText(self):
        self.outFile = open(self.currAnnotName, 'w')

    def closeAnnotationText(self):
        self.outFile.close()

    def doAnnotation(self, fileName=None):
        self.mkAnnotationText(fileName)
        self.openAnnotationText()
        self.parseAnnotations()
        self.closeAnnotationText()

    def mkFolder(self, folderName):
        self.folderName = os.path.join(self.dataDir, folderName)
        self.imageFolderName = os.path.join(self.folderName, 'image')
        self.annotFolderName = os.path.join(self.folderName, 'labels')

        if os.path.isdir(self.folderName) == False:
            os.mkdir(self.folderName)
        if os.path.isdir(self.imageFolderName) == False:
            os.mkdir(self.imageFolderName)
        if os.path.isdir(self.annotFolderName) == False:
            os.mkdir(self.annotFolderName)

    def saveImage(self, fileName=None):
        if fileName is not None:
            self.currImageName = os.path.join(self.imageFolderName, fileName + '_' + str(self.nameCount).zfill(5) + '.jpg')
            cv2.imwrite(self.currImageName, self.frame)
        else:
            self.currImageName = os.path.join(self.imageFolderName, str(self.nameCount).zfill(5) + '.jpg')
            cv2.imwrite(self.currImageName, self.frame)

    def doGetFunc(self):
        self.getFrame(self.frameNum)
        isSkip = self.getAnnotations(self.frameNum)
        self.frameNum += self.frameStep
        return isSkip

    def openTrainText(self):
        self.trainText = open(os.path.join(self.folderName, 'train.txt'), 'w')

    def writeTrainText(self):
        # print(self.currImageName)
        self.trainText.write(self.currImageName + '\n')

    def closeTrainText(self):
        self.trainText.close()

    def printAnnot(self):
        for idx in range(0, len(self.annos)):
            print([self.frame.shape[1], self.frame.shape[0], self.annos['LLX'].iloc[idx], self.annos['URX'].iloc[idx], self.annos['LLY'].iloc[idx], self.annos['URY'].iloc[idx]])
            dw = 1. / self.frame.shape[1]
            dh = 1. / self.frame.shape[0]
            # x = self.annos['CenterX'].iloc[idx]
            # y = self.annos['CenterY'].iloc[idx]
            x = abs(self.annos['LLX'].iloc[idx] + self.annos['URX'].iloc[idx]) / 2.0 - 1
            y = abs(self.annos['LLY'].iloc[idx] + self.annos['URY'].iloc[idx]) / 2.0 - 1
            w = abs(self.annos['LLX'].iloc[idx] - self.annos['URX'].iloc[idx])
            h = abs(self.annos['LLY'].iloc[idx] - self.annos['URY'].iloc[idx])
            x = x * dw
            w = w * dw
            y = y * dh
            h = h * dh
            clsId = self.classes.index(self.annos['ObjectType'].iloc[idx])
            print([x, y, w, h])

    def increaseNameCount(self):
        self.nameCount += 1




#Image Crop for AVTDC Project
import cv2
import codecs
import os
import pandas as pd
# import keyboard

class VideoController:
    def __init__(self):
        #Check class list before cropping
        self.class_list = {'자전거':0, '버스':1, '사람':2, '세단':3, '트럭':4,
                           'bike':0, 'none':1, 'person':2, 'sedan':3, 'truck':4}
        # self.class_list = ['bike', 'truck', 'person', 'sedan', 'none']
        self.human_frame_diff = 9
        self.bicycle_frame_diff = 24
        self.bus_frame_diff = 30
        self.cars_frame_diff = 55
    #
    def setVideo(self, *args):
        if not args:
            video_name = os.path.join(self.folder_name, self.file_name, self.file_name + '.ts')
            self.video = VideoFile(video_name)

        else:
            self.video = VideoFile(args)

    def setCSV(self, *args):
        if not args:
            csv_name = os.path.join(self.folder_name, self.file_name, self.file_name + '.csv')
            self.csv = CSVFile(csv_name)
        else:
            self.csv = CSVFile(args)


    def setTargetFolder(self,folder_name, file_name):
        self.folder_name = folder_name
        self.file_name = file_name
        self.setVideo()
        self.setCSV()

    def setOutputDirectory(self, output_path):
        self.out_dir = os.path.join(output_path, self.file_name)
        if not os.path.isdir(self.out_dir):
            os.mkdir(self.out_dir)
        self._makeClassDir()

    def _makeClassDir(self):
        if not os.path.isdir(self.out_dir):
            os.mkdir(self.out_dir)

        for class_name in range(5):
            if not os.path.isdir(os.path.join(self.out_dir, str(class_name))):
                os.mkdir(os.path.join(self.out_dir, str(class_name)))
        self._makeClassDirforSuperResolutionTrainData()

    def _makeClassDirforSuperResolutionTrainData(self):
        for class_name in range(5):
            if (not os.path.isdir(os.path.join(self.out_dir, str(class_name) +"_64"))):
                os.mkdir(os.path.join(self.out_dir, str(class_name)+"_64"))

    def checkFrame(self, frame, line):
        if (self.class_list[line['ObjectType']] == 0):
            frame_diff = self.bicycle_frame_diff
        elif (self.class_list[line['ObjectType']] == 1  or self.class_list[line['ObjectType']] == 4):
            frame_diff =self.bus_frame_diff
        elif (self.class_list[line['ObjectType']] == 2):
            frame_diff = self.human_frame_diff
        elif (self.class_list[line['ObjectType']] == 3):
            frame_diff = self.cars_frame_diff

        if ((line['FrameNum'] - frame) >= frame_diff):
            return True

    def getBoundingBoxColor(self, line_object):
        # input : object type eg, 사람, 세단, 트럭, 자전거 , 버스
        if (line_object == 0): #bike
            RGB = (255, 255, 0)
        elif (line_object == 1): #truck
            RGB = (0, 255, 255)
        elif (line_object == 2): #person
            RGB = (255, 0, 0)
        elif (line_object == 3): #sedan
            RGB = (0, 255, 0)
        elif (line_object == 4): #none
            RGB = (0, 0, 255)

        else:
            RGB = (255, 255, 255)
        return RGB

    def drawBox(self, img, axis_list, type_name, RGB ):
        x1, y1, x2, y2 = axis_list
        img = cv2.rectangle(img,(int(x1), int(y1)),(int(x2), int(y2)), RGB, 2) #2 : thickness
        cv2.putText(img, type_name, (int(x2), int(y2)), cv2.FONT_HERSHEY_SIMPLEX, 0.5, RGB)# lineType=cv2.LINE_AA)
        return img

    # def getFrame1Index(self):
    #     for i in range(len(self.csv.csv_pd)):
    #             if self.csv.csv_pd['FrameNum'].iloc[i] == 1:
    #                 return i

    def makeSquare(self, axis_list):
        # input :
        #  axis_list = [line['CenterX'], line['CenterY'], line['LLX'], \
        #             line['LLY'], line['URX'], line['URY']]
        # output : [X1,X2,Y1,Y2]
        xc, yc, x1, y1, x2, y2 = axis_list

        x_length = x2 - x1
        y_length = y2 - y1
        if (x_length >= y_length):
            if (x_length % 2 == 1):
                if (x1 % 2 == 1):
                    Y1 = yc - (x_length + 1) / 2
                    Y2 = yc + (x_length + 1) / 2
                    X1 = x1
                    X2 = x2 + 1
                else:
                    Y1 = yc - (x_length + 1) / 2
                    Y2 = yc + (x_length + 1) / 2
                    X1 = x1 - 1
                    X2 = x2
            else:
                Y1 = yc - (x_length)/2
                Y2 = yc + (x_length)/2
                X1 = x1
                X2 = x2
        else:
            if (y_length % 2 == 1):
                if (y1 % 2 == 1):
                    Y1 = y1
                    Y2 = y2 + 1
                    X1 = xc - (y_length + 1) / 2
                    X2 = xc + (y_length + 1) / 2

                else:
                    Y1 = y1 - 1
                    Y2 = y2
                    X1 = xc - ((y_length + 1) / 2)
                    X2 = xc + ((y_length + 1) / 2)
            else:
                Y1 = y1
                Y2 = y2
                X1 = xc - ((y_length) / 2)
                X2 = xc + ((y_length) / 2)
        points = [X1, Y1, X2, Y2]

        for idx in range(len(points)):
            if (points[idx] < 0):
                points[idx] = 0
        if (points[0] > 1920):
            points[0] = 1920
        if (points[2] > 1920):
            points[2] = 1920
        if (points[1] > 1080):
            points[1] = 1080
        if (points[3] > 1080):
            points[3] = 1080

        return points

    def saveImg(self, image, line):
        x1, y1, x2, y2 = self.makeSquare([line['CenterX'], line['CenterY'], line['LLX'], line['LLY'], line['URX'], line['URY']])
        x1, y1, x2, y2 = int(x1), int(y1), int(x2), int(y2)
        cropped_img = image[y1:y2 ,x1:x2]
        img_name = self.file_name + "f_%05d_ID_%07d.jpg"%(line["FrameNum"], line['targetId'])
        cv2.imwrite(os.path.join(self.out_dir, str(self.class_list[line['ObjectType']]), img_name), cropped_img)
        if cropped_img.shape[0] >= 64:
            img_name = self.file_name + line['ObjectType'] + "f_%05d_ID_%07d.jpg"%(line["FrameNum"], line['targetId'])
            cv2.imwrite(os.path.join(self.out_dir, str(self.class_list[line['ObjectType']])+'_64', img_name), cropped_img)
        # print (img_name + " save done.")


    def iterVideo(self, video_flag = True, crop_flag = False, bb_flag = True, isFiltered = True, square = True, waitKey = 1):
        csv_pd = self.csv.csv_pd
        ID_list = []
        frame_list = []

        while 1:
            success, image = self.video.readVideo()

            if not success:
                break
            annoIdxList = csv_pd.loc[csv_pd['FrameNum']==self.video.frame].index.tolist()

            if crop_flag or (video_flag and bb_flag):
                for idx in annoIdxList:
                    line = csv_pd.loc[idx, :]

                    if crop_flag:
                        if (isFiltered):
                            if line['targetId'] in ID_list: #Object already exists
                                pass
                                idx = ID_list.index(line['targetId'])
                                before_frame = frame_list[idx]
                                if (self.checkFrame(before_frame, line)):
                                    frame_list[idx] = line['FrameNum']
                                    #squared_axis : x1 y1 x2 y2
                                    self.saveImg(image, line)
                            else:

                                ID_list.append(line['targetId'])
                                frame_list.append(line['FrameNum'])
                                self.saveImg(image, line)
                        else:
                            self.saveImg(image, line)

                    if bb_flag:
                        RGB = self.getBoundingBoxColor(self.class_list[line['ObjectType']])
                        if (square):
                            image = self.drawBox(image,
                                               self.makeSquare([line['CenterX'], line['CenterY'], line['LLX'], line['LLY'], line['URX'], line['URY']]),
                                               line['ObjectType'], RGB)
                        else:
                            image = self.drawBox(image,[line['LLX'], line['LLY'], line['URX'], line['URY']] , line['ObjectType'], RGB)

            if video_flag:
                print(str(self.video.frame))
                cv2.imshow("cropping", image)
                cv2.waitKey(waitKey)

        self.video.releaseVideo()

    def getCandidate(self, isFiltered = False):
        # print("Loaded video : " + self.video.video_name + " , loaded CSV : " + self.csv.csv_name)
        # count
        csv_pd = self.csv.csv_pd
        success, image = self.video.readVideo()

        currentFrameNum = self.video.vidcap.get(cv2.CAP_PROP_POS_FRAMES)
        index_list = csv_pd.index[csv_pd['FrameNum'] == currentFrameNum].tolist()
        # annotations = csv_pd.loc[index_list, :]



        # candidate_xy = []
        candidates = []
        labels = []
        if (success):
            for annoIdx in index_list:
                line = csv_pd.loc[annoIdx, :]
                axis_list = [line['CenterX'], line['CenterY'], line['LLX'], line['LLY'], line['URX'], line['URY']]
                className = line['ObjectType']
                # candidate_xy :  [X1,Y1,X2,Y2]
                candidate_xy = self.makeSquare(axis_list)
                candidates.append(candidate_xy)
                labels.append(className)

            return image, candidates, labels


        if (success):
            for i in range(len(csv_pd)):
                if (csv_pd['FrameNum'][i] > self.video.frame):
                    break
                elif (csv_pd['FrameNum'][i] == self.video.frame):
                    # print ("hello")
                    line = csv_pd.loc[i, :]
                    # print(str(line['FrameNum']) + " " + str(line['CenterX']))
                    axis_list = [line['CenterX'], line['CenterY'], line['LLX'], line['LLY'], line['URX'], line['URY']]
                    className = line['ObjectType']
                    # candidate_xy :  [X1,Y1,X2,Y2]
                    candidate_xy = self.makeSquare(axis_list)
                    candidates.append(candidate_xy)
                    labels.append(className)
            return image, candidates, labels


    def getFrame(self, frame_number):
        # self.video.setVideo() #initialize
        self.video.vidcap.set(cv2.CAP_PROP_POS_FRAMES, frame_number)
        success, frame = self.video.vidcap.read()
        return frame

    def getAnnotations(self, frame_number):
        csv_pd = self.csv.csv_pd
        # line = csv_pd.loc[frame_number, : ]

        # print (csv_pd['FrameNum'].where(csv_pd['FrameNum'] ==frame_number))
        index_list = csv_pd.index[csv_pd['FrameNum'] == frame_number].tolist()
        # print (csv_pd.index[csv_pd['FrameNum'] == frame_number].tolist())
        return csv_pd.loc[index_list, :]

    # def showVideo(self, square = False):
    #     #input : folder name -> then fn load csv file and video file
    #     #One can show annotations corresponding to frame
    #     csv_pd = self.csv.csv_pd
    #     while (self.video.vidcap.isOpened()):
    #
    #         success, image = self.video.readVideo()
    #         frame_1_index = self.getFrame1Index()
    #
    #         while success:
    #             for i in range(frame_1_index, len(csv_pd)):
    #                 line = csv_pd.loc[i]
    #                 while (line['FrameNum'] != self.video.frame):
    #                     success, image = self.video.readVideo()
    #                     cv2.waitKey(0)
    #
    #                 print (self.video.frame, line['FrameNum'])
    #                 RGB = self.getBoundingBoxColor(line['ObjectType'])
    #
    #                 if (square):
    #                     axis_list = [line['CenterX'], line['CenterY'], line['LLX'], line['LLY'], line['URX'], line['URY']]
    #                     x1, y1, x2, y2 = self.makeSquare(axis_list)
    #                     img = self.drawBox(image, [x1, y1, x2, y2], line['ObjectType'], RGB)
    #                 else:
    #                     img = self.drawBox(image,[line['LLX'], line['LLY'], line['URX'], line['URY']] , line['ObjectType'], RGB)
    #
    #                 print(line['FrameNum'], self.video.frame)
    #                 cv2.imshow("cropping", img)
    #         break
    #     self.video.releaseVideo()

    # def saveAllCroppedFile(self, isFiltered = False):
    #     csv_pd = self.csv.csv_pd
    #     success, image = self.video.readVideo()
    #     ID_list =[]
    #     frame_list = []
    #     # frame_1_index = self.getFrame1Index()
    #     max_frame = int(csv_pd['FrameNum'].describe()['max'])
    #     if (success):
    #         while max_frame >= self.video.frame:
    #             tmp_pd = csv_pd.loc[csv_pd['FrameNum']==self.video.frame]
    #             for idx in tmp_pd.index.tolist():
    #                 line = tmp_pd.loc[idx, :]
    #                 if (isFiltered):
    #                     if line['targetId'] in ID_list: #Object already exists
    #                         pass
    #                         idx = ID_list.index(line['targetId'])
    #                         before_frame = frame_list[idx]
    #                         if (self.checkFrame(before_frame, line)):
    #                             frame_list[idx] = line['FrameNum']
    #                             #squared_axis : x1 y1 x2 y2
    #                             self.saveImg(image, line)
    #                     else:
    #
    #                         ID_list.append(line['targetId'])
    #                         frame_list.append(line['FrameNum'])
    #                         self.saveImg(image, line)
    #
    #                 else: # In case of filtering is canceled
    #                     self.saveImg(image, line)
    #             success, image = self.video.readVideo()
    #
    #
    #
    #         # for i in range(frame_1_index, len(csv_pd)):
    #         #     line = csv_pd.loc[i, :]
    #         #     while (self.video.frame != line['FrameNum']):
    #         #         success, image = self.video.readVideo()
    #
    #
    #
    #     self.video.releaseVideo()
    #
    # # def saveCroppedFileFromSpecificFrameNumber(self, frame, annotations, interval):


