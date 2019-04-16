from gtts import gTTS
import os

class make_voice:
    def __init__(self):
        text = "안녕 진광"
        output_path = "/home/cpark/PycharmProjects/face/sounds"
        output_name = "JK"
        output_path = os.path.join(output_path, output_name + '.mp3')

        self.do(text, output_path)

    def do(self, text, output_path, lang='ko'):
        tts = gTTS(text=text, lang=lang)
        tts.save(output_path)

if __name__ == '__main__':
    mv = make_voice()
