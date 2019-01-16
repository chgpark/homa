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

class VOTParcer:
    def __init__(self):
        self.video = VideoFile()
        self.annot = AnnotationFile()

    def set_sequence_dir_path(self, sequence_dir_path):
        self.sequence_dir_path = sequence_dir_path
        self.__read_list_txt__('list.txt')
        self.iterate_dataset_name()

    def __read_list_txt__(self, list_txt_name):
        with open(os.path.join(self.sequence_dir_path, list_txt_name), "r") as list_txt:
            self.list_dataset_name = list_txt.read().split('\n')
        list_txt.close()

    def show_data_with_annot(self, dataset_name):
        self.dataset_path = os.path.join(self.sequence_dir_path, dataset_name)
        self.np_gt = np.loadtxt(os.path.join(self.dataset_path, 'groundtruth.txt'), delimiter=',').astype(np.int32)

        self.list_data_file = os.listdir(os.path.join(self.dataset_path, 'color'))

        for idx in range(self.np_gt.shape[0]):
            image = cv2.imread(os.path.join(self.dataset_path, 'color', self.list_data_file[idx]))
            tmp_gt = [self.np_gt[idx].reshape(-1, 1, 2)]
            cv2.polylines(image, tmp_gt, isClosed=True, color=(255, 0, 0))
            cv2.imshow('tmp', image)
            cv2.waitKey(1)

    def iterate_dataset_name(self):
        idx = -1
        for dataset_name in self.list_dataset_name:
            idx += 1
            if idx <= 1:
                continue
            self.show_data_with_annot(dataset_name)




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
        self.list_classes = os.listdir(loaded_path)
        self.className = className
        self.train_img = []
        self.train_label = []
        self.num = 0
        # for class_path in self.list_classes:
        for clsIdx, class_path in enumerate(className):
            list_img_per_class = os.listdir(os.path.join(self.loaded_path, class_path))
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
        self.list_classes = os.listdir(loaded_path)
        self.num = 0
        self.train_img = []
        self.train_label = []
        self.type_flag = type_flag

       # for class_path in self.list_classes:
        for clsIdx in range(1000):
            clsIdx += 1
            list_img_per_class = os.listdir(os.path.join(self.loaded_path, str(clsIdx)))
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



if __name__ == '__main__':
    vot = VOTParcer()
    vot.set_sequence_dir_path('/run/user/1020/gvfs/dav:host=192.168.0.3,port=5005,ssl=false,user=cpark/ResearchServer/dataset/VOT/sequences')
