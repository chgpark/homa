import numpy as np
import cv2

class CamProject:
    def __init__(self):
        self.window_name = 'test'

    def set_camera(self, num_dev):
        self.cap = cv2.VideoCapture(num_dev)

    def show(self):
        while True:
            ret, frame = self.cap.read()

            cv2.imshow(self.window_name, frame)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break


if __name__ == "__main__":
    CP = CamProject()
    CP.set_camera(0)
    CP.show()


