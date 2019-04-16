import cv2
import os
import numpy as np
import pandas as pd

class VideoFile:
    def __init__(self):
        self.width = 3840
        self.height = 2160

    def set_video(self, video_path):
        self.video_path = video_path
        self.vidcap = cv2.VideoCapture(video_path)

    def release_video(self):
        self.vidcap.release()

    def read_video(self):
        self.frame = self.vidcap.get(cv2.CAP_PROP_POS_FRAMES)
        self.success, self.image = self.vidcap.read()
        return self.success, self.image

class AnnotationFile:
    def set_text(self, text_path):
        self.text_path = text_path
        self.pd_text = pd.read_csv(text_path, sep=" ", header=None)

class OkumaCropper:
    def __init__(self):
        self.video = VideoFile()
        self.annotation = AnnotationFile()

    def set_data_dir(self, data_path):
        self.data_path = data_path
        self.videos_path = os.path.join(self.data_path, 'videos')
        self.annotations_path = os.path.join(self.data_path, 'annotations')

    def get_filenames(self):
        self.video_names = os.listdir(self.videos_path)

    def set_output_path(self, output_path):
        self.output_path = output_path
        if not os.path.isdir(self.output_path):
            os.mkdir(self.output_path)

    def make_square(self, axis_list):
        x1, y1, x2, y2 = axis_list
        xc = (x1 + x2) / 2
        yc = (y1 + y2) / 2
        x_length = abs(x2 - x1)
        y_length = abs(y2 - y1)
        if x_length >= y_length:
            if x_length % 2 == 1:
                if x1 % 2 == 1:
                    Y1 = yc - (x_length + 1) / 2
                    Y2 = yc + (x_length + 1) / 2
                    X1 = x1
                    X2 = x2 + 1
                else:
                    Y1 = yc - (x_length + 1) / 2
                    Y2 = yc + (x_length + 1) / 2
                    X1 = x1
                    X2 = x2 + 1
            else:
                Y1 = yc - x_length / 2
                Y2 = yc + x_length / 2
                X1 = x1
                X2 = x2
        else:
            if y_length % 2 == 1:
                if y1 % 2 == 1:
                    Y1 = y1
                    Y2 = y2
                    X1 = xc - (y_length + 1) / 2
                    X2 = xc + (y_length + 1) / 2
                else:
                    Y1 = y1 - 1
                    Y2 = y2
                    X1 = xc - (y_length + 1) / 2
                    X2 = xc + (y_length + 1) / 2
            else:
                Y1 = y1
                Y2 = y2
                X1 = xc - y_length / 2
                X2 = xc + y_length / 2
        points = [X1, Y1, X2, Y2]
        for idx in range(len(points)):
            if points[idx] < 0:
                points[idx] = 0

        if points[0] > self.video.width:
            points[0] = self.video.width
        if points[2] > self.video.width:
            points[2] = self.video.width
        if points[1] > self.video.height:
            points[1] = self.video.height
        if points[3] > self.video.height:
            points[3] = self.video.height

        return points

    def draw_box(self, image, axis_list, type_name):
        x1, y1, x2, y2 = axis_list
        image = cv2.rectangle(image, (x1, y1), (x2, y2), (0, 255, 0), 2)
        cv2.putText(image, type_name, (int(x2), int(y2)), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0))
        return image

    def save_image(self, image, line):
        x1, y1, x2, y2 = self.make_square([line[1], line[2], line[3], line[4]])
        x1, y1, x2, y2 = int(x1),int(y1),int(x2),int(y2)
        cropped_image = image[y1:y2, x1:x2]
        cv2.imwrite(os.path.join(self.output_path, self.target_name + '_' + str(line[0]) + '_'+ str(self.video.frame) + '.jpg'),cropped_image)

    def iteration_file(self):
        n = 0
        for video_name in self.video_names:
            if n <= 4:
                n+=1
                continue
            print(video_name)
            self.target_name = os.path.splitext(video_name)[0]
            self.video.set_video(os.path.join(self.videos_path, video_name))
            self.annotation.set_text(os.path.join(self.annotations_path, self.target_name + '.txt'))
            self.cropping_video()

    def cropping_video(self):
        pd_text = self.annotation.pd_text
        while 1:
            success, image = self.video.read_video()
            if not success:
                break
            annotation_idx_list = pd_text.loc[pd_text[5] == self.video.frame].index.tolist()


            for idx in annotation_idx_list:
                line = pd_text.loc[idx,:]
                if line[6] == 1 or line[8] == 1:
                    continue
                self.save_image(image, line)
            #     image = self.draw_box(image, [line[1], line[2], line[3], line[4]], line[9])
            # cv2.imshow("cropping", image)
            # cv2.waitKey(1)



if __name__ == '__main__':
    # cv2.namedWindow("cropping", cv2.WINDOW_GUI_NORMAL)
    cr = OkumaCropper()
    cr.set_data_dir('/run/user/1000/gvfs/smb-share:server=urobot.synology.me,share=researchserver/dataset/AVTDC/opendata/DataSet/okutama action')
    cr.set_output_path('/run/user/1000/gvfs/smb-share:server=urobot.synology.me,share=researchserver/dataset/AVTDC/opendata/cropped')
    cr.get_filenames()
    cr.iteration_file()