import os
import random

import pandas as pd
import numpy as np

import keypress

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
        self.imgcnt = 0
        # self.keyp = keypress.keyinput()

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
            

            self.cvt_vot_to_our(image, tmp_gt)
            cv2.polylines(image, tmp_gt, isClosed=True, color=(0, 0, 256), thickness=4)
            cv2.imshow('tmp', image)
            cv2.waitKey(1)

    def iterate_dataset_name(self):
        idx = 0
        for dataset_name in self.list_dataset_name:
            if idx == 0:
                idx += 1
                continue
            self.show_data_with_annot(dataset_name)

    def cvt_vot_to_our(self, image, gt_vot):
        gt_vot = gt_vot[0].reshape(-1,2)
        x_max, y_max = gt_vot.max(0)
        x_min, y_min = gt_vot.min(0)
        w = x_max - x_min
        h = y_max - y_min
        cv2.rectangle(image, (x_min, y_min), (x_max, y_max), color=(256, 0, 0), thickness=4)
        cv2.imshow('tmp2', image[y_min:y_min+h, x_min:x_min+w])



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



if __name__ == '__main__':

    vot = VOTParcer()
    vot.set_sequence_dir_path('/run/user/1020/gvfs/dav:host=192.168.0.3,port=5005,ssl=false,user=cpark/ResearchServer/dataset/VOT/sequences')
