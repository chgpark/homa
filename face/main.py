import cv2
from pydub import AudioSegment
from pydub.playback import play

class voice:
    def __init__(self):
        self.voice_dict = {}
        self.voice_file_dict = {1:"sounds/JK.mp3"}

        self.get_voice()

    def get_voice(self):
        for voice_key in self.voice_file_dict.keys():
            voice = AudioSegment.from_mp3(self.voice_file_dict[1])
            self.voice_dict[voice_key] = voice

    def run_voice(self, voice_key):
        play(self.voice_dict[voice_key])

class face:
    def __init__(self):
        self.cascPath = '/home/cpark/PycharmProjects/face/haarcascade_frontalface_default.xml'
        self.faceCascade = cv2.CascadeClassifier(self.cascPath)

    def get_face(self, gray):
        faces = self.faceCascade.detectMultiScale(gray,
        # scaleFactor=1.1,
        # minNeighbors=5,
        # minSize=(30, 30),
        # flags = cv2.CASCADE_SCALE_IMAGE
        )
        return faces

class video:
    def __init__(self, cam_num):
        self.cap = cv2.VideoCapture(cam_num)
        self.face_detect = face()
        self.voice_by_face = voice()

    def do(self):
        while(True):
            # Capture frame-by-frame
            ret, frame = self.cap.read()

            # Our operations on the frame come here
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

            faces = self.face_detect.get_face(gray=gray)

            if len(faces) > 0:
                print('detect')
            for (x, y, w, h) in faces:
                cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

                face_class = 1

                if face_class == 1:
                    self.voice_by_face.run_voice()


            # Display the resulting frame
            cv2.imshow('frame',frame)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

        self.release()

    def release(self):
        self.cap.release()
        cv2.destroyAllWindows()

if __name__ == '__main__':
    v = video(cam_num=1)
    v.do()
